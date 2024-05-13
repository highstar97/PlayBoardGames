#include "YachtScoreTableWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "YachtPlayerState.h"
#include "YachtPlayerController.h"
#include "YachtDiceSlotWidget.h"

TArray<bool> UYachtScoreTableWidget::GetSelectedArray(int32 OwnerNumber)
{
	if (OwnerNumber == 1)
		return Selected1PArray;
	return Selected2PArray;
}

TArray<int32> UYachtScoreTableWidget::GetScoreArray(int32 OwnerNumber)
{
	if (OwnerNumber == 1)
		return Score1PArray;
	return Score2PArray;
}

TArray<int32> UYachtScoreTableWidget::GetSpecialScoreArray(int32 OwnerNumber)
{
	if (OwnerNumber == 1)
		return SpecialScore1PArray;
	return SpecialScore2PArray;
}

void UYachtScoreTableWidget::UpdateScoreTable(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray)
{
	for (int32 i = 0; i < 12; ++i)
	{
		if (OwnerNumber == 1)
		{
			TextBlock1PArray[i]->SetText(ScoreArray[i] == -1 ? FText::GetEmpty() : FText::FromString(FString::FromInt(ScoreArray[i])));
			if (SelectedArray[i])
			{
				TextBlock1PArray[i]->SetColorAndOpacity(Fixed);
			}
		}
		else
		{
			TextBlock2PArray[i]->SetText(ScoreArray[i] == -1 ? FText::GetEmpty() : FText::FromString(FString::FromInt(ScoreArray[i])));
			if (SelectedArray[i])
			{
				TextBlock2PArray[i]->SetColorAndOpacity(Fixed);
			}
		}
	}
}

void UYachtScoreTableWidget::UpdateSpecialScore(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray)
{	
	if (OwnerNumber == 1)
	{
		TextBlock_1PSubTotal->SetText(FText::FromString(FString::FromInt(SpecialScoreArray[0]) + TEXT("/63")));
		TextBlock_1PSubTotal->SetColorAndOpacity(Fixed);

		TextBlock_1PBonus->SetText(FText::FromString(FString::FromInt(SpecialScoreArray[1])));
		TextBlock_1PBonus->SetColorAndOpacity(Fixed);

		TextBlock_1PTotal->SetText(FText::FromString(FString::FromInt(SpecialScoreArray[2])));
		TextBlock_1PTotal->SetColorAndOpacity(Fixed);
	}
	else
	{
		TextBlock_2PSubTotal->SetText(FText::FromString(FString::FromInt(SpecialScoreArray[0]) + TEXT("/63")));
		TextBlock_2PSubTotal->SetColorAndOpacity(Fixed);

		TextBlock_2PBonus->SetText(FText::FromString(FString::FromInt(SpecialScoreArray[1])));
		TextBlock_2PBonus->SetColorAndOpacity(Fixed);

		TextBlock_2PTotal->SetText(FText::FromString(FString::FromInt(SpecialScoreArray[2])));
		TextBlock_2PTotal->SetColorAndOpacity(Fixed);
	}
}

void UYachtScoreTableWidget::PredictScore(const TArray<int32>& ValueArray)
{
	AYachtPlayerState* YachtPlayerState = GetOwningPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	if (YachtPlayerState->GetPlayerNumber() == 1)
	{
		Predict1PScore(ValueArray);
	}
	else
	{
		Predict2PScore(ValueArray);
	}
}

void UYachtScoreTableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Selected1PArray.Init(false, 12);

	Score1PArray.Init(0, 12);

	SpecialScore1PArray.Init(0, 3);

	TextBlock1PArray.Empty();
	TextBlock1PArray.Add(TextBlock_1POne);
	TextBlock1PArray.Add(TextBlock_1PTwo);
	TextBlock1PArray.Add(TextBlock_1PThree);
	TextBlock1PArray.Add(TextBlock_1PFour);
	TextBlock1PArray.Add(TextBlock_1PFive);
	TextBlock1PArray.Add(TextBlock_1PSix);
	TextBlock1PArray.Add(TextBlock_1PChoice);
	TextBlock1PArray.Add(TextBlock_1P4OfAKind);
	TextBlock1PArray.Add(TextBlock_1PFullHouse);
	TextBlock1PArray.Add(TextBlock_1PSmallStraight);
	TextBlock1PArray.Add(TextBlock_1PLargeStraight);
	TextBlock1PArray.Add(TextBlock_1PYacht);

	Button1PArray.Empty();
	Button1PArray.Add(Button_1POne);
	Button1PArray.Add(Button_1PTwo);
	Button1PArray.Add(Button_1PThree);
	Button1PArray.Add(Button_1PFour);
	Button1PArray.Add(Button_1PFive);
	Button1PArray.Add(Button_1PSix);
	Button1PArray.Add(Button_1PChoice);
	Button1PArray.Add(Button_1P4OfAKind);
	Button1PArray.Add(Button_1PFullHouse);
	Button1PArray.Add(Button_1PSmallStraight);
	Button1PArray.Add(Button_1PLargeStraight);
	Button1PArray.Add(Button_1PYacht);

	for (int32 i = 0; i < 12; ++i)
	{
		if (!ensure(Button1PArray[i] != nullptr)) return;

		SButton* SlateButton = (SButton*)&(Button1PArray[i]->TakeWidget().Get());
		SlateButton->SetOnClicked(FOnClicked::CreateLambda([this, i]()
			{
				OnClickButton(1, i);
				return FReply::Handled();
			}));
	}

	Selected2PArray.Init(false, 12);

	Score2PArray.Init(0, 12);

	SpecialScore2PArray.Init(0, 3);

	TextBlock2PArray.Empty();
	TextBlock2PArray.Add(TextBlock_2POne);
	TextBlock2PArray.Add(TextBlock_2PTwo);
	TextBlock2PArray.Add(TextBlock_2PThree);
	TextBlock2PArray.Add(TextBlock_2PFour);
	TextBlock2PArray.Add(TextBlock_2PFive);
	TextBlock2PArray.Add(TextBlock_2PSix);
	TextBlock2PArray.Add(TextBlock_2PChoice);
	TextBlock2PArray.Add(TextBlock_2P4OfAKind);
	TextBlock2PArray.Add(TextBlock_2PFullHouse);
	TextBlock2PArray.Add(TextBlock_2PSmallStraight);
	TextBlock2PArray.Add(TextBlock_2PLargeStraight);
	TextBlock2PArray.Add(TextBlock_2PYacht);

	Button2PArray.Empty();
	Button2PArray.Add(Button_2POne);
	Button2PArray.Add(Button_2PTwo);
	Button2PArray.Add(Button_2PThree);
	Button2PArray.Add(Button_2PFour);
	Button2PArray.Add(Button_2PFive);
	Button2PArray.Add(Button_2PSix);
	Button2PArray.Add(Button_2PChoice);
	Button2PArray.Add(Button_2P4OfAKind);
	Button2PArray.Add(Button_2PFullHouse);
	Button2PArray.Add(Button_2PSmallStraight);
	Button2PArray.Add(Button_2PLargeStraight);
	Button2PArray.Add(Button_2PYacht);

	for (int32 i = 0; i < 12; ++i)
	{
		if (!ensure(Button1PArray[i] != nullptr)) return;

		SButton* SlateButton = (SButton*)&(Button2PArray[i]->TakeWidget().Get());
		SlateButton->SetOnClicked(FOnClicked::CreateLambda([this, i]()
			{
				OnClickButton(2, i);
				return FReply::Handled();
			}));
	}
}

