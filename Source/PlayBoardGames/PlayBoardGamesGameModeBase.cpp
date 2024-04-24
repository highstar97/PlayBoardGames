#include "PlayBoardGamesGameModeBase.h"

#include "PBGPlayerController.h"

APlayBoardGamesGameModeBase::APlayBoardGamesGameModeBase()
{
	PlayerControllerClass = APBGPlayerController::StaticClass();
}

void APlayBoardGamesGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Login Player : %s"), *NewPlayer->GetName());
}