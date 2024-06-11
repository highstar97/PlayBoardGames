#include "YachtPlayerController.h"

#include "YachtGameMode.h"
#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtWidget.h"

AYachtPlayerController::AYachtPlayerController()
{
	static ConstructorHelpers::FClassFinder<UYachtWidget> BP_YachtWidgetClass(TEXT("/Game/Blueprints/Yacht/WBP_YachtWidget"));
	if (BP_YachtWidgetClass.Succeeded())
	{
		YachtWidgetClass = BP_YachtWidgetClass.Class;
	}
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

void AYachtPlayerController::Server_ToggleKeep_Implementation(const int32 Index)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = this->GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	// Check Player Turn
	if (YachtGameState->GetWhichPlayerTurn() != YachtPlayerState->GetPlayerNumber()) return;

	// Keep Dice
	YachtGameState->ToggleKeep(Index);

	YachtGameState->ForceNetUpdate();
}

void AYachtPlayerController::Server_Roll_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = this->GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	// Check Player Turn
	if (YachtGameState->GetWhichPlayerTurn() != YachtPlayerState->GetPlayerNumber()) return;

	// Is My Turn Remaining?
	if (YachtGameState->GetRemainingTurn() <= 0) return;

	// Roll Dice
	YachtGameState->Roll();

	// Predict Score
	YachtGameState->SetbIsPredicting(true);
	YachtGameState->PredictScore();

	// Next Turn;
	YachtGameState->NextTurn();

	YachtGameState->ForceNetUpdate();
	YachtPlayerState->ForceNetUpdate();
}

void AYachtPlayerController::Server_FixScore_Implementation(const int32 PlayerNumber, const int32 Index)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = this->GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	// Check Player Turn
	if (YachtGameState->GetWhichPlayerTurn() != YachtPlayerState->GetPlayerNumber()) return;

	// Check CurrentPlayerTurn != Button's OwnerPlayerNumber
	if (YachtGameState->GetWhichPlayerTurn() != PlayerNumber) return;

	// Need to Roll at least once
	if (YachtGameState->GetRemainingTurn() == YachtGameState->GetMaxTurn()) return;

	// Check PlayerState's FixedArray[Index]
	if (YachtPlayerState->GetFixedArray()[Index] == true) return;

	// Set Fixed Array true
	YachtPlayerState->SetFixedArray(true, Index);

	// Update ScoreArray[Index]
	YachtPlayerState->SetScoreArray(YachtGameState->GetPredictArray()[Index], Index);

	// Update ScoreArray[12]~[14]
	YachtPlayerState->UpdateSpecialScore();

	// Set GameState's bIsPredicting false
	YachtGameState->SetbIsPredicting(false);
	
	// Set Init Keep & Dice Array
	YachtGameState->InitArray();

	// Call GameState's FinishTurn()
	YachtGameState->FinishTurn();

	YachtGameState->ForceNetUpdate();
	YachtPlayerState->ForceNetUpdate();
}

void AYachtPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (!ensure(YachtWidgetClass != nullptr)) return;
		YachtWidget = CreateWidget<UYachtWidget>(this, YachtWidgetClass);
		
		if (!ensure(YachtWidget != nullptr)) return;
		TurnOnYachtWidget();
	}
}