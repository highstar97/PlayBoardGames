#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PBGSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FYachtSaveData
{
	GENERATED_USTRUCT_BODY()

public:
    UPROPERTY()
    TMap<FString, int32> NumOfAchieves;
};

UCLASS()
class PLAYBOARDGAMES_API UPBGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UPBGSaveGame();

public:
    UPROPERTY(VisibleAnywhere, Category = "SaveData.Basic")
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = "SaveData.Basic")
    uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, Category = "SaveData.Basic")
    FString ID;

    UPROPERTY(VisibleAnywhere, Category = "SaveData.Yacht")
	FYachtSaveData YachtSaveData;
};