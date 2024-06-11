#include "PBGPlayerInfoWidget.h"

#include "Components/TextBlock.h"

void UPBGPlayerInfoWidget::SetID(const FString& InputID)
{
	TextBlock_ID->SetText(FText::FromString(InputID));
}