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
	int32 GetWhichPlayerTurn() { return bIsPlayer1Turn == true ? 1 : 2; }

	void ChangePlayerTurn();

public:
	FOnPlayerChanged OnPlayerChanged;

private:
	UPROPERTY(Replicated)
	bool bIsPlayer1Turn;
};