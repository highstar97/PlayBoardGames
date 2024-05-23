#include "PBGPlayerController.h"

#include "PBGGameInstance.h"
#include "PBGPlayerState.h"
#include "PBGMainMenuWidget.h"

APBGPlayerController::APBGPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_MainMenuClass(TEXT("/Game/Blueprints/MainMenu/WBP_MainMenu"));
	if (BP_MainMenuClass.Succeeded())
	{
		PBGMainMenuClass = BP_MainMenuClass.Class;
	}
}

void APBGPlayerController::Host(FString ServerName)
{
	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	PBGGameInstance->SetDesiredServerName(ServerName);
	PBGGameInstance->Host();
}

void APBGPlayerController::Join(uint32 Index)
{
	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	PBGGameInstance->Join(Index);

	if (!ensure(PBGMainMenu != nullptr)) return;
	PBGMainMenu->TearDown();
}

void APBGPlayerController::LoadToMainMenuLevel()
{
	ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void APBGPlayerController::FindServerList()
{
	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	PBGGameInstance->FindServerList();
}

void APBGPlayerController::UpdateServerList(TArray<FServerData> ServerDatas)
{
	if (!ensure(PBGMainMenu != nullptr)) return;

	PBGMainMenu->UpdateServerList(ServerDatas);
}

void APBGPlayerController::TurnOnMainMenu()
{
	if (!ensure(PBGMainMenu != nullptr)) return;

	PBGMainMenu->SetUp();
}

void APBGPlayerController::TurnOffMainMenu()
{
	if (!ensure(PBGMainMenu != nullptr)) return;

	PBGMainMenu->TearDown();
}

void APBGPlayerController::Server_SetbIsHost_Implementation(const bool _bIsHost)
{
	APBGPlayerState* PBGPlayerState = GetPlayerState<APBGPlayerState>();
	if (!ensure(PBGPlayerState != nullptr)) return;

	PBGPlayerState->SetbIsHost(_bIsHost);
}

void APBGPlayerController::Server_SetUserName_Implementation(const FString& _UserName)
{
	APBGPlayerState* PBGPlayerState = GetPlayerState<APBGPlayerState>();
	if (!ensure(PBGPlayerState != nullptr)) return;

	PBGPlayerState->SetUserName(_UserName);
}

void APBGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (!ensure(PBGMainMenuClass != nullptr)) return;
		PBGMainMenu = CreateWidget<UPBGMainMenuWidget>(this, PBGMainMenuClass);
		if (!ensure(PBGMainMenu != nullptr)) return;

		PBGMainMenu->SetMainMenuInterface(this);
		TurnOnMainMenu();
	}
}