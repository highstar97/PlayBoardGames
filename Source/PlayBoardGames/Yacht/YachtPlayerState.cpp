#include "YachtPlayerState.h"

#include "Net/UnrealNetwork.h"

#include "YachtGameState.h"
#include "YachtPlayerController.h"

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

void AYachtPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
		if (!ensure(YachtGameState != nullptr)) return;

		PlayerNumber = YachtGameState->GetWhichPlayerTurn();

		YachtGameState->AddNumOfPlay(1);
	}

	AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetPlayerController());
	if(YachtPlayerController != nullptr && YachtPlayerController->IsLocalController())
	{
		YachtPlayerController->Client_UpdateYourNumber(PlayerNumber);
	}
}

void AYachtPlayerState::NextTurn()
{
	--RemainingTurn;

	OnRemainingTurnChanged.Broadcast();
}

void AYachtPlayerState::FinishTurn()
{
	RemainingTurn = 3;
	OnRemainingTurnChanged.Broadcast();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	YachtGameState->ChangePlayerTurn();
}