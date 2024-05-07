#include "YachtPlayerState.h"

#include "Net/UnrealNetwork.h"

#include "YachtGameState.h"

AYachtPlayerState::AYachtPlayerState()
{
	bReplicates = true;

	PlayerNumber = 0;
	RemainingTurn = 3;
}

void AYachtPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYachtPlayerState, PlayerNumber);
	DOREPLIFETIME(AYachtPlayerState, RemainingTurn);
}

void AYachtPlayerState::NextTurn()
{
	--RemainingTurn;
	if (RemainingTurn == 0)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
		if (!ensure(YachtGameState != nullptr)) return;

		YachtGameState->ChangePlayerTurn();
		RemainingTurn = 3;
	}

	OnRemainingTurnChanged.Broadcast();
}