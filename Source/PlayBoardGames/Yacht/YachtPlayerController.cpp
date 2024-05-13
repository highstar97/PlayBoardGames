#include "YachtPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "YachtGameMode.h"
#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtWidget.h"
#include "YachtDiceSlotWidget.h"

AYachtPlayerController::AYachtPlayerController()
{
	static ConstructorHelpers::FClassFinder<UYachtWidget> BP_YachtWidgetClass(TEXT("/Game/Blueprints/Yacht/WBP_YachtWidget"));
	if (BP_YachtWidgetClass.Succeeded())
	{
		YachtWidgetClass = BP_YachtWidgetClass.Class;
	}
}

void AYachtPlayerController::InitPlayerState()
{
	Super::InitPlayerState();

	if (!ensure(PlayerState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = Cast<AYachtPlayerState>(PlayerState);
	if (!ensure(YachtPlayerState != nullptr)) return;

	YachtPlayerState->OnRemainingTurnChanged.AddUObject(this, &AYachtPlayerController::Server_UpdateRemainingTurnToAllClient);
}

void AYachtPlayerController::TurnOnYachtWidget()
{
	if (!ensure(YachtWidget != nullptr)) return;
	
	YachtWidget->AddToViewport();

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetWidgetToFocus(YachtWidget->TakeWidget());
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
}

void AYachtPlayerController::TurnOffYachtWidget()
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->RemoveFromParent();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
}

bool AYachtPlayerController::IsPlayerTurn()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return false;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return false;

	AYachtPlayerState* YachtPlayerState = GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return false;

	if (YachtGameState->GetWhichPlayerTurn() == YachtPlayerState->GetPlayerNumber())
	{
		return true;
	}
	return false;
}

bool AYachtPlayerController::IsTurnRemain()
{
	AYachtPlayerState* YachtPlayerState = GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return false;

	if (YachtPlayerState->GetRemainingTurn() > 0)
	{
		return true;
	}
	return false;
}

void AYachtPlayerController::Server_FinishTurn_Implementation()
{
	AYachtPlayerState* YachtPlayerState = GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	YachtPlayerState->FinishTurn();
}

void AYachtPlayerController::Server_NextTurn_Implementation()
{
	AYachtPlayerState* YachtPlayerState = GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	YachtPlayerState->NextTurn();
}

void AYachtPlayerController::Server_UpdateYourNumberToAllClient_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerState* YachtPlayerState = Cast<AYachtPlayerState>(_PlayerState);
		if (!ensure(YachtPlayerState != nullptr)) return;

		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdateYourNumber(YachtPlayerState->GetPlayerNumber());
	}
}

void AYachtPlayerController::Client_UpdateYourNumber_Implementation(const int32 YourNumber)
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->UpdateTextBlock_YourNumber(YourNumber);
}

void AYachtPlayerController::Server_UpdateValueToAllClient_Implementation(const TArray<int32>& ValueArray)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdateValue(ValueArray);
	}
}

void AYachtPlayerController::Client_UpdateValue_Implementation(const TArray<int32>& ValueArray)
{
	if (!ensure(YachtWidget != nullptr)) return;
	
	YachtWidget->UpdateValue(ValueArray);
}

void AYachtPlayerController::Server_UpdateKeepToAllClient_Implementation(const TArray<bool>& KeepArray)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdateKeep(KeepArray);
	}
}

void AYachtPlayerController::Client_UpdateKeep_Implementation(const TArray<bool>& KeepArray)
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->UpdateKeep(KeepArray);
}

void AYachtPlayerController::Server_UpdateScoreTableToAllClient_Implementation(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdateScoreTable(OwnerNumber, SelectedArray, ScoreArray);
	}
}

void AYachtPlayerController::Client_UpdateScoreTable_Implementation(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray)
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->UpdateScoreTableWidget(OwnerNumber, SelectedArray, ScoreArray);
}

void AYachtPlayerController::Server_UpdateSpecialScoreToAllClient_Implementation(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdateSpecialScore(OwnerNumber, SpecialScoreArray);
	}
}

void AYachtPlayerController::Client_UpdateSpecialScore_Implementation(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray)
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->UpdateSpecialScore(OwnerNumber, SpecialScoreArray);
}

void AYachtPlayerController::Server_UpdatePlayerNumberToAllClient_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	int32 WhichPlayerTurn = YachtGameState->GetWhichPlayerTurn();

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdatePlayerNumber(WhichPlayerTurn);
	}
}

void AYachtPlayerController::Client_UpdatePlayerNumber_Implementation(const int32 PlayerNumber)
{
	if (YachtWidget == nullptr) return;

	YachtWidget->UpdateTextBlock_PlayerNumber(PlayerNumber);
	YachtWidget->InitDiceSlotWidget();
}

void AYachtPlayerController::Server_UpdateRemainingTurnToAllClient_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	int32 RemainingTurn = YachtPlayerState->GetRemainingTurn();

	for (TObjectPtr<APlayerState> _PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(_PlayerState->GetOwningController());
		if (!ensure(YachtPlayerController != nullptr)) return;

		YachtPlayerController->Client_UpdateRemainingTurn(RemainingTurn);
	}
}

void AYachtPlayerController::Client_UpdateRemainingTurn_Implementation(const int32 RemainingTurn)
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->UpdateTextBlock_RemainingTurn(RemainingTurn);
}

void AYachtPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	YachtGameState->OnPlayerChanged.AddUObject(this, &AYachtPlayerController::Server_UpdatePlayerNumberToAllClient);

	if (IsLocalPlayerController())
	{
		if (!ensure(YachtWidgetClass != nullptr)) return;
		YachtWidget = CreateWidget<UYachtWidget>(this, YachtWidgetClass);
		if (!ensure(YachtWidget != nullptr)) return;

		TurnOnYachtWidget();
	}
}