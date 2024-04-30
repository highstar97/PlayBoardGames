#include "YachtPlayerController.h"

#include "YachtWidget.h"

AYachtPlayerController::AYachtPlayerController()
{
	static ConstructorHelpers::FClassFinder<UYachtWidget> BP_YachtWidgetClass(TEXT("/Game/Blueprints/Yacht/WBP_YachtWidget"));
	if (BP_YachtWidgetClass.Succeeded())
	{
		YachtWidgetClass = BP_YachtWidgetClass.Class;
	}
}

void AYachtPlayerController::TurnOnYachtWidget()
{
	if (!ensure(YachtWidget != nullptr)) return;
	
	YachtWidget->AddToViewport();

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetWidgetToFocus(YachtWidget->TakeWidget());
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
}

void AYachtPlayerController::TurnOffYachtWidget()
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->RemoveFromParent();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
}

void AYachtPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (!ensure(YachtWidgetClass != nullptr)) return;
		YachtWidget = CreateWidget<UYachtWidget>(this, YachtWidgetClass);
		if (!ensure(YachtWidget != nullptr)) return;

		TurnOnYachtWidget();
	}
}