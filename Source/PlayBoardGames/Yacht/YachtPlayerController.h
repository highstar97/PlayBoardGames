#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YachtPlayerController.generated.h"

class UYachtAchievementComponent;
class UYachtWidget;

USTRUCT()
struct FAchievementScoreMessage
{
	GENERATED_BODY()
	
public:
	FAchievementScoreMessage() : EarnedScore(0), FixedButton("None") {}

	FAchievementScoreMessage(const int32 _EarnedScore, const FString& _FixedButton) : EarnedScore(_EarnedScore), FixedButton(_FixedButton) {}

public:
	UPROPERTY()
	int32 EarnedScore;

	UPROPERTY()
	FString FixedButton;
};

UCLASS()
class PLAYBOARDGAMES_API AYachtPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AYachtPlayerController();

public:
	UFUNCTION(Server, unreliable)
	void Server_ToggleKeep(const int32 Index);	
	
	UFUNCTION(Server, unreliable)
	void Server_Roll();

	UFUNCTION(Server, unreliable)
	void Server_FixScore(const int32 PlayerNUmber, const int32 Index);

	void ShowAchieveWidget(int32 NumOfAchieve, const FString& AchieveScore);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(Client, unreliable)
	void Client_SendAchieveScoreMessage(const int32 FixedScore, int32 AchieveHandIndex);

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> YachtWidgetClass;

	UPROPERTY()
	UYachtWidget* YachtWidget;

	UPROPERTY()
	TMap<int32, FAchievementScoreMessage> AchievementDataMap;

	UPROPERTY()
	UYachtAchievementComponent* AchievementComponent;
};