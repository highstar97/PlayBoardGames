#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YachtScoreTableWidget.generated.h"

class UTextBlock;
struct FDiceInfo;

UCLASS()
class PLAYBOARDGAMES_API UYachtScoreTableWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/*void PredictScore(TMap<int32, FDiceInfo> DiceMap);

	void UnPredictScore();

	void SetSelected1PArray(int32 index, bool boolean = true);

	void SetSelected2PArray(int32 index, bool boolean = true);

	void UpdateSubTotals();

	void Update35();

	void UpdateTotals();

protected:
	virtual void NativeConstruct() override;

private:
	int32 CheckAces(TMap<int32, int32> DiceMap);
	int32 CheckDoubles(TMap<int32, int32> DiceMap);
	int32 CheckThrees(TMap<int32, int32> DiceMap);
	int32 CheckFours(TMap<int32, int32> DiceMap);
	int32 CheckFives(TMap<int32, int32> DiceMap);
	int32 CheckSixes(TMap<int32, int32> DiceMap);
	int32 CheckChoice(TMap<int32, int32> DiceMap);
	int32 Check4OfAKind(TMap<int32, int32> DiceMap);
	int32 CheckFullHouse(TMap<int32, int32> DiceMap);
	int32 CheckSmallStraight(TMap<int32, int32> DiceMap);
	int32 CheckLargeStraight(TMap<int32, int32> DiceMap);
	int32 CheckYacht(TMap<int32, int32> DiceMap);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PAces;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PDoubles;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PThrees;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PFours;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PFives;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PSixes;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PSubTotals;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1P35;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PChoice;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PYacht;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_1PTotals;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PAces;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PDoubles;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PThrees;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PFours;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PFives;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PSixes;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PSubTotals;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2P35;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PChoice;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2P4OfAKind;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PFullHouse;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PSmallStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PLargeStraight;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PYacht;

	UPROPERTY(VisibleAnywhere, Category = "Score", meta = (BindWidget))
	UTextBlock* TEXT_2PTotals;

private:
	TArray<bool> Selected1PArray;

	TArray<bool> Selected2PArray;

	TArray<int32> Score1PArray;

	TArray<int32> Score2PArray;*/
};