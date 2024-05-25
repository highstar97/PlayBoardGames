#include "LobbyWidget.h"

#include "Components/PanelWidget.h"
#include "Components/Button.h"

#include "../PBGGameInstance.h"
#include "../PBGGameState.h"
#include "../PBGPlayerState.h"
#include "LobbyPlayerController.h"
#include "LobbyPlayerRowWidget.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& Objectinitializer) : Super(Objectinitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_PlayerRowClass(TEXT("/Game/Blueprints/Lobby/WBP_PlayerRow"));
	if (BP_PlayerRowClass.Succeeded())
	{
		PlayerRowClass = BP_PlayerRowClass.Class;
	}
}

void ULobbyWidget::UpdatePlayerList(TArray<APBGPlayerState*> ConnectedPlayerStates)
{
	if (!ensure(ScrollBox_PlayerList != nullptr)) return;

	ScrollBox_PlayerList->ClearChildren();

	for (APBGPlayerState*& PBGPlayerState : ConnectedPlayerStates)
	{
		if (!ensure(PlayerRowClass != nullptr)) return;
		ULobbyPlayerRowWidget* PlayerRow = CreateWidget<ULobbyPlayerRowWidget>(GetOwningPlayer(), PlayerRowClass);
		if (!ensure(PlayerRow != nullptr)) return;

		PlayerRow->SetPlayerName(FText::FromString(PBGPlayerState->GetUserName()));
		PlayerRow->Setup(this, PBGPlayerState->GetbIsHost());

		ScrollBox_PlayerList->AddChild(PlayerRow);
	}
}

void ULobbyWidget::KickOut(ULobbyPlayerRowWidget* PlayerRow)
{
	if (!ensure(ScrollBox_PlayerList != nullptr)) return;

	int32 TargetIndex = ScrollBox_PlayerList->GetChildIndex(PlayerRow);

	ScrollBox_PlayerList->RemoveChild(PlayerRow);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APBGGameState* PBGGameState = Cast<APBGGameState>(World->GetGameState());
	if (!ensure(PBGGameState != nullptr)) return;

	APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(PBGGameState->PlayerArray[TargetIndex]);
	if (!ensure(PBGPlayerState != nullptr)) return;

	ALobbyPlayerController* LobbyPlayerController = Cast<ALobbyPlayerController>(PBGPlayerState->GetPlayerController());
	if (!ensure(LobbyPlayerController != nullptr)) return;

	LobbyPlayerController->LoadToMainMenuLevel();
}

bool ULobbyWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(Button_CancelGame != nullptr)) return false;
	Button_CancelGame->OnClicked.AddDynamic(this, &ULobbyWidget::ExitGame);

	return true;
}

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(World->GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	TextBlock_GameName->SetText(FText::FromString(PBGGameInstance->GetDesiredServerName()));
}

void ULobbyWidget::ExitGame()
{
	ALobbyPlayerController* LobbyPlayerController = GetOwningPlayer<ALobbyPlayerController>();
	if (!ensure(LobbyPlayerController != nullptr)) return;

	LobbyPlayerController->LoadToMainMenuLevel();
}