#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PBGGameState.generated.h"

UCLASS()
class PLAYBOARDGAMES_API APBGGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	APBGGameState();

	void PrintPlayerArray();
};