#include "PlayBoardGamesGameModeBase.h"

#include "PBGPlayerController.h"
#include "PBGPlayerState.h"
#include "PBGGameState.h"

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