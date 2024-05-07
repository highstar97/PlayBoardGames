#include "YachtWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "YachtGameMode.h"
#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtPlayerController.h"
#include "YachtScoreTableWidget.h"
#include "YachtDiceSlotWidget.h"

void UYachtWidget::Roll()
{
	if (!ensure(DiceSlotWidget != nullptr)) return;

	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwningPlayer());
	if (!ensure(YachtPlayerController != nullptr)) return;
	
	if (!YachtPlayerController->IsPlayerTurn()) return;
	
	if (!YachtPlayerController->IsTurnRemain()) return;

	UnPredictScore();
	for (int32 i = 1; i <= 5; ++i)
	{
		DiceSlotWidget->Roll(i);
	}
	PredictScore();

	YachtPlayerController->Server_UpdateValueToAllClient(DiceSlotWidget->GetValuerArray());

	YachtPlayerController->Server_NextTurn();
}

void UYachtWidget::UpdateValue(const TArray<int32>& ValueArray)
{
	DiceSlotWidget->UpdateTextBlock_Value(ValueArray);
}

void UYachtWidget::UpdateKeep(const TArray<bool>& KeepArray)
{
	DiceSlotWidget->UpdateTextBlock_Keep(KeepArray);
}

void UYachtWidget::UpdateTextBlock_YourNumber(const int32 YourNumber)
{
	FString TempString = TEXT("You're Player ");

	TempString += FString::FromInt(YourNumber);
	TextBlock_YourNumber->SetText(FText::FromString(TempString));
}

void UYachtWidget::UpdateTextBlock_PlayerNumber(const int32 PlayerNumber)
{
	FString TempString = TEXT("Player ");

	TempString += FString::FromInt(PlayerNumber);

	TempString.Append(TEXT(" Turn"));
	TextBlock_PlayerNumber->SetText(FText::FromString(TempString));
}

void UYachtWidget::UpdateTextBlock_RemainingTurn(const int32 RemainingTurn)
{
	FString TempString = TEXT("Turn ");

	TempString += FString::FromInt(RemainingTurn);

	TempString.Append(TEXT(" Remain"));
	TextBlock_RemainingTurn->SetText(FText::FromString(TempString));
}

void UYachtWidget::PredictScore()
{
	//ScoreTableWidget->PredictScore(DiceSlotWidget->GetDiceMap());
}

void UYachtWidget::UnPredictScore()
{
	//ScoreTableWidget->UnPredictScore();
}

void UYachtWidget::InitDiceSlotWidget()
{
	if (!ensure(DiceSlotWidget != nullptr)) return;

	DiceSlotWidget->InitDiceSlot();
}

void UYachtWidget::NativeConstruct()
{
	if (!ensure(Button_Roll != nullptr)) return;
	Button_Roll->OnClicked.AddDynamic(this, &UYachtWidget::Roll);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	UpdateTextBlock_PlayerNumber(YachtGameState->GetWhichPlayerTurn());

	Cast<AYachtPlayerController>(GetOwningPlayer())->Server_UpdateYourNumberToAllClient();
}