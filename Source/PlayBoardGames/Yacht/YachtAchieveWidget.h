#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YachtAchieveWidget.generated.h"

class UWidgetAnimation;
class UTextBlock;

UCLASS()
class PLAYBOARDGAMES_API UYachtAchieveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUp();

	void TearDown();

	void PlayShowAnimation();

	void UpdateWidget(int32 NumOfAchieve, const FString& AchieveScore);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim, AllowPrivateAccess = "true"), Transient)
	UWidgetAnimation* Show;

	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_AchieveScore;

	UPROPERTY(VisibleAnywhere, Category = "Text", meta = (BindWidget))
	UTextBlock* TextBlock_AchieveTimes;
};