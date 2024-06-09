#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "YachtGameState.generated.h"

class UYachtPredictScoreComponent;

UCLASS()
class PLAYBOARDGAMES_API AYachtGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AYachtGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	bool GetbIsPredicting() const { return bIsPredicting; }
	void SetbIsPredicting(const bool _bIsPredicting) { bIsPredicting = _bIsPredicting; }

	int32 GetWhichPlayerTurn() { if (bIsPlayer1Turn) return 1; else return 2; }
	
	int32 GetRemainingTurn() const { return RemainingTurn; }
	void SetRemainingTurn(const int32 NewRemaingTurn) { RemainingTurn = NewRemaingTurn; }

	int32 GetMaxTurn() const { return MaxTurn; }

	TArray<bool> GetKeepArray() const { return KeepArray; }

	TArray<int32> GetDiceArray() const { return DiceArray; }

	TArray<int32> GetPredictArray() const { return PredictArray; }

public:
	void InitArray();

	void InitKeepArray();

	void InitDiceArray();

	void ToggleKeep(int32 Index);

	void Roll();

	void PredictScore();

	void NextTurn();

	void FinishTurn();

private:
	UPROPERTY(Replicated)
	bool bIsPlayer1Turn;

	UPROPERTY(Replicated)
	bool bIsPredicting;

	UPROPERTY(Replicated)
	int32 CurrentRound;

	UPROPERTY()
	int32 TotalRound;

	UPROPERTY(Replicated)
	int32 RemainingTurn;

	UPROPERTY()
	int32 MaxTurn;

	UPROPERTY(Replicated)
	TArray<bool> KeepArray;

	UPROPERTY(Replicated)
	TArray<int32> DiceArray;

	UPROPERTY(Replicated)
	TArray<int32> PredictArray;

	UPROPERTY(EditDefaultsOnly)
	UYachtPredictScoreComponent* PredictScoreComponent;
};