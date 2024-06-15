#include "PBGGameInstance.h"

#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

#include "PBGSaveGame.h"
#include "PBGGameState.h"
#include "PBGPlayerState.h"
#include "PBGPlayerController.h"
#include "PBGMainMenuWidget.h"

const static FName SERVER_NAME_SETTING_KEY = TEXT("Server Name");

UPBGGameInstance::UPBGGameInstance()
{
	bIsHost = false;
	// TODO : Make it more simply.
	PBGGames.Empty();
	PBGGames = { FPBGGame("Null"), FPBGGame("Yacht") };
}

void UPBGGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem != nullptr)
	{
		if (IsDedicatedServerInstance())
		{
			UE_LOG(LogTemp, Warning, TEXT("DEDICATED SERVER"));
		}

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

void UPBGGameInstance::SaveGameData(const FString& InputID)
{
	if (UGameplayStatics::DoesSaveGameExist(InputID, 0))
	{
		UGameplayStatics::SaveGameToSlot(PBGSaveGame, PBGSaveGame->SaveSlotName, PBGSaveGame->UserIndex);
	}
	else
	{
		PBGSaveGame = GetMutableDefault<UPBGSaveGame>();
		PBGSaveGame->SaveSlotName = InputID;
		PBGSaveGame->UserIndex = 0;
		PBGSaveGame->ID = InputID;
		UGameplayStatics::SaveGameToSlot(PBGSaveGame, PBGSaveGame->SaveSlotName, PBGSaveGame->UserIndex);
	}
}

void UPBGGameInstance::LoadGameData(const FString& InputID)
{
	if (UGameplayStatics::DoesSaveGameExist(InputID, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameExist"));
	}
	else
	{
		SaveGameData(InputID);
		UE_LOG(LogTemp, Warning, TEXT("No SaveGameExist"));
	}
	PBGSaveGame = Cast<UPBGSaveGame>(UGameplayStatics::LoadGameFromSlot(InputID, 0));
}

void UPBGGameInstance::Host()
{
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

	SessionInterface->JoinSession(0, NAME_GameSession, SessionSearch->SearchResults[Index]);
}

void UPBGGameInstance::FindServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

		// TODO : Loading Widget Needed
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

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(GetFirstLocalPlayerController());
	if (!ensure(PBGPlayerController != nullptr)) return;

	PBGPlayerController->TurnOffMainMenu();

	bIsHost = true;
	
	World->ServerTravel("/Game/Maps/Lobby?listen");
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
	if (Success && SessionSearch.IsValid())
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

		APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(GetFirstLocalPlayerController());
		if (!ensure(PBGPlayerController != nullptr)) return;

		PBGPlayerController->UpdateServerList(ServerDatas);
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

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPBGGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	// TODO : if In Lobby, Need to change... ( think : need new interface for Load to MainMenu )
	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(GetFirstLocalPlayerController());
	if (!ensure(PBGPlayerController != nullptr)) return;

	bIsHost = false;
	PBGPlayerController->LoadToMainMenuLevel();
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