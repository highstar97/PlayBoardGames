#pragma once

#include "CoreMinimal.h"
#include "../PBGPlayerState.h"
#include "YachtPlayerState.generated.h"

UCLASS()
class PLAYBOARDGAMES_API AYachtPlayerState : public APBGPlayerState
{
	GENERATED_BODY()

public:
	AYachtPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

public:
	int32 GetPlayerNumber() const { return PlayerNumber; }
	void SetPlayerNumber(int32 NewNumber) { PlayerNumber = NewNumber; }

	TArray<bool> GetFixedArray() const { return FixedArray; }
	void SetFixedArray(bool bIsFixed, int32 Index) { FixedArray[Index] = bIsFixed; }

	TArray<int32> GetScoreArray() const { return ScoreArray; }
	void SetScoreArray(int32 FixedScore, int32 Index) { ScoreArray[Index] = FixedScore; }

public:
	void UpdateSpecialScore();

	int32 CalculateSubTotal();

	int32 CalculateBonus();
	
	int32 CalculateTotal();

private:
	UFUNCTION(Server, unreliable)
	void Server_UpdatePlayerNumber(const int32 NewNumber);

private:
	UPROPERTY(Replicated)
	int32 PlayerNumber;
	
	UPROPERTY(Replicated)
	TArray<bool> FixedArray;

	UPROPERTY(Replicated)
	TArray<int32> ScoreArray;
};