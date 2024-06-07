#include "YachtWidget.h"

#include "TimerManager.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtPlayerController.h"
#include "YachtScoreTableWidget.h"
#include "YachtDiceSlotWidget.h"

void UYachtWidget::Roll()
{
	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwningPlayer());
	if (!ensure(YachtPlayerController != nullptr)) return;

	YachtPlayerController->Server_Roll();
}

void UYachtWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(Button_Roll != nullptr)) return;
	Button_Roll->OnClicked.AddDynamic(this, &UYachtWidget::Roll);
}

void UYachtWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateYourNumber();

	UpdatePlayerNumber();

	UpdateRemainingTurn();

	UpdateDiceSlotWidget();

	UpdateScoreTableWidget();
}

void UYachtWidget::UpdateYourNumber()
{
	if (!ensure(TextBlock_YourNumber != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = GetOwningPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;
	
	FString TempString = TEXT("You're Player ");
	TempString += FString::FromInt(YachtPlayerState->GetPlayerNumber());

	TextBlock_YourNumber->SetText(FText::FromString(TempString));
}

void UYachtWidget::UpdatePlayerNumber()
{
	if (!ensure(TextBlock_PlayerNumber != nullptr)) return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	FString TempString = TEXT("Player ");
	TempString += FString::FromInt(YachtGameState->GetWhichPlayerTurn());
	TempString += TEXT(" Turn");

	TextBlock_PlayerNumber->SetText(FText::FromString(TempString));
}

void UYachtWidget::UpdateRemainingTurn()
{
	if (!ensure(TextBlock_RemainingTurn != nullptr)) return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	FString TempString = TEXT("Turn ");
	TempString += FString::FromInt(YachtGameState->GetRemainingTurn());
	TempString +=TEXT(" Remain");

	TextBlock_RemainingTurn->SetText(FText::FromString(TempString));
}

void UYachtWidget::UpdateDiceSlotWidget()
{
	if (!ensure(DiceSlotWidget != nullptr)) return;

	DiceSlotWidget->UpdateKeepWidget();
	DiceSlotWidget->UpdateDiceWidget();
}

void UYachtWidget::UpdateScoreTableWidget()
{
	if (!ensure(ScoreTableWidget != nullptr)) return;

	ScoreTableWidget->UpdateScoreWidget();
}