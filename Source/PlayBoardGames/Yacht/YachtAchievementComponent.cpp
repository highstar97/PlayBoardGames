#include "YachtAchievementComponent.h"

#include "GameFramework/GameplayMessageSubsystem.h"

#include "../PBGGameInstance.h"
#include "../PBGSaveGame.h"

UYachtAchievementComponent::UYachtAchievementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	NumsOfTrigger = { 1,3 };
}

void UYachtAchievementComponent::AchieveScore(FGameplayTag ChannelTag, const FAchievementScoreMessage& InMessage)
{
	if (Cast<APlayerController>(GetOwner())->IsLocalPlayerController() == false) return;

	const FAchievementScoreMessage& Message = InMessage;
	if (Message.EarnedScore == 0) return;
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	UPBGGameInstance* PBGGameInstace = Cast<UPBGGameInstance>(World->GetGameInstance());
	if (!ensure(PBGGameInstace != nullptr)) return;

	UPBGSaveGame* PBGSaveGame = PBGGameInstace->GetPBGSaveGame();
	if (!ensure(PBGSaveGame != nullptr)) return;

	int32 NumOfAchieve = ++(PBGSaveGame->YachtSaveData.NumOfAchieves[InMessage.FixedButton]);

	for (int32 NumOfTrigger : NumsOfTrigger)
	{
		if (NumOfAchieve == NumOfTrigger)
		{
			AYachtPlayerController* YachtPlayerController = Cast<AYachtPlayerController>(GetOwner());
			if (!ensure(YachtPlayerController != nullptr)) return;

			YachtPlayerController->ShowAchieveWidget(NumOfAchieve, InMessage.FixedButton);
			PBGGameInstace->SaveGameData(PBGSaveGame->ID);
			return;
		}
	}
}

void UYachtAchievementComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);

	FGameplayTag ChannelTag = FGameplayTag::RequestGameplayTag(FName("Achieve.Score"));
	auto ListenerHandle = MessageSubsystem.RegisterListener(ChannelTag, this, &UYachtAchievementComponent::AchieveScore);
}