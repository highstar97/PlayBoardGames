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
	TArray<bool> GetSelectedArray(int32 OwnerNumber);

	TArray<int32> GetScoreArray(int32 OwnerNumber);

	TArray<int32> GetSpecialScoreArray(int32 OwnerNumber);

	void UpdateScoreTable(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray);

	void UpdateSpecialScore(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray);

	void PredictScore(const TArray<int32>& ValueArray);

protected:
	virtual void NativeConstruct() override;

private:
	void OnClickButton(int32 OwnerNumber, int32 Index);

	void Predict1PScore(const TArray<int32>& ValueArray);

	void UnPredict1PScore();

	void Predict2PScore(const TArray<int32>& ValueArray);

	void UnPredict2PScore();

	int32 PredictOne(const TArray<int32>& ValueArray);

	int32 PredictTwo(const TArray<int32>& ValueArray);

	int32 PredictThree(const TArray<int32>& ValueArray);

	int32 PredictFour(const TArray<int32>& ValueArray);

	int32 PredictFive(const TArray<int32>& ValueArray);

	int32 PredictSix(const TArray<int32>& ValueArray);

	int32 PredictChoice(const TArray<int32>& ValueArray);

	int32 Predict4OfAKind(const TArray<int32>& ValueArray);

	int32 PredictFullHouse(const TArray<int32>& ValueArray);

	int32 PredictSmallStraight(const TArray<int32>& ValueArray);

	int32 PredictLargeStraight(const TArray<int32>& ValueArray);

	int32 PredictYacht(const TArray<int32>& ValueArray);

	int32 CalculateSubTotal(int32 OwnerNumber);

	int32 CalculateBonus(int32 OwnerNumber);

	int32 CalculateTotal(int32 OwnerNumber);

private:
	FSlateColor Fixed = FSlateColor(FColor::Red);
	
	TArray<bool> Selected1PArray;

	TArray<int32> Score1PArray;

	TArray<int32> SpecialScore1PArray;

	TArray<UTextBlock*> TextBlock1PArray;

	TArray<UButton*> Button1PArray;

	TArray<bool> Selected2PArray;

	TArray<int32> Score2PArray;

	TArray<int32> SpecialScore2PArray;

	TArray<UTextBlock*> TextBlock2PArray;

	TArray<UButton*> Button2PArray;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1POne;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PTwo;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PThree;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PFour;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PFive;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PSix;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PSubTotal;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PBonus;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PChoice;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PYacht;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_1PTotal;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2POne;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PTwo;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PThree;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PFour;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PFive;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PSix;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PSubTotal;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PBonus;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PChoice;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PYacht;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TextBlock_2PTotal;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1POne;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PTwo;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PThree;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PFour;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PFive;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PSix;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PChoice;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_1PYacht;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2POne;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PTwo;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PThree;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PFour;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PFive;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PSix;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PChoice;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UButton* Button_2PYacht;
};