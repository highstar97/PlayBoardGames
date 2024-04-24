#include "PBGGameInstance.h"

#include "OnlineSessionSettings.h"

#include "PBGMainMenuWidget.h"

const static FName SERVER_NAME_SETTING_KEY = TEXT("Server Name");

UPBGGameInstance::UPBGGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_MainMenuClass(TEXT("/Game/Blueprints/MainMenu/WBP_MainMenu"));
	if (!ensure(BP_MainMenuClass.Class != nullptr)) return;

	PBGMainMenuClass = BP_MainMenuClass.Class;

	// ToDo : Make it more simply.
	PBGGames.Empty();
	FPBGGame Null;
	PBGGames.Add(Null);
	FPBGGame Yacht("Yacht");
	PBGGames.Add(Yacht);
}

void UPBGGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem : %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPBGGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPBGGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPBGGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPBGGameInstance::OnJoinSessionComplete);
		}
	}

	if (!ensure(GetEngine() != nullptr)) return;
	GetEngine()->OnNetworkFailure().AddUObject(this, &UPBGGameInstance::OnNetworkFailure);
}

void UPBGGameInstance::LoadMenu()
{
	if (!ensure(PBGMainMenuClass != nullptr)) return;

	MainMenu = CreateWidget<UPBGMainMenuWidget>(this, PBGMainMenuClass);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->SetUp();

	MainMenu->SetMainMenuInterface(this);
}

void UPBGGameInstance::Host(FString ServerName)
{
	DesiredServerName = ServerName;
	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* ExistingSessionInterface = SessionInterface->GetNamedSession(NAME_GameSession);
		if (ExistingSessionInterface != nullptr)
		{
			SessionInterface->DestroySession(NAME_GameSession);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPBGGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	if (MainMenu != nullptr)
	{
		MainMenu->TearDown();
	}

	SessionInterface->JoinSession(0, NAME_GameSession, SessionSearch->SearchResults[Index]);
}

void UPBGGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPBGGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPBGGameInstance::StartSession()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->StartSession(NAME_GameSession);
	}
}

void UPBGGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create Session"));
		return;
	}

	if (MainMenu != nullptr)
	{
		MainMenu->TearDown();
	}

	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting"));

	/*
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/Lobby?listen");
	*/
}

void UPBGGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UPBGGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && MainMenu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finish Find Session"));

		TArray<FServerData> ServerDatas;
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session Name : %s"), *SearchResult.GetSessionIdStr());
			FServerData ServerData;

			ServerData.HostUserName = SearchResult.Session.OwningUserName;
			ServerData.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			ServerData.CurrentPlayers = ServerData.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;

			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(SERVER_NAME_SETTING_KEY, ServerName))
			{
				ServerData.Name = ServerName;
			}
			else
			{
				ServerData.Name = "Could not find name.";
			}

			ServerDatas.Add(ServerData);
		}

		MainMenu->SetServerList(ServerDatas);
	}
}

void UPBGGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string"));
		return;
	}

	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPBGGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	LoadMainMenu();
}

void UPBGGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSetting;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			SessionSetting.bIsLANMatch = true;
		}
		else
		{
			SessionSetting.bIsLANMatch = false;
		}
		SessionSetting.NumPublicConnections = 2;
		SessionSetting.bShouldAdvertise = true;
		SessionSetting.bUsesPresence = true;
		SessionSetting.Set(SERVER_NAME_SETTING_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->CreateSession(0, NAME_GameSession, SessionSetting);
	}
}