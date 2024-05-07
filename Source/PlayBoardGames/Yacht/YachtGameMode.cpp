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

	UE_LOG(LogTemp, Warning, TEXT("YachtGameMode Login Player : %s"), *NewPlayer->GetName());

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(NewPlayer);
	if (!ensure(YachtPlayerController != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = YachtPlayerController->GetPlayerState<AYachtPlayerState>(); 
	if (!ensure(YachtPlayerState != nullptr)) return;

	int32 PlayerNumber = YachtGameState->GetWhichPlayerTurn();
	YachtPlayerState->SetPlayerNumber(PlayerNumber);

	YachtGameState->ChangePlayerTurn();
}