#include "PlayBoardGamesGameModeBase.h"

#include "PBGGameState.h"
#include "PBGPlayerState.h"
#include "PBGPlayerController.h"

APlayBoardGamesGameModeBase::APlayBoardGamesGameModeBase()
{
	PlayerControllerClass = APBGPlayerController::StaticClass();
	PlayerStateClass = APBGPlayerState::StaticClass();
	GameStateClass = APBGGameState::StaticClass();
}

void APlayBoardGamesGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}