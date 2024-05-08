#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "YachtGameState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerChanged);

class AYachtPlayerController;

UCLASS()
class PLAYBOARDGAMES_API AYachtGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AYachtGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	int32 GetWhichPlayerTurn() { return NumOfPlay % 2 == 1 ? 1 : 2; }

	void ChangePlayerTurn();

public:
	FOnPlayerChanged OnPlayerChanged;

private:
	bool IsGameFinish() { if (NumOfPlay == 24) return true; else return false; }

private:
	UPROPERTY(Replicated)
	int32 NumOfPlay;
};