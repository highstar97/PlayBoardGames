#include "YachtPredictScoreComponent.h"

#include "YachtGameState.h"

UYachtPredictScoreComponent::UYachtPredictScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UYachtPredictScoreComponent::PredictScore(const TArray<int32>& DiceArray, TArray<int32>& PredictArray)
{
	for (int32 i = 0; i < 6; ++i)
	{
		PredictArray[i] = PredictSingleNumber(i + 1, DiceArray);
	}

	for (int32 i = 6; i < 12; ++i)
	{
		switch (i)
		{
		case (6):
		{
			PredictArray[i] = PredictChoice(DiceArray);
			break;
		}
		case (7):
		{
			PredictArray[i] = Predict4OfAKind(DiceArray);
			break;
		}
		case (8):
		{
			PredictArray[i] = PredictFullHouse(DiceArray);
			break;
		}
		case (9):
		{
			PredictArray[i] = PredictSmallStraight(DiceArray);
			break;
		}
		case (10):
		{
			PredictArray[i] = PredictLargeStraight(DiceArray);
			break;
		}
		case (11):
		{
			PredictArray[i] = PredictYacht(DiceArray);
			break;
		}
		}
	}
}

void UYachtPredictScoreComponent::BeginPlay()
{
	Super::BeginPlay();
}

int32 UYachtPredictScoreComponent::PredictSingleNumber(int32 Number, const TArray<int32>& DiceArray)
{
	int32 Score = 0;
	for (int32 i = 0; i < 5; ++i)
	{
		if (DiceArray[i] == Number)
		{
			Score += Number;
		}
	}
	return Score;
}

int32 UYachtPredictScoreComponent::PredictChoice(const TArray<int32>& DiceArray)
{
	int32 Score = 0;
	for (int32 i = 0; i < 5; ++i)
	{
		Score += DiceArray[i];
	}
	return Score;
}

int32 UYachtPredictScoreComponent::Predict4OfAKind(const TArray<int32>& DiceArray)
{
	TArray<int32> SortedDiceArray = DiceArray;
	SortedDiceArray.Sort();

	if (SortedDiceArray[1] == SortedDiceArray[4])	// SortedDiceArray[1] ~ [4] is same
	{
		return SortedDiceArray[1] * 4;
	}
	else if (SortedDiceArray[0] == SortedDiceArray[3]) // SortedDiceArray[0] ~ [3] is same
	{
		return SortedDiceArray[0] * 4;
	}
	else
	{
		return 0;
	}
}

int32 UYachtPredictScoreComponent::PredictFullHouse(const TArray<int32>& DiceArray)
{
	TArray<int32> SortedDiceArray = DiceArray;
	SortedDiceArray.Sort();

	if (SortedDiceArray[0] == SortedDiceArray[1] && SortedDiceArray[2] == SortedDiceArray[4])
	{
		return SortedDiceArray[0] * 2 + SortedDiceArray[2] * 3;
	}
	else if (SortedDiceArray[0] == SortedDiceArray[2] && SortedDiceArray[3] == SortedDiceArray[4])
	{
		return SortedDiceArray[0] * 3 + SortedDiceArray[3] * 2;
	}
	return 0;
}

int32 UYachtPredictScoreComponent::PredictSmallStraight(const TArray<int32>& DiceArray)
{
	TArray<int32> SortedDiceArray = DiceArray;
	SortedDiceArray.Sort();

	int32 NumOfContinue = 1;
	int32 PrevValue = SortedDiceArray[0];
	for (int32 DiceNumber = 2; DiceNumber <= 5; ++DiceNumber)
	{
		if (SortedDiceArray[DiceNumber - 1] == PrevValue) continue;

		if (SortedDiceArray[DiceNumber - 1] == PrevValue + 1)
		{
			++NumOfContinue;
		}
		else
		{
			NumOfContinue = 1;
		}
		PrevValue = SortedDiceArray[DiceNumber - 1];
	}

	if (NumOfContinue >= 4) return 15;
	return 0;
}

int32 UYachtPredictScoreComponent::PredictLargeStraight(const TArray<int32>& DiceArray)
{
	TArray<int32> SortedDiceArray = DiceArray;
	SortedDiceArray.Sort();

	int32 PrevValue = SortedDiceArray[0];
	for (int32 DiceNumber = 2; DiceNumber <= 5; ++DiceNumber)
	{
		if (SortedDiceArray[DiceNumber - 1] == PrevValue) return 0;

		if (SortedDiceArray[DiceNumber - 1] == PrevValue + 1)
		{
			PrevValue = SortedDiceArray[DiceNumber - 1];
		}
		else
		{
			return 0;
		}
	}
	return 30;
}

int32 UYachtPredictScoreComponent::PredictYacht(const TArray<int32>& DiceArray)
{
	TArray<int32> SortedDiceArray = DiceArray;
	SortedDiceArray.Sort();

	if (SortedDiceArray[0] == SortedDiceArray[4]) return 50;
	return 0;
}