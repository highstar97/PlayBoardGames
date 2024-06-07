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
	UYachtDiceSlotWidget(const FObjectInitializer &ObjectInitializer);

public:
	void UpdateKeepWidget();

	void UpdateDiceWidget();

protected:
	virtual void NativeConstruct() override;

private:
	void OnClicked(int32 Index);

private:
	FSlateColor Color_Keeping = FSlateColor(FColor::Red);

	FSlateColor Color_UnKeeping = FSlateColor(FColor::White);
	
	UPROPERTY(VisibleAnywhere, Category = "Text")
	TArray<UTextBlock*> TextBlockArray;

	UPROPERTY(VisibleAnywhere, Category = "Button")
	TArray<UButton*> ButtonArray;

private:
	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_Dice1;

	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_Dice2;

	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_Dice3;

	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_Dice4;

	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_Dice5;

	UPROPERTY(VisibleAnywhere, Category = "Button", meta = (BindWidget))
	UButton* Button_KeepDice1;

	UPROPERTY(VisibleAnywhere, Category = "Button", meta = (BindWidget))
	UButton* Button_KeepDice2;

	UPROPERTY(VisibleAnywhere, Category = "Button", meta = (BindWidget))
	UButton* Button_KeepDice3;

	UPROPERTY(VisibleAnywhere, Category = "Button", meta = (BindWidget))
	UButton* Button_KeepDice4;

	UPROPERTY(VisibleAnywhere, Category = "Button", meta = (BindWidget))
	UButton* Button_KeepDice5;
};