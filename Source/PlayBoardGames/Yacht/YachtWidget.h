#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YachtWidget.generated.h"

class UTextBlock;
class UButton;
class UYachtScoreTableWidget;
class UYachtDiceSlotWidget;

UCLASS()
class PLAYBOARDGAMES_API UYachtWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	UFUNCTION()
	void Roll();

	void UpdateValue(const TArray<int32>& ValueArray);

	void UpdateKeep(const TArray<bool>& KeepArray);

	void UpdateScoreTableWidget(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray);

	void UpdateSpecialScore(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray);

	void UpdateTextBlock_YourNumber(const int32 YourNumber);

	void UpdateTextBlock_PlayerNumber(const int32 PlayerNumber);

	void UpdateTextBlock_RemainingTurn(const int32 RemainingTurn);

	void PredictScore();

	void InitDiceSlotWidget();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_YourNumber;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_PlayerNumber;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_RemainingTurn;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UButton* Button_Roll;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UYachtScoreTableWidget* ScoreTableWidget;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UYachtDiceSlotWidget* DiceSlotWidget;
};