#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PBGGameInstance.generated.h"

USTRUCT()
struct FPBGGame
{
	GENERATED_USTRUCT_BODY();

public:
	FPBGGame() { Name = "Null"; }
	FPBGGame(FString _Name) { Name = _Name; };

public:
	FString Name;
};

UCLASS()
class PLAYBOARDGAMES_API UPBGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPBGGameInstance();

public:
	TArray<FPBGGame> GetPBGGames() { return PBGGames; }

private:
	TArray<FPBGGame> PBGGames;
};
