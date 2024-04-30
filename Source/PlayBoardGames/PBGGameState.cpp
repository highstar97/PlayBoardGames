#include "PBGGameState.h"

#include "EngineUtils.h"

#include "PBGPlayerState.h"

APBGGameState::APBGGameState()
{
}

void APBGGameState::PrintPlayerArray()
{
    UE_LOG(LogTemp, Warning, TEXT("Print PlayerArray in PBGGameState"));
    for (TObjectPtr<APlayerState> PlayerState : PlayerArray)
    {
        APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(PlayerState);
        UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %f"), PBGPlayerState->GetUniqueID());
        UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), PBGPlayerState->GetbIsHost() ? TEXT("True") : TEXT("False"));
        UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), *PBGPlayerState->GetUserName());
    }
}