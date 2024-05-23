#include "PBGPlayerInfoWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

#include "PBGGameInstance.h"
#include "PBGGameState.h"
#include "PBGPlayerState.h"
#include "PBGPlayerController.h"

void UPBGPlayerInfoWidget::OnTextCommitted(const FText& _Text, ETextCommit::Type _CommitMethod)
{
	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(GetOwningPlayer());
	if (!ensure(PBGPlayerController != nullptr)) return;

	PBGPlayerController->Server_SetUserName(_Text.ToString());

	if (!ensure(TextBlock_UserName != nullptr)) return;

	TextBlock_UserName->SetText(_Text);

	TurnOffEditableTextBox();
}

bool UPBGPlayerInfoWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(Button_UserName != nullptr)) return false;
	Button_UserName->OnClicked.AddDynamic(this, &UPBGPlayerInfoWidget::TurnOnEditableTextBox);

	if (!ensure(EditableText_NewUserName != nullptr)) return false;
	EditableText_NewUserName->OnTextCommitted.AddDynamic(this, &UPBGPlayerInfoWidget::OnTextCommitted);

	return true;
}

void UPBGPlayerInfoWidget::TurnOnEditableTextBox()
{
	if (!ensure(NameSwitcher != nullptr)) return;

	NameSwitcher->SetActiveWidgetIndex(1);
}

void UPBGPlayerInfoWidget::TurnOffEditableTextBox()
{
	if (!ensure(NameSwitcher != nullptr)) return;

	NameSwitcher->SetActiveWidgetIndex(0);
}