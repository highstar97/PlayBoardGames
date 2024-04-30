#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class PLAYBOARDGAMES_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* ExitPlayer) override;

private:
	void SetStartGame(bool _CanStart);

	void StartGame();

private:
	uint32 NumberOfPlayers = 0;

	FTimerHandle GameStartTimer;
};