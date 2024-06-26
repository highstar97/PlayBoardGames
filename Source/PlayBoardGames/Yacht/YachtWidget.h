#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YachtWidget.generated.h"

class UTextBlock;
class UButton;
class UYachtScoreTableWidget;
class UYachtDiceSlotWidget;
class UYachtAchieveWidget;

UCLASS()
class PLAYBOARDGAMES_API UYachtWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	void SetUp();
	
	void TearDown();

	UFUNCTION()
	void Roll();

	void ShowAchieveWidget(int32 NumOfAchieve, const FString& AchieveScore);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void UpdateYourNumber();

	void UpdatePlayerNumber();

	void UpdateRemainingTurn();

	void UpdateDiceSlotWidget();

	void UpdateScoreTableWidget();

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

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UYachtAchieveWidget* YachtAchieveWidget;
};