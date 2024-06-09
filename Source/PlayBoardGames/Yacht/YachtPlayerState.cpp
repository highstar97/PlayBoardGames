#include "YachtPlayerState.h"

#include "Net/UnrealNetwork.h"

#include "../PBGGameInstance.h"

AYachtPlayerState::AYachtPlayerState()
{
	bReplicates = true;
	NetUpdateFrequency = 1.0f;

	PlayerNumber = 0;
	FixedArray.Init(false, 12);
	ScoreArray.Init(0, 15);
}

void AYachtPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYachtPlayerState, PlayerNumber);
	DOREPLIFETIME(AYachtPlayerState, FixedArray);
	DOREPLIFETIME(AYachtPlayerState, ScoreArray);
}

void AYachtPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(World->GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	// Is Player Host?
	PBGGameInstance->LoadPlayerStateData().Key == true ? Server_UpdatePlayerNumber(1) : Server_UpdatePlayerNumber(2);
}

void AYachtPlayerState::UpdateSpecialScore()
{
	ScoreArray[12] = CalculateSubTotal();
	ScoreArray[13] = CalculateBonus();
	ScoreArray[14] = CalculateTotal();
}

int32 AYachtPlayerState::CalculateSubTotal()
{
	int32 SubTotal = 0;
	for (int32 i = 0; i < 6; ++i)
	{
		SubTotal += ScoreArray[i];
	}
	return SubTotal;
}

int32 AYachtPlayerState::CalculateBonus()
{
	int32 Bonus = 35;
	if (ScoreArray[12] >= 63) return Bonus;
	return 0;
}

int32 AYachtPlayerState::CalculateTotal()
{
	int32 Total = ScoreArray[12] + ScoreArray[13];
	for (int32 i = 6; i < 12; ++i)
	{
		Total += ScoreArray[i];
	}
	return Total;
}

void AYachtPlayerState::Server_UpdatePlayerNumber_Implementation(const int32 NewNumber)
{
	SetPlayerNumber(NewNumber);
}