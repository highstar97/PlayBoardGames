#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainMenuInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class PLAYBOARDGAMES_API IMainMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Host(FString ServerName) = 0;

	virtual void Join(uint32 Index) = 0;

	virtual void  LoadMainMenu() = 0;

	virtual void RefreshServerList() = 0;
};