#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayBoardGamesGameModeBase.generated.h"

UCLASS()
class PLAYBOARDGAMES_API APlayBoardGamesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayBoardGamesGameModeBase();

protected:
	virtual void PostLogin(APlayerController* NewPlayer);
};