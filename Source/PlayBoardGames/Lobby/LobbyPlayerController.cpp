#include "LobbyPlayerController.h"

#include "LobbyWidget.h"
#include "../PBGGameState.h"
#include "../PBGPlayerState.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	static ConstructorHelpers::FClassFinder<ULobbyWidget> BP_LobbyWidgetClass(TEXT("/Game/Blueprints/Lobby/WBP_LobbyWidget"));
	if (BP_LobbyWidgetClass.Succeeded())
	{
		LobbyWidgetClass = BP_LobbyWidgetClass.Class;
	}
}

void ALobbyPlayerController::TurnOnLobbyWidget()
{
	if (!ensure(LobbyWidget != nullptr)) return;

	LobbyWidget->AddToViewport();

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetWidgetToFocus(LobbyWidget->TakeWidget());
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
}

void ALobbyPlayerController::Client_TurnOffLobbyWidget_Implementation()
{
	if (!ensure(LobbyWidget != nullptr)) return;

	LobbyWidget->RemoveFromParent();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
}

void ALobbyPlayerController::UpdatePlayerList()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APBGGameState* PBGGameState = Cast<APBGGameState>(World->GetGameState());
	if (!ensure(PBGGameState != nullptr)) return;

	// PBGGameState->PrintPlayerArray();

	TArray<APBGPlayerState*> ConnectedPlayerStates;
	ConnectedPlayerStates.Empty();

	UE_LOG(LogTemp, Warning, TEXT("UpdatePlayerList on %s"), *this->GetName());
	for (TObjectPtr<APlayerState> _PlayerState : PBGGameState->PlayerArray)
	{
		APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(_PlayerState);
		if (!ensure(PBGPlayerState != nullptr)) return;

		UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), PBGPlayerState->GetbIsHost() ? TEXT("True") : TEXT("False"));
		UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), *PBGPlayerState->GetUserName());

		ConnectedPlayerStates.Add(PBGPlayerState);
	}

	if (!ensure(LobbyWidget != nullptr)) return;

	LobbyWidget->UpdatePlayerList(ConnectedPlayerStates);
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
		
	if (IsLocalPlayerController())
	{
		if (!ensure(LobbyWidgetClass != nullptr)) return;
		LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
		if (!ensure(LobbyWidget != nullptr)) return;

		TurnOnLobbyWidget();
		UpdatePlayerList();
	}
}