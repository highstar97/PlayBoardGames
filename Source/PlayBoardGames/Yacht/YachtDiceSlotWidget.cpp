#include "YachtDiceSlotWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "YachtPlayerController.h"

void UYachtDiceSlotWidget::InitDiceSlot()
{
	InitNumberArray();
	InitKeepArray();
	InitTextBlockArray();
}

void UYachtDiceSlotWidget::Roll(int32 DiceNumber)
{
	if (KeepArray[DiceNumber - 1] == true)
	{
		return;
	}

	int32 NewValue = FMath::RandRange(1, 6);

	ValueArray[DiceNumber - 1] = NewValue;
}

void UYachtDiceSlotWidget::KeepValue(int32 DiceNumber)
{
	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwningPlayer());
	if (!ensure(YachtPlayerController != nullptr)) return;

	if (!YachtPlayerController->IsPlayerTurn()) return;

	KeepArray[DiceNumber - 1] = !KeepArray[DiceNumber - 1];

	YachtPlayerController->Server_UpdateKeepToAllClient(KeepArray);
}

void UYachtDiceSlotWidget::UpdateTextBlock_Value(const TArray<int32>& _ValueArray)
{
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		TextBlockArray[DiceNumber - 1]->SetText(FText::FromString(FString::FromInt(_ValueArray[DiceNumber - 1])));
	}
}

void UYachtDiceSlotWidget::UpdateTextBlock_Keep(const TArray<bool>& _KeepArray)
{	
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		TextBlockArray[DiceNumber - 1]->SetColorAndOpacity(_KeepArray[DiceNumber - 1] ? Keeping : UnKeeping);
	}
}

void UYachtDiceSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ValueArray.Empty();
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		ValueArray.Add(DiceNumber);
	}

	KeepArray.Empty();
	KeepArray.Init(false, 5);

	TextBlockArray.Empty();
	TextBlockArray.Add(TextBlock_Dice1);
	TextBlockArray.Add(TextBlock_Dice2);
	TextBlockArray.Add(TextBlock_Dice3);
	TextBlockArray.Add(TextBlock_Dice4);
	TextBlockArray.Add(TextBlock_Dice5);

	InitTextBlockArray();

	ButtonArray.Empty();
	ButtonArray.Add(Button_KeepDice1);
	ButtonArray.Add(Button_KeepDice2);
	ButtonArray.Add(Button_KeepDice3);
	ButtonArray.Add(Button_KeepDice4);
	ButtonArray.Add(Button_KeepDice5);

	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		if (!ensure(ButtonArray[DiceNumber - 1] != nullptr)) return;

		SButton* SlateButton = (SButton*)&(ButtonArray[DiceNumber - 1]->TakeWidget().Get());
		SlateButton->SetOnClicked(FOnClicked::CreateLambda([this, DiceNumber]()
			{
				KeepValue(DiceNumber);
				return FReply::Handled();
			}));
	}
}

void UYachtDiceSlotWidget::InitNumberArray()
{
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		ValueArray[DiceNumber - 1] = DiceNumber;
	}
}

void UYachtDiceSlotWidget::InitKeepArray()
{
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		KeepArray[DiceNumber - 1] = false;
		TextBlockArray[DiceNumber - 1]->SetColorAndOpacity(UnKeeping);
	}
}

void UYachtDiceSlotWidget::InitTextBlockArray()
{
	for (int32 DiceNumber = 1; DiceNumber <= 5; ++DiceNumber)
	{
		TextBlockArray[DiceNumber - 1]->SetText(FText::FromString(FString::FromInt(DiceNumber)));
	}
}