#include "YachtGameState.h"

#include "Net/UnrealNetwork.h"

#include "YachtGameMode.h"
#include "YachtPredictScoreComponent.h"

AYachtGameState::AYachtGameState()
{
	bReplicates = true;
	NetUpdateFrequency = 1.0f;

	bIsPlayer1Turn = true;
	bIsPredicting = false;
	CurrentRound = 1;
	TotalRound = 12;
	RemainingTurn = 3;
	MaxTurn = 3;
	KeepArray.Init(false, 5);
	DiceArray.Init(0, 5);
	PredictArray.Init(-1, 12);
	PredictScoreComponent = CreateDefaultSubobject<UYachtPredictScoreComponent>(TEXT("PredictScoreComponent"));
}

void AYachtGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYachtGameState, bIsPlayer1Turn);
	DOREPLIFETIME(AYachtGameState, bIsPredicting);
	DOREPLIFETIME(AYachtGameState, CurrentRound);
	DOREPLIFETIME(AYachtGameState, RemainingTurn);
	DOREPLIFETIME(AYachtGameState, KeepArray);
	DOREPLIFETIME(AYachtGameState, DiceArray);
	DOREPLIFETIME(AYachtGameState, PredictArray);
}

void AYachtGameState::InitArray()
{
	InitKeepArray();
	InitDiceArray();
}

void AYachtGameState::InitKeepArray()
{
	for (bool& bIsKeep : KeepArray)
	{
		bIsKeep = false;
	}
}

void AYachtGameState::InitDiceArray()
{
	for (int32& Number : DiceArray)
	{
		Number = 0;
	}
}

void AYachtGameState::ToggleKeep(int32 Index)
{
	KeepArray[Index] = !KeepArray[Index];
}

void AYachtGameState::Roll()
{
	for (int32 i = 0; i < DiceArray.Num(); ++i)
	{
		if (KeepArray[i]) continue;

		DiceArray[i] = FMath::RandRange(1, 6);
	}
}

void AYachtGameState::PredictScore()
{
	PredictScoreComponent->PredictScore(DiceArray, PredictArray);
}

void AYachtGameState::NextTurn()
{
	--RemainingTurn;
}

void AYachtGameState::FinishTurn()
{
	// Init RemainingTurn
	RemainingTurn = MaxTurn;

	// Change PlayerTurn
	bIsPlayer1Turn = !bIsPlayer1Turn;

	// if(Player Turn 2 -> 1) : Round Change
	if (bIsPlayer1Turn)
	{
		// if Play All Round -> GameEnd;
		if (++CurrentRound > TotalRound)
		{
			AYachtGameMode* YachtGameMode = Cast<AYachtGameMode>(GetWorld()->GetAuthGameMode());
			if (!ensure(YachtGameMode != nullptr)) return;

			YachtGameMode->EndGame();
		}
	}
}