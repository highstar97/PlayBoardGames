#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YachtPredictScoreComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYBOARDGAMES_API UYachtPredictScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYachtPredictScoreComponent();

public:
	void PredictScore(const TArray<int32>& DiceArray, TArray<int32>& PredictArray);

protected:
	virtual void BeginPlay() override;

private:
	int32 PredictSingleNumber(int32 Number, const TArray<int32>& DiceArray);

	int32 PredictChoice(const TArray<int32>& DiceArray);

	int32 Predict4OfAKind(const TArray<int32>& DiceArray);

	int32 PredictFullHouse(const TArray<int32>& DiceArray);

	int32 PredictSmallStraight(const TArray<int32>& DiceArray);

	int32 PredictLargeStraight(const TArray<int32>& DiceArray);

	int32 PredictYacht(const TArray<int32>& DiceArray);
};