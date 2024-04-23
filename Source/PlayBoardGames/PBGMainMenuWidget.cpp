#include "PBGMainMenuWidget.h"

#include "Components/Button.h"

bool UPBGMainMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(Button_Exit != nullptr)) return false;
	Button_Exit->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::ExitGame);

	return true;
}

void UPBGMainMenuWidget::ExitGame()
{

}