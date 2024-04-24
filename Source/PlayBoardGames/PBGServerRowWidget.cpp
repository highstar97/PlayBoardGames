#include "PBGServerRowWidget.h"

#include "Components/Button.h"

#include "PBGMainMenuWidget.h"

void UPBGServerRowWidget::Setup(UPBGMainMenuWidget* _Parent, uint32 _Index)
{
	this->Parent = _Parent;
	this->Index = _Index;
	Button_ServerRow->OnClicked.AddDynamic(this, &UPBGServerRowWidget::OnClicked);
}

void UPBGServerRowWidget::OnClicked()
{
	Parent->SelectIndex(Index);
}