#include "YachtGameState.h"

#include "Net/UnrealNetwork.h"

#include "YachtPlayerController.h"

AYachtGameState::AYachtGameState()
{
	bReplicates = true;

	bIsPlayer1Turn = true;
}

void AYachtGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYachtGameState, bIsPlayer1Turn);
}

void AYachtGameState::ChangePlayerTurn()
{
	bIsPlayer1Turn = !bIsPlayer1Turn;

	OnPlayerChanged.Broadcast();
}