#include "YachtGameState.h"

#include "Net/UnrealNetwork.h"

#include "YachtPlayerController.h"

AYachtGameState::AYachtGameState()
{
	bReplicates = true;

	NumOfPlay = 1;
}

void AYachtGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYachtGameState, NumOfPlay);
}

void AYachtGameState::ChangePlayerTurn()
{
	++NumOfPlay;

	OnPlayerChanged.Broadcast();

	if (IsGameFinish())
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Finish"));
	}
}