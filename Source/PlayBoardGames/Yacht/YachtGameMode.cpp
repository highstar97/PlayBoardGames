#include "YachtGameMode.h"

#include "YachtPlayerController.h"

AYachtGameMode::AYachtGameMode()
{
	PlayerControllerClass = AYachtPlayerController::StaticClass();
}

void AYachtGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("YachtGameMode Login Player : %s"), *NewPlayer->GetName());
}