void UYachtScoreTableWidget::OnClickButton(int32 OwnerNumber, int32 Index)
{
	if (GetSelectedArray(OwnerNumber)[Index]) return;

	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwningPlayer());
	if (!ensure(YachtPlayerController != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = GetOwningPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	if (YachtPlayerState->GetRemainingTurn() == 3) return;	// Must roll at least once.

	if (OwnerNumber == 1)
	{
		Selected1PArray[Index] = true;
		UnPredict1PScore();

		SpecialScore1PArray[0] = CalculateSubTotal(OwnerNumber);
		SpecialScore1PArray[1] = CalculateBonus(OwnerNumber);
		SpecialScore1PArray[2] = CalculateTotal(OwnerNumber);
	}
	else
	{
		Selected2PArray[Index] = true;
		UnPredict2PScore();

		SpecialScore2PArray[0] = CalculateSubTotal(OwnerNumber);
		SpecialScore2PArray[1] = CalculateBonus(OwnerNumber);
		SpecialScore2PArray[2] = CalculateTotal(OwnerNumber);
	}

	YachtPlayerController->Server_UpdateScoreTableToAllClient(OwnerNumber, GetSelectedArray(OwnerNumber), GetScoreArray(OwnerNumber));

	YachtPlayerController->Server_UpdateSpecialScoreToAllClient(OwnerNumber, GetSpecialScoreArray(OwnerNumber));

	YachtPlayerController->Server_FinishTurn();
}

void UYachtScoreTableWidget::Predict1PScore(const TArray<int32>& ValueArray)
{
	for (int32 i = 0; i < 12; ++i)
	{
		if (Selected1PArray[i]) continue;

		int32 Score = -1;
		switch (i)
		{
		case (0):
		{
			Score = PredictOne(ValueArray);
			break;
		}
		case (1):
		{
			Score = PredictTwo(ValueArray);
			break;
		}
		case (2):
		{
			Score = PredictThree(ValueArray);
			break;
		}
		case (3):
		{
			Score = PredictFour(ValueArray);
			break;
		}
		case (4):
		{
			Score = PredictFive(ValueArray);
			break;
		}
		case (5):
		{
			Score = PredictSix(ValueArray);
			break;
		}
		case (6):
		{
			Score = PredictChoice(ValueArray);
			break;
		}
		case (7):
		{
			Score = Predict4OfAKind(ValueArray);
			break;
		}
		case (8):
		{
			Score = PredictFullHouse(ValueArray);
			break;
		}
		case (9):
		{
			Score = PredictSmallStraight(ValueArray);
			break;
		}
		case (10):
		{
			Score = PredictLargeStraight(ValueArray);
			break;
		}
		case (11):
		{
			Score = PredictYacht(ValueArray);
			break;
		}
		}
		Score1PArray[i] = Score;
	}
}

void UYachtScoreTableWidget::UnPredict1PScore()
{
	for (int32 i = 0; i < 12; ++i)
	{
		if (Selected1PArray[i]) continue;
		Score1PArray[i] = -1;
	}
}

void UYachtScoreTableWidget::Predict2PScore(const TArray<int32>& ValueArray)
{
	for (int32 i = 0; i < 12; ++i)
	{
		if (Selected2PArray[i]) continue;

		int32 Score = -1;
		switch (i)
		{
		case (0):
		{
			Score = PredictOne(ValueArray);
			break;
		}
		case (1):
		{
			Score = PredictTwo(ValueArray);
			break;
		}
		case (2):
		{
			Score = PredictThree(ValueArray);
			break;
		}
		case (3):
		{
			Score = PredictFour(ValueArray);
			break;
		}
		case (4):
		{
			Score = PredictFive(ValueArray);
			break;
		}
		case (5):
		{
			Score = PredictSix(ValueArray);
			break;
		}
		case (6):
		{
			Score = PredictChoice(ValueArray);
			break;
		}
		case (7):
		{
			Score = Predict4OfAKind(ValueArray);
			break;
		}
		case (8):
		{
			Score = PredictFullHouse(ValueArray);
			break;
		}
		case (9):
		{
			Score = PredictSmallStraight(ValueArray);
			break;
		}
		case (10):
		{
			Score = PredictLargeStraight(ValueArray);
			break;
		}
		case (11):
		{
			Score = PredictYacht(ValueArray);
			break;
		}
		}
		Score2PArray[i] = Score;
	}
}

void UYachtScoreTableWidget::UnPredict2PScore()
{
	for (int32 i = 0; i < 12; ++i)
	{
		if (Selected2PArray[i]) continue;
		Score2PArray[i] = -1;
	}
}

int32  UYachtScoreTableWidget::PredictOne(const TArray<int32>& ValueArray)
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (ValueArray[DiceNumber - 1] == 1)
		{
			Score += 1;
		}
	}
	return Score;
}

int32  UYachtScoreTableWidget::PredictTwo(const TArray<int32>& ValueArray)
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (ValueArray[DiceNumber - 1] == 2)
		{
			Score += 2;
		}
	}
	return Score;
}

int32  UYachtScoreTableWidget::PredictThree(const TArray<int32>& ValueArray)
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (ValueArray[DiceNumber - 1] == 3)
		{
			Score += 3;
		}
	}
	return Score;
}

int32  UYachtScoreTableWidget::PredictFour(const TArray<int32>& ValueArray) 
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (ValueArray[DiceNumber - 1] == 4)
		{
			Score += 4;
		}
	}
	return Score;
}

int32  UYachtScoreTableWidget::PredictFive(const TArray<int32>& ValueArray)
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (ValueArray[DiceNumber - 1] == 5)
		{
			Score += 5;
		}
	}
	return Score;
}

int32  UYachtScoreTableWidget::PredictSix(const TArray<int32>& ValueArray)
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (ValueArray[DiceNumber - 1] == 6)
		{
			Score += 6;
		}
	}
	return Score;
}

int32  UYachtScoreTableWidget::PredictChoice(const TArray<int32>& ValueArray)
{
	int32 Score = 0;
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		Score += ValueArray[DiceNumber - 1];
	}
	return Score;
}

int32  UYachtScoreTableWidget::Predict4OfAKind(const TArray<int32>& ValueArray)
{
	TArray<int32> SortedValueArray = ValueArray;
	SortedValueArray.Sort();

	if (SortedValueArray[1] == SortedValueArray[4])	// SortedValueArray[1] ~ [4] is same
	{
		return SortedValueArray[1] * 4;
	}
	else if (SortedValueArray[0] == SortedValueArray[3]) // SortedValueArray[0] ~ [3] is same
	{
		return SortedValueArray[0] * 4;
	}
	else
	{
		return 0;
	}
}

int32  UYachtScoreTableWidget::PredictFullHouse(const TArray<int32>& ValueArray)
{
	TArray<int32> SortedValueArray = ValueArray;
	SortedValueArray.Sort();

	if (SortedValueArray[0] == SortedValueArray[1] && SortedValueArray[2] == SortedValueArray[4])
	{
		return SortedValueArray[0] * 2 + SortedValueArray[2] * 3;
	}
	else if (SortedValueArray[0] == SortedValueArray[2] && SortedValueArray[3] == SortedValueArray[4])
	{
		return SortedValueArray[0] * 3 + SortedValueArray[3] * 2;
	}
	return 0;
}

int32  UYachtScoreTableWidget::PredictSmallStraight(const TArray<int32>& ValueArray)
{
	TArray<int32> SortedValueArray = ValueArray;
	SortedValueArray.Sort();

	int32 NumOfContinue = 1;
	int32 PrevValue = SortedValueArray[0];
	for (int32 DiceNumber = 2; DiceNumber <= 5; ++DiceNumber)
	{
		if (SortedValueArray[DiceNumber - 1] == PrevValue) continue;

		if (SortedValueArray[DiceNumber - 1] == PrevValue + 1)
		{
			++NumOfContinue;			
		}
		else
		{
			NumOfContinue = 1;
		}
		PrevValue = SortedValueArray[DiceNumber - 1];
	}

	if (NumOfContinue >= 4) return 15;
	return 0;
}

int32  UYachtScoreTableWidget::PredictLargeStraight(const TArray<int32>& ValueArray)
{
	TArray<int32> SortedValueArray = ValueArray;
	SortedValueArray.Sort();

	int32 PrevValue = SortedValueArray[0];
	for (int32 DiceNumber = 2; DiceNumber <= 5; ++DiceNumber)
	{
		if (SortedValueArray[DiceNumber - 1] == PrevValue) return 0;

		if (SortedValueArray[DiceNumber - 1] == PrevValue + 1)
		{
			PrevValue = SortedValueArray[DiceNumber - 1];
		}
		else
		{
			return 0;
		}
	}
	return 30;
}

int32  UYachtScoreTableWidget::PredictYacht(const TArray<int32>& ValueArray)
{
	TArray<int32> SortedValueArray = ValueArray;
	SortedValueArray.Sort();

	if (SortedValueArray[0] == SortedValueArray[4]) return 50;
	return 0;
}

int32 UYachtScoreTableWidget::CalculateSubTotal(int32 OwnerNumber)
{
	int32 SubTotal = 0;	
	for (int32 i = 0; i < 6; ++i)
	{
		if(GetScoreArray(OwnerNumber)[i] != -1)
			SubTotal += GetScoreArray(OwnerNumber)[i];
	}
	return SubTotal;
}

int32 UYachtScoreTableWidget::CalculateBonus(int32 OwnerNumber)
{
	int32 Bonus = 35;
	if (GetSpecialScoreArray(OwnerNumber)[0] >= 63) return Bonus;
	return 0;
}

int32 UYachtScoreTableWidget::CalculateTotal(int32 OwnerNumber)
{
	int32 Total = GetSpecialScoreArray(OwnerNumber)[0] + GetSpecialScoreArray(OwnerNumber)[1];
	for (int32 i = 6; i < 12; ++i)
	{
		if (GetScoreArray(OwnerNumber)[i] != -1)
			Total += GetScoreArray(OwnerNumber)[i];
	}
	return Total;
}