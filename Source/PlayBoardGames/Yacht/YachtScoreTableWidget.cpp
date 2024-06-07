#include "YachtScoreTableWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtPlayerController.h"

UYachtScoreTableWidget::UYachtScoreTableWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TextBlock1PArray.Empty();
	Button1PArray.Empty();
	TextBlock2PArray.Empty();
	Button2PArray.Empty();
}

void UYachtScoreTableWidget::UpdateScoreWidget()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	const bool& bIsPredicting = YachtGameState->GetbIsPredicting();

	const int32& CurrentTurnPlayerNumber = YachtGameState->GetWhichPlayerTurn();

	const TArray<int32>& PredictArray = YachtGameState->GetPredictArray();

	for (TObjectPtr<APlayerState> PlayerState : YachtGameState->PlayerArray)
	{
		AYachtPlayerState* YachtPlayerState = Cast<AYachtPlayerState>(PlayerState);
		if (!ensure(YachtPlayerState != nullptr)) return;

		const int32& PlayerNumber = YachtPlayerState->GetPlayerNumber();

		const TArray<bool>& FixedArray = YachtPlayerState->GetFixedArray();

		const TArray<int32>& ScoreArray = YachtPlayerState->GetScoreArray();

		const bool& bShowPredictScore = CurrentTurnPlayerNumber == PlayerNumber && bIsPredicting;

		const TArray<UTextBlock*>& TextBlockArray = PlayerNumber == 1 ? TextBlock1PArray : TextBlock2PArray;

		for (int32 i = 0; i < 12; ++i)
		{
			if (FixedArray[i])
			{
				TextBlockArray[i]->SetText(FText::FromString(FString::FromInt(ScoreArray[i])));
				TextBlockArray[i]->SetColorAndOpacity(Color_Fixed);
			}
			else
			{
				TextBlockArray[i]->SetText(bShowPredictScore ? FText::FromString(FString::FromInt(PredictArray[i])) : FText::GetEmpty());
				TextBlockArray[i]->SetColorAndOpacity(Color_UnFixed);
			}
		}

		TextBlockArray[12]->SetText(FText::FromString(FString::FromInt(ScoreArray[12]) + TEXT("/63")));
		for (int32 i = 13; i < 15; ++i)
		{
			TextBlockArray[i]->SetText(FText::FromString(FString::FromInt(ScoreArray[i])));
		}
	}

	/*
	AYachtPlayerState* YachtPlayerState = GetOwningPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	bool bIsPredicting = YachtGameState->GetbIsPredicting();

	int32 CurrentTurnPlayerNumber = YachtGameState->GetWhichPlayerTurn();

	const TArray<int32> PredictArray = YachtGameState->GetPredictArray();

	const TArray<bool> FixedArray = YachtPlayerState->GetFixedArray();

	const TArray<int32> ScoreArray = YachtPlayerState->GetScoreArray();

	for (int32 PlayerNumber = 1; PlayerNumber <= 2; ++PlayerNumber)
	{
		const TArray<UTextBlock*>& TextBlockArray = PlayerNumber == 1 ? TextBlock1PArray : TextBlock2PArray;

		for (int32 i = 0; i < 12; ++i)
		{
			if (FixedArray[i] == true)
			{
				TextBlockArray[i]->SetText(FText::FromString(FString::FromInt(ScoreArray[i])));
				TextBlockArray[i]->SetColorAndOpacity(ColorFixed);
			}
			else if (PlayerNumber == CurrentTurnPlayerNumber)
			{
				FText InputText = bIsPredicting ? FText::FromString(FString::FromInt(PredictArray[i])) : FText::GetEmpty();
				TextBlockArray[i]->SetText(InputText);
			}
		}

		if (PlayerNumber == CurrentTurnPlayerNumber)
		{
			TextBlockArray[12]->SetText(FText::FromString(FString::FromInt(ScoreArray[12]) + TEXT("/63")));
			// TextBlockArray[12]->SetColorAndOpacity(ColorFixed);

			for (int32 i = 13; i < 15; ++i)
			{
				TextBlockArray[i]->SetText(FText::FromString(FString::FromInt(ScoreArray[i])));
				// TextBlockArray[i]->SetColorAndOpacity(ColorFixed);
			}
		}
	}
	*/
}

void UYachtScoreTableWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
	TextBlock1PArray.Add(TextBlock_1PSubTotal);
	TextBlock1PArray.Add(TextBlock_1PBonus);
	TextBlock1PArray.Add(TextBlock_1PTotal);

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
	TextBlock2PArray.Add(TextBlock_2PSubTotal);
	TextBlock2PArray.Add(TextBlock_2PBonus);
	TextBlock2PArray.Add(TextBlock_2PTotal);

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

	SButton* SlateButton;

	for (int32 i = 0; i < 12; ++i)
	{
		if (!ensure(Button1PArray[i] != nullptr)) return;
		
		SlateButton = (SButton*)&(Button1PArray[i]->TakeWidget().Get());
		SlateButton->SetOnClicked(FOnClicked::CreateLambda([this, i]()
			{
				OnClickButton(1, i);
				return FReply::Handled();
			}));
		
		if (!ensure(Button2PArray[i] != nullptr)) return;

		SlateButton = (SButton*)&(Button2PArray[i]->TakeWidget().Get());
		SlateButton->SetOnClicked(FOnClicked::CreateLambda([this, i]()
			{
				OnClickButton(2, i);
				return FReply::Handled();
			}));
	}
}

void UYachtScoreTableWidget::OnClickButton(int32 PlayerNumber, int32 Index)
{
	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwningPlayer());
	if (!ensure(YachtPlayerController != nullptr)) return;

	YachtPlayerController->Server_FixScore(PlayerNumber, Index);
}