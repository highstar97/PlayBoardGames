#include "YachtScoreTableWidget.h"

#include "Components/TextBlock.h"

#include "YachtDiceSlotWidget.h"
/*
void UYachtScoreTableWidget::PredictScore(TMap<int32, FDiceInfo> DiceMap)
{
	int32 PlayerNumber = 0;
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	switch (PlayerNumber)
	{
	case(1):
	{
		if (TEXT_1PAces->Text.IsEmpty())
		{
			int32 Score = CheckAces(DiceMap);
			TEXT_1PAces->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[0] = Score;
		}
		if (TEXT_1PDoubles->Text.IsEmpty())
		{
			int32 Score = CheckDoubles(DiceMap);
			TEXT_1PDoubles->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[1] = Score;
		}
		if (TEXT_1PThrees->Text.IsEmpty())
		{
			int32 Score = CheckThrees(DiceMap);
			TEXT_1PThrees->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[2] = Score;
		}
		if (TEXT_1PFours->Text.IsEmpty())
		{
			int32 Score = CheckFours(DiceMap);
			TEXT_1PFours->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[3] = Score;
		}
		if (TEXT_1PFives->Text.IsEmpty())
		{
			int32 Score = CheckFives(DiceMap);
			TEXT_1PFives->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[4] = Score;
		}
		if (TEXT_1PSixes->Text.IsEmpty())
		{
			int32 Score = CheckSixes(DiceMap);
			TEXT_1PSixes->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[5] = Score;
		}
		if (TEXT_1PChoice->Text.IsEmpty())
		{
			int32 Score = CheckChoice(DiceMap);
			TEXT_1PChoice->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[6] = Score;
		}
		if (TEXT_1P4OfAKind->Text.IsEmpty())
		{
			int32 Score = Check4OfAKind(DiceMap);
			TEXT_1P4OfAKind->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[7] = Score;
		}
		if (TEXT_1PFullHouse->Text.IsEmpty())
		{
			int32 Score = CheckFullHouse(DiceMap);
			TEXT_1PFullHouse->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[8] = Score;
		}
		if (TEXT_1PSmallStraight->Text.IsEmpty())
		{
			int32 Score = CheckSmallStraight(DiceMap);
			TEXT_1PSmallStraight->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[9] = Score;
		}
		if (TEXT_1PLargeStraight->Text.IsEmpty())
		{
			int32 Score = CheckLargeStraight(DiceMap);
			TEXT_1PLargeStraight->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[10] = Score;
		}
		if (TEXT_1PYacht->Text.IsEmpty())
		{
			int32 Score = CheckYacht(DiceMap);
			TEXT_1PYacht->SetText(FText::FromString(FString::FromInt(Score)));
			Score1PArray[11] = Score;
		}
		break;
	}
	case(2):
	{
		if (TEXT_2PAces->Text.IsEmpty())
		{
			int32 Score = CheckAces(DiceMap);
			TEXT_2PAces->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[0] = Score;
		}
		if (TEXT_2PDoubles->Text.IsEmpty())
		{
			int32 Score = CheckDoubles(DiceMap);
			TEXT_2PDoubles->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[1] = Score;
		}
		if (TEXT_2PThrees->Text.IsEmpty())
		{
			int32 Score = CheckThrees(DiceMap);
			TEXT_2PThrees->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[2] = Score;
		}
		if (TEXT_2PFours->Text.IsEmpty())
		{
			int32 Score = CheckFours(DiceMap);
			TEXT_2PFours->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[3] = Score;
		}
		if (TEXT_2PFives->Text.IsEmpty())
		{
			int32 Score = CheckFives(DiceMap);
			TEXT_2PFives->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[4] = Score;
		}
		if (TEXT_2PSixes->Text.IsEmpty())
		{
			int32 Score = CheckSixes(DiceMap);
			TEXT_2PSixes->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[5] = Score;
		}
		if (TEXT_2PChoice->Text.IsEmpty())
		{
			int32 Score = CheckChoice(DiceMap);
			TEXT_2PChoice->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[6] = Score;
		}
		if (TEXT_2P4OfAKind->Text.IsEmpty())
		{
			int32 Score = Check4OfAKind(DiceMap);
			TEXT_2P4OfAKind->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[7] = Score;
		}
		if (TEXT_2PFullHouse->Text.IsEmpty())
		{
			int32 Score = CheckFullHouse(DiceMap);
			TEXT_2PFullHouse->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[8] = Score;
		}
		if (TEXT_2PSmallStraight->Text.IsEmpty())
		{
			int32 Score = CheckSmallStraight(DiceMap);
			TEXT_2PSmallStraight->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[9] = Score;
		}
		if (TEXT_2PLargeStraight->Text.IsEmpty())
		{
			int32 Score = CheckLargeStraight(DiceMap);
			TEXT_2PLargeStraight->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[10] = Score;
		}
		if (TEXT_2PYacht->Text.IsEmpty())
		{
			int32 Score = CheckYacht(DiceMap);
			TEXT_2PYacht->SetText(FText::FromString(FString::FromInt(Score)));
			Score2PArray[11] = Score;
		}
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreChartWidget -> PredictScore : PlayerNumber Error"));
		break;
	}
	}
}

void UYachtScoreTableWidget::UnPredictScore()
{
	int32 PlayerNumber = 0;
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	switch (PlayerNumber)
	{
	case(1):
	{
		for (int32 i = 0; i < 12; ++i)
		{
			if (!Selected1PArray[i])
			{
				switch (i)
				{
				case(0):
				{
					TEXT_1PAces->SetText(FText::GetEmpty());
					break;
				}
				case(1):
				{
					TEXT_1PDoubles->SetText(FText::GetEmpty());
					break;
				}
				case(2):
				{
					TEXT_1PThrees->SetText(FText::GetEmpty());
					break;
				}
				case(3):
				{
					TEXT_1PFours->SetText(FText::GetEmpty());
					break;
				}
				case(4):
				{
					TEXT_1PFives->SetText(FText::GetEmpty());
					break;
				}
				case(5):
				{
					TEXT_1PSixes->SetText(FText::GetEmpty());
					break;
				}
				case(6):
				{
					TEXT_1PChoice->SetText(FText::GetEmpty());
					break;
				}
				case(7):
				{
					TEXT_1P4OfAKind->SetText(FText::GetEmpty());
					break;
				}
				case(8):
				{
					TEXT_1PFullHouse->SetText(FText::GetEmpty());
					break;
				}
				case(9):
				{
					TEXT_1PSmallStraight->SetText(FText::GetEmpty());
					break;
				}
				case(10):
				{
					TEXT_1PLargeStraight->SetText(FText::GetEmpty());
					break;
				}
				case(11):
				{
					TEXT_1PYacht->SetText(FText::GetEmpty());
					break;
				}
				}
				Score1PArray[i] = 0;
			}
			else
			{
				switch (i)
				{
				case(0):
				{
					TEXT_1PAces->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(1):
				{
					TEXT_1PDoubles->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(2):
				{
					TEXT_1PThrees->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(3):
				{
					TEXT_1PFours->SetColorAndOpacity(FLinearColor::Red);;
					break;
				}
				case(4):
				{
					TEXT_1PFives->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(5):
				{
					TEXT_1PSixes->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(6):
				{
					TEXT_1PChoice->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(7):
				{
					TEXT_1P4OfAKind->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(8):
				{
					TEXT_1PFullHouse->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(9):
				{
					TEXT_1PSmallStraight->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(10):
				{
					TEXT_1PLargeStraight->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(11):
				{
					TEXT_1PYacht->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				}
			}
		}
		break;
	}
	case(2):
	{
		for (int32 i = 0; i < 12; ++i)
		{
			if (!Selected2PArray[i])
			{
				switch (i)
				{
				case(0):
				{
					TEXT_2PAces->SetText(FText::GetEmpty());
					break;
				}
				case(1):
				{
					TEXT_2PDoubles->SetText(FText::GetEmpty());
					break;
				}
				case(2):
				{
					TEXT_2PThrees->SetText(FText::GetEmpty());
					break;
				}
				case(3):
				{
					TEXT_2PFours->SetText(FText::GetEmpty());
					break;
				}
				case(4):
				{
					TEXT_2PFives->SetText(FText::GetEmpty());
					break;
				}
				case(5):
				{
					TEXT_2PSixes->SetText(FText::GetEmpty());
					break;
				}
				case(6):
				{
					TEXT_2PChoice->SetText(FText::GetEmpty());
					break;
				}
				case(7):
				{
					TEXT_2P4OfAKind->SetText(FText::GetEmpty());
					break;
				}
				case(8):
				{
					TEXT_2PFullHouse->SetText(FText::GetEmpty());
					break;
				}
				case(9):
				{
					TEXT_2PSmallStraight->SetText(FText::GetEmpty());
					break;
				}
				case(10):
				{
					TEXT_2PLargeStraight->SetText(FText::GetEmpty());
					break;
				}
				case(11):
				{
					TEXT_2PYacht->SetText(FText::GetEmpty());
					break;
				}
				}
				Score2PArray[i] = 0;
			}
			else
			{
				switch (i)
				{
				case(0):
				{
					TEXT_2PAces->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(1):
				{
					TEXT_2PDoubles->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(2):
				{
					TEXT_2PThrees->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(3):
				{
					TEXT_2PFours->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(4):
				{
					TEXT_2PFives->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(5):
				{
					TEXT_2PSixes->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(6):
				{
					TEXT_2PChoice->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(7):
				{
					TEXT_2P4OfAKind->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(8):
				{
					TEXT_2PFullHouse->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(9):
				{
					TEXT_2PSmallStraight->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(10):
				{
					TEXT_2PLargeStraight->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				case(11):
				{
					TEXT_2PYacht->SetColorAndOpacity(FLinearColor::Red);
					break;
				}
				}
			}
		}
		break;
	}
	}
	UpdateSubTotals();
	Update35();
	UpdateTotals();
}

void UYachtScoreTableWidget::SetSelected1PArray(int32 index, bool boolean)
{
	int32 PlayerNumber = 0;
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	if (PlayerNumber == 1 && !Selected1PArray[index])
	{
		Selected1PArray[index] = boolean;
		UnPredictScore();
		GameMode->NextPlayer();
	}
	else
	{
		return;
	}
}

void UYachtScoreTableWidget::SetSelected2PArray(int32 index, bool boolean)
{
	int32 PlayerNumber = 0;
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	if (PlayerNumber == 2 && !Selected2PArray[index])
	{
		Selected2PArray[index] = boolean;
		UnPredictScore();
		GameMode->NextPlayer();
	}
	else
	{
		return;
	}
}

void UYachtScoreTableWidget::UpdateSubTotals()
{
	int32 PlayerNumber = 0;
	int32 SubTotals = 0;
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	switch (PlayerNumber)
	{
	case(1):
	{
		if (!TEXT_1PAces->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_1PAces->Text).ToString());
		}
		if (!TEXT_1PDoubles->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_1PDoubles->Text).ToString());
		}
		if (!TEXT_1PThrees->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_1PThrees->Text).ToString());
		}
		if (!TEXT_1PFours->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_1PFours->Text).ToString());
		}
		if (!TEXT_1PFives->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_1PFives->Text).ToString());
		}
		if (!TEXT_1PSixes->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_1PSixes->Text).ToString());
		}
		TEXT_1PSubTotals->SetText(FText::FromString(FString::FromInt(SubTotals)));
		break;
	}
	case(2):
	{
		if (!TEXT_2PAces->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_2PAces->Text).ToString());
		}
		if (!TEXT_2PDoubles->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_2PDoubles->Text).ToString());
		}
		if (!TEXT_2PThrees->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_2PThrees->Text).ToString());
		}
		if (!TEXT_2PFours->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_2PFours->Text).ToString());
		}
		if (!TEXT_2PFives->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_2PFives->Text).ToString());
		}
		if (!TEXT_2PSixes->Text.IsEmpty())
		{
			SubTotals += FCString::Atoi(*(TEXT_2PSixes->Text).ToString());
		}
		TEXT_2PSubTotals->SetText(FText::FromString(FString::FromInt(SubTotals)));
		break;
	}
	}
}

void UYachtScoreTableWidget::Update35()
{
	int32 PlayerNumber = 0;
	FString Bonus = TEXT("35");
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	switch (PlayerNumber)
	{
	case(1):
	{
		if (!TEXT_1PSubTotals->Text.IsEmpty())
		{
			if (FCString::Atoi(*(TEXT_1PSubTotals->Text).ToString()) >= 63)
			{
				TEXT_1P35->SetText(FText::FromString(Bonus));
			}
		}
		break;
	}
	case(2):
	{
		if (!TEXT_2PSubTotals->Text.IsEmpty())
		{
			if (FCString::Atoi(*(TEXT_2PSubTotals->Text).ToString()) >= 63)
			{
				TEXT_2P35->SetText(FText::FromString(Bonus));
			}
		}
		break;
	}
	}
}

void UYachtScoreTableWidget::UpdateTotals()
{
	int32 PlayerNumber = 0;
	int32 Totals = 0;
	AYachtGameModeBase* GameMode = Cast<AYachtGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		PlayerNumber = GameMode->GetPlayer();
	}

	switch (PlayerNumber)
	{
	case(1):
	{
		if (!TEXT_1PSubTotals->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1PSubTotals->Text).ToString());
		}
		if (!TEXT_1P35->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1P35->Text).ToString());
		}
		if (!TEXT_1PChoice->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1PChoice->Text).ToString());
		}
		if (!TEXT_1P4OfAKind->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1P4OfAKind->Text).ToString());
		}
		if (!TEXT_1PFullHouse->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1PFullHouse->Text).ToString());
		}
		if (!TEXT_1PSmallStraight->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1PSmallStraight->Text).ToString());
		}
		if (!TEXT_1PLargeStraight->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1PLargeStraight->Text).ToString());
		}
		if (!TEXT_1PYacht->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_1PYacht->Text).ToString());
		}
		TEXT_1PTotals->SetText(FText::FromString(FString::FromInt(Totals)));
		break;
	}
	case(2):
	{
		if (!TEXT_2PSubTotals->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2PSubTotals->Text).ToString());
		}
		if (!TEXT_2P35->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2P35->Text).ToString());
		}
		if (!TEXT_2PChoice->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2PChoice->Text).ToString());
		}
		if (!TEXT_2P4OfAKind->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2P4OfAKind->Text).ToString());
		}
		if (!TEXT_2PFullHouse->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2PFullHouse->Text).ToString());
		}
		if (!TEXT_2PSmallStraight->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2PSmallStraight->Text).ToString());
		}
		if (!TEXT_2PLargeStraight->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2PLargeStraight->Text).ToString());
		}
		if (!TEXT_2PYacht->Text.IsEmpty())
		{
			Totals += FCString::Atoi(*(TEXT_2PYacht->Text).ToString());
		}
		TEXT_2PTotals->SetText(FText::FromString(FString::FromInt(Totals)));
		break;
	}
	}
}

void UYachtScoreTableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Selected1PArray.Init(false, 12);
	Selected2PArray.Init(false, 12);
	Score1PArray.Init(0, 12);
	Score2PArray.Init(0, 12);
}

int32 UYachtScoreTableWidget::CheckAces(TMap<int32, int32> DiceMap)
{
	return 1 * DiceMap[1];
}

int32 UYachtScoreTableWidget::CheckDoubles(TMap<int32, int32> DiceMap)
{
	return 2 * DiceMap[2];
}

int32 UYachtScoreTableWidget::CheckThrees(TMap<int32, int32> DiceMap)
{
	return 3 * DiceMap[3];
}

int32 UYachtScoreTableWidget::CheckFours(TMap<int32, int32> DiceMap)
{
	return 4 * DiceMap[4];
}

int32 UYachtScoreTableWidget::CheckFives(TMap<int32, int32> DiceMap)
{
	return 5 * DiceMap[5];
}

int32 UYachtScoreTableWidget::CheckSixes(TMap<int32, int32> DiceMap)
{
	return 6 * DiceMap[6];
}

int32 UYachtScoreTableWidget::CheckChoice(TMap<int32, int32> DiceMap)
{
	int32 Temp = 0;
	for (int32 i = 1; i <= 6; ++i)
	{
		Temp += (i * DiceMap[i]);
	}
	return Temp;
}

int32 UYachtScoreTableWidget::Check4OfAKind(TMap<int32, int32> DiceMap)
{
	bool bActive = false;
	for (int32 i = 1; i <= 6; ++i)
	{
		if (DiceMap[i] == 4)
		{
			bActive = true;
		}
	}

	if (bActive)
	{
		int32 Temp = 0;
		for (int32 i = 1; i <= 6; ++i)
		{
			Temp += (i * DiceMap[i]);
		}
		return Temp;
	}
	else
	{
		return 0;
	}
}

int32 UYachtScoreTableWidget::CheckFullHouse(TMap<int32, int32> DiceMap)
{
	bool bHas2Card = false;
	bool bHas3Card = false;
	for (int32 i = 1; i <= 6; ++i)
	{
		if (DiceMap[i] == 2)
		{
			bHas2Card = true;
		}
		if (DiceMap[i] == 3)
		{
			bHas3Card = true;
		}
	}

	if (bHas2Card && bHas3Card)
	{
		int32 Temp = 0;
		for (int32 i = 1; i <= 6; ++i)
		{
			Temp += (i * DiceMap[i]);
		}
		return Temp;
	}
	else
	{
		return 0;
	}
}

int32 UYachtScoreTableWidget::CheckSmallStraight(TMap<int32, int32> DiceMap)
{
	bool bContinuous = false;
	int32 MaxCount = 0;
	int32 Count = 0;
	for (int32 i = 1; i <= 6; ++i)
	{
		if (DiceMap[i] > 0)
		{
			if (MaxCount < ++Count)
			{
				MaxCount = Count;
			}
		}
		else
		{
			Count = 0;
		}
	}

	MaxCount >= 4 ? bContinuous = true : bContinuous = false;

	if (bContinuous)
	{
		return 15;
	}
	else
	{
		return 0;
	}
}

int32 UYachtScoreTableWidget::CheckLargeStraight(TMap<int32, int32> DiceMap)
{
	bool bContinuous = false;
	int32 MaxCount = 0;
	int32 Count = 0;
	for (int32 i = 1; i <= 6; ++i)
	{
		if (DiceMap[i] > 0)
		{
			if (MaxCount < ++Count)
			{
				MaxCount = Count;
			}
		}
		else
		{
			Count = 0;
		}
	}

	MaxCount >= 5 ? bContinuous = true : bContinuous = false;

	if (bContinuous)
	{
		return 30;
	}
	else
	{
		return 0;
	}
}

int32 UYachtScoreTableWidget::CheckYacht(TMap<int32, int32> DiceMap)
{
	bool bActive = false;
	for (int32 i = 1; i <= 6; ++i)
	{
		if (DiceMap[i] == 5)
		{
			bActive = true;
		}
	}

	if (bActive)
	{
		return 50;
	}
	else
	{
		return 0;
	}
}
*/