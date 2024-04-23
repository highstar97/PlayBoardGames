#include "PBGPlayerController.h"

#include "Blueprint/UserWidget.h"

#include "PBGMainMenuWidget.h"

void APBGPlayerController::TurnOnPBGMainMenuWidget()
{
	if (!ensure(MainMenuClass != nullptr))return;

	MainMenuWidget = CreateWidget<UPBGMainMenuWidget>(this, MainMenuClass);
	if (!ensure(MainMenuWidget != nullptr)) return;

	MainMenuWidget->SetUp();
}

void APBGPlayerController::TurnOffPBGMainMenuWidget()
{
	if (!ensure(MainMenuWidget != nullptr)) return;

	MainMenuWidget->TearDown();
}