#include "YachtDiceSlotWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "YachtGameState.h"
#include "YachtPlayerController.h"

UYachtDiceSlotWidget::UYachtDiceSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TextBlockArray.Empty();
	ButtonArray.Empty();
}

void UYachtDiceSlotWidget::UpdateKeepWidget()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	TArray<bool> KeepArray = YachtGameState->GetKeepArray();
	for (int32 i = 0; i < KeepArray.Num(); ++i)
	{
		if (!ensure(TextBlockArray[i] != nullptr)) return;

		KeepArray[i] == true ? TextBlockArray[i]->SetColorAndOpacity(Color_Keeping) : TextBlockArray[i]->SetColorAndOpacity(Color_UnKeeping);
	}
}

void UYachtDiceSlotWidget::UpdateDiceWidget()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	TArray<int32> DiceArray = YachtGameState->GetDiceArray();
	for (int32 i = 0; i < DiceArray.Num(); ++i)
	{
		if (!ensure(TextBlockArray[i] != nullptr)) return;

		TextBlockArray[i]->SetText(FText::FromString(FString::FromInt(DiceArray[i])));
	}
}

void UYachtDiceSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlockArray.Add(TextBlock_Dice1);
	TextBlockArray.Add(TextBlock_Dice2);
	TextBlockArray.Add(TextBlock_Dice3);
	TextBlockArray.Add(TextBlock_Dice4);
	TextBlockArray.Add(TextBlock_Dice5);

	ButtonArray.Add(Button_KeepDice1);
	ButtonArray.Add(Button_KeepDice2);
	ButtonArray.Add(Button_KeepDice3);
	ButtonArray.Add(Button_KeepDice4);
	ButtonArray.Add(Button_KeepDice5);

	for (int32 i = 0; i < ButtonArray.Num(); ++i)
	{
		if (!ensure(ButtonArray[i] != nullptr)) return;

		SButton* SlateButton = (SButton*)&(ButtonArray[i]->TakeWidget().Get());
		SlateButton->SetOnClicked(FOnClicked::CreateLambda([this, i]()
			{
				OnClicked(i);
				return FReply::Handled();
			}));
	}
}

void UYachtDiceSlotWidget::OnClicked(int32 Index)
{
	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwningPlayer());
	if (!ensure(YachtPlayerController != nullptr)) return;

	YachtPlayerController->Server_ToggleKeep(Index);
}