#include "LobbyPlayerController.h"

#include "../PBGSaveGame.h"
#include "../PBGGameInstance.h"
#include "../PBGGameState.h"
#include "../PBGPlayerState.h"
#include "LobbyWidget.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	static ConstructorHelpers::FClassFinder<ULobbyWidget> BP_LobbyWidgetClass(TEXT("/Game/Blueprints/Lobby/WBP_LobbyWidget"));
	if (BP_LobbyWidgetClass.Succeeded())
	{
		LobbyWidgetClass = BP_LobbyWidgetClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> BP_TransitionWidgetClass(TEXT("/Game/Blueprints/WBP_Transition"));
	if (BP_TransitionWidgetClass.Succeeded())
	{
		TransitionWidgetClass = BP_TransitionWidgetClass.Class;
	}

	bIsLobbyWidgetTurnOn = false;
	bIsTransitionWidgetTurnOn = false;
}

void ALobbyPlayerController::TurnOnLobbyWidget()
{
	if (bIsLobbyWidgetTurnOn) return;

	if (!ensure(LobbyWidget != nullptr)) return;

	LobbyWidget->AddToViewport();

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetWidgetToFocus(LobbyWidget->TakeWidget());
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);

	bIsLobbyWidgetTurnOn = true;
}

void ALobbyPlayerController::Client_TurnOffLobbyWidget_Implementation()
{
	if (!bIsLobbyWidgetTurnOn) return;

	if (!ensure(LobbyWidget != nullptr)) return;

	LobbyWidget->RemoveFromParent();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);

	bIsLobbyWidgetTurnOn = false;
}

void ALobbyPlayerController::TurnOnTransitionWidget()
{
	if (bIsTransitionWidgetTurnOn) return;

	if (!ensure(TransitionWidget != nullptr)) return;

	TransitionWidget->AddToViewport();

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeUIOnly);
	
	bIsTransitionWidgetTurnOn = true;
}

void ALobbyPlayerController::TurnOffTransitionWidget()
{
	if (!bIsTransitionWidgetTurnOn) return;

	if (!ensure(TransitionWidget != nullptr)) return;

	TransitionWidget->RemoveFromParent();

	FInputModeGameOnly InputModeGameOnly;

	SetInputMode(InputModeGameOnly);

	bIsTransitionWidgetTurnOn = false;
}

void ALobbyPlayerController::Server_UpdatePlayerState_Implementation(const bool _bIsHost, const FString& _UserName)
{
	APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(GetPlayerState<APBGPlayerState>());
	if (!ensure(PBGPlayerState != nullptr)) return;

	PBGPlayerState->SetbIsHost(_bIsHost);
	PBGPlayerState->SetUserName(_UserName);
}

void ALobbyPlayerController::Client_UpdatePlayerState_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(World->GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;
	
	bIsHost = PBGGameInstance->GetbIsHost();
	
	UPBGSaveGame* PBGSaveGame = PBGGameInstance->GetPBGSaveGame();
	if (!ensure(PBGSaveGame != nullptr)) return;

	UserName = PBGSaveGame->ID;

	Server_UpdatePlayerState(bIsHost, UserName);
}

void ALobbyPlayerController::Server_UpdatePlayerListToAllClient_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APBGGameState* PBGGameState = Cast<APBGGameState>(World->GetGameState());
	if (!ensure(PBGGameState != nullptr)) return;

	TArray<APBGPlayerState*> ConnectedPlayerStates;
	ConnectedPlayerStates.Empty();

	for (TObjectPtr<APlayerState> _PlayerState : PBGGameState->PlayerArray)
	{
		APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(_PlayerState);
		if (!ensure(PBGPlayerState != nullptr)) return;

		ConnectedPlayerStates.Add(PBGPlayerState);
	}

	for (APBGPlayerState* _PlayerState : ConnectedPlayerStates)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server's bIsHost : %s, UserName : %s"), _PlayerState->GetbIsHost() ? TEXT("True") : TEXT("False"), *_PlayerState->GetUserName());
	}

	for (TObjectPtr<APlayerState> _PlayerState : PBGGameState->PlayerArray)
	{
		ALobbyPlayerController* LobbyPlayerController = Cast<ALobbyPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(LobbyPlayerController != nullptr)) return;

		LobbyPlayerController->Client_UpdatePlayerList(ConnectedPlayerStates);
	}
}

void ALobbyPlayerController::Client_UpdatePlayerList_Implementation(const TArray<APBGPlayerState*>& ConnectedPlayerStates)
{
	for (APBGPlayerState* _PlayerState : ConnectedPlayerStates)
	{
		UE_LOG(LogTemp, Warning, TEXT("Client's bIsHost : %s, UserName : %s"), _PlayerState->GetbIsHost() ? TEXT("True") : TEXT("False"), *_PlayerState->GetUserName());
	}

	if (!ensure(TransitionWidget != nullptr)) return;
	TurnOffTransitionWidget();

	if (!ensure(LobbyWidget != nullptr)) return;
	TurnOnLobbyWidget();

	LobbyWidget->UpdatePlayerList(ConnectedPlayerStates);
}

void ALobbyPlayerController::LoadToMainMenuLevel()
{
	ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
		
	if (IsLocalPlayerController())
	{
		if (!ensure(TransitionWidgetClass != nullptr)) return;
		TransitionWidget = CreateWidget<UUserWidget>(this, TransitionWidgetClass);
		if (!ensure(TransitionWidget != nullptr)) return;

		if (!ensure(LobbyWidgetClass != nullptr)) return;
		LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
		if (!ensure(LobbyWidget != nullptr)) return;

		TurnOnTransitionWidget();

		Client_UpdatePlayerState();

		GetWorldTimerManager().SetTimer(UpdatePlyaerListTimer, this, &ALobbyPlayerController::Server_UpdatePlayerListToAllClient, 1.5f, false);
	}
}