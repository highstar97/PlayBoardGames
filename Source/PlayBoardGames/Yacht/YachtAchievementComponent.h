#pragma once

#include "CoreMinimal.h"
#include "YachtPlayerController.h"
#include "Components/ActorComponent.h"
#include "YachtAchievementComponent.generated.h"

struct FGameplayTag;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYBOARDGAMES_API UYachtAchievementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UYachtAchievementComponent();

public:
	UFUNCTION()
	void AchieveScore(FGameplayTag ChannelTag, const FAchievementScoreMessage& InMessage);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<int32> NumsOfTrigger;
};