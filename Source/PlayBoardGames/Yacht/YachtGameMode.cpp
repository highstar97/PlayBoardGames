#include "YachtGameMode.h"

#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtPlayerController.h"

AYachtGameMode::AYachtGameMode()
{
	PlayerControllerClass = AYachtPlayerController::StaticClass();
	GameStateClass = AYachtGameState::StaticClass();
	PlayerStateClass = AYachtPlayerState::StaticClass();
}

void AYachtGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}