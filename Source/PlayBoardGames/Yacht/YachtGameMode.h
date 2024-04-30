#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YachtGameMode.generated.h"

UCLASS()
class PLAYBOARDGAMES_API AYachtGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AYachtGameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer);
};