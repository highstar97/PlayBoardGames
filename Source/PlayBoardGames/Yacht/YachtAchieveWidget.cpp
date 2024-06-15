#include "YachtAchieveWidget.h"

#include "Components/TextBlock.h"

void UYachtAchieveWidget::SetUp()
{
	this->AddToViewport();
}

void UYachtAchieveWidget::TearDown()
{
	this->RemoveFromParent();
}

void UYachtAchieveWidget::PlayShowAnimation()
{
	PlayAnimationForward(Show);
}

void UYachtAchieveWidget::UpdateWidget(int32 NumOfAchieve, const FString& AchieveScore)
{
	if (!ensure(TextBlock_AchieveScore != nullptr)) return;
	if (!ensure(TextBlock_AchieveTimes != nullptr)) return;

	TextBlock_AchieveScore->SetText(FText::FromString(AchieveScore));
	TextBlock_AchieveTimes->SetText(FText::FromString(FString::FromInt(NumOfAchieve)));
}