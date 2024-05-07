#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "YachtPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRemainingTurnChanged);

UCLASS()
class PLAYBOARDGAMES_API AYachtPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AYachtPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	int32 GetPlayerNumber() const { return PlayerNumber; }

	void SetPlayerNumber(int32 NewPlayerNumber) { PlayerNumber = NewPlayerNumber; }

	int32 GetRemainingTurn() const { return RemainingTurn; }

	void SetRemainingTurn(int32 NewRemainingTurn = 3) { RemainingTurn = NewRemainingTurn; }

	void NextTurn();

public:
	FOnRemainingTurnChanged OnRemainingTurnChanged;

private:
	UPROPERTY(Replicated)
	int32 PlayerNumber;

	UPROPERTY(Replicated)
	int32 RemainingTurn;
};