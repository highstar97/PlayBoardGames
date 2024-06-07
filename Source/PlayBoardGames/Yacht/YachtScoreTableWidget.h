#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YachtScoreTableWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class PLAYBOARDGAMES_API UYachtScoreTableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UYachtScoreTableWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateScoreWidget();

protected:
	virtual void NativeConstruct() override;

private:
	void OnClickButton(int32 PlayerNumber, int32 Index);

private:
	FSlateColor Color_Fixed = FSlateColor(FColor::Red);

	FSlateColor Color_UnFixed = FSlateColor(FColor::White);

	UPROPERTY(VisibleAnywhere, Category = "1P Text")
	TArray<UTextBlock*> TextBlock1PArray;

	UPROPERTY(VisibleAnywhere, Category = "1P Button")
	TArray<UButton*> Button1PArray;

	UPROPERTY(VisibleAnywhere, Category = "2P Text")
	TArray<UTextBlock*> TextBlock2PArray;

	UPROPERTY(VisibleAnywhere, Category = "2P Button")
	TArray<UButton*> Button2PArray;

private:
	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1POne;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PTwo;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PThree;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PFour;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PFive;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PSix;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PSubTotal;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PBonus;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PChoice;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PYacht;

	UPROPERTY(VisibleAnywhere, Category = "1P Text", meta = (BindWidget))
	UTextBlock* TextBlock_1PTotal;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2POne;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PTwo;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PThree;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PFour;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PFive;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PSix;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PSubTotal;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PBonus;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PChoice;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PYacht;

	UPROPERTY(VisibleAnywhere, Category = "2P Text", meta = (BindWidget))
	UTextBlock* TextBlock_2PTotal;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1POne;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PTwo;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PThree;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PFour;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PFive;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PSix;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PChoice;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "1P Button", meta = (BindWidget))
	UButton* Button_1PYacht;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2POne;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PTwo;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PThree;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PFour;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PFive;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PSix;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PChoice;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "2P Button", meta = (BindWidget))
	UButton* Button_2PYacht;
};