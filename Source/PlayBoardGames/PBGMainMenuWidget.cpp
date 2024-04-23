#include "PBGMainMenuWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "PBGGameInstance.h"

void UPBGMainMenuWidget::SetUp()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetWidgetToFocus(this->TakeWidget());
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeUIOnly);
	PlayerController->SetShowMouseCursor(true);
}

void UPBGMainMenuWidget::TearDown()
{
	this->RemoveFromParent();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeGameOnly;
	PlayerController->SetInputMode(InputModeGameOnly);
	PlayerController->SetShowMouseCursor(false);
}

bool UPBGMainMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(Button_Exit != nullptr)) return false;
	Button_Exit->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::ExitGame);

	return true;
}

void UPBGMainMenuWidget::NativeConstruct()
{
	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	TArray<FPBGGame> PBGGames = PBGGameInstance->GetPBGGames();
	if (PBGGames.IsEmpty()) return;

	// ToDo : Make it more simple.
	if (!ensure(TextBlock_Game1 != nullptr)) return;
	if (!PBGGames.IsValidIndex(1)) return;
	TextBlock_Game1->SetText(FText::FromString(PBGGames[1].Name));
}

void UPBGMainMenuWidget::ExitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}