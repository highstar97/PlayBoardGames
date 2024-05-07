#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YachtDiceSlotWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class PLAYBOARDGAMES_API UYachtDiceSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	TArray<int32> GetValuerArray() { return ValueArray; }

	TArray<bool> GetKeepArray() { return KeepArray; }

	void InitDiceSlot();

	void Roll(int32 DiceNumber);

	void KeepValue(int32 DiceNumber);

	void UpdateTextBlock_Value(const TArray<int32>& _ValueArray);

	void UpdateTextBlock_Keep(const TArray<bool>& _KeepArray);

protected:
	virtual void NativeConstruct() override;

private:
	void InitNumberArray();

	void InitKeepArray();

	void InitTextBlockArray();

private:
	UPROPERTY(VisibleAnywhere, Category = "Dice", meta = (AllowPrivateAccess = true))
	TArray<int32> ValueArray;

	UPROPERTY(VisibleAnywhere, Category = "Dice", meta = (AllowPrivateAccess = true))
	TArray<bool> KeepArray;

	UPROPERTY(VisibleAnywhere, Category = "Dice", meta = (AllowPrivateAccess = true))
	TArray<UTextBlock*> TextBlockArray;

	UPROPERTY(VisibleAnywhere, Category = "Dice", meta = (AllowPrivateAccess = true))
	TArray<UButton*> ButtonArray;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_Dice1;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_Dice2;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_Dice3;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_Dice4;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UTextBlock* TextBlock_Dice5;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UButton* Button_KeepDice1;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UButton* Button_KeepDice2;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UButton* Button_KeepDice3;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UButton* Button_KeepDice4;

	UPROPERTY(VisibleAnywhere, Category = "Playing", meta = (BindWidget))
	UButton* Button_KeepDice5;

	FSlateColor Keeping = FSlateColor(FColor::Red);

	FSlateColor UnKeeping = FSlateColor(FColor::White);
};