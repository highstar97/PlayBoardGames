#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YachtGameMode.generated.h"

class AYachtPlayerState;
class AYachtGameState;

UCLASS()
class PLAYBOARDGAMES_API AYachtGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AYachtGameMode();

	virtual void PostLogin(APlayerController* NewPlayer);

public:
	void EndGame();
};