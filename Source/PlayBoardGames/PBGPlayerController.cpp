#include "PBGPlayerController.h"

#include "PBGMainMenuWidget.h"
#include "PBGGameInstance.h"

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

	UE_LOG(LogTemp, Warning, TEXT("Turn oning Controller : %s"), *this->GetName());
}

void APBGPlayerController::TurnOffMainMenu()
{
	if (!ensure(PBGMainMenu != nullptr)) return;

	PBGMainMenu->TearDown();
}

void APBGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(PBGMainMenuClass != nullptr)) return;
	PBGMainMenu = CreateWidget<UPBGMainMenuWidget>(this, PBGMainMenuClass);
	if (!ensure(PBGMainMenu != nullptr)) return;

	PBGMainMenu->SetMainMenuInterface(this);
	TurnOnMainMenu();
}