#include "PBGPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "PBGGameState.h"

APBGPlayerState::APBGPlayerState()
{
	bIsHost = false;
	UserName = "User001";
}

void APBGPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (IsValid(PlayerState))
	{
		APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(PlayerState);
		if (IsValid(PBGPlayerState))
		{
			PBGPlayerState->bIsHost = bIsHost;
			PBGPlayerState->UserName = UserName;
		}
	}
}

void APBGPlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);

	if (IsValid(PlayerState))
	{
		APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(PlayerState);
		if (IsValid(PBGPlayerState))
		{
			bIsHost = PBGPlayerState->bIsHost;
			UserName = PBGPlayerState->UserName;
		}
	}
}

void APBGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APBGPlayerState, bIsHost);
	DOREPLIFETIME(APBGPlayerState, UserName);
}