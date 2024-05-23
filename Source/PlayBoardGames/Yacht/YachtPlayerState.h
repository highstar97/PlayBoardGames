#pragma once

#include "CoreMinimal.h"
#include "../PBGPlayerState.h"
#include "YachtPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRemainingTurnChanged);

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

	void SetPlayerNumber(int32 NewPlayerNumber) { PlayerNumber = NewPlayerNumber; }

	int32 GetRemainingTurn() const { return RemainingTurn; }

	void SetRemainingTurn(int32 NewRemainingTurn = 3) { RemainingTurn = NewRemainingTurn; }

	void NextTurn();

	void FinishTurn();

public:
	FOnRemainingTurnChanged OnRemainingTurnChanged;

private:
	UPROPERTY(Replicated)
	int32 PlayerNumber;

	UPROPERTY(Replicated)
	int32 RemainingTurn;
};