#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YachtPlayerController.generated.h"

class UYachtWidget;

UCLASS()
class PLAYBOARDGAMES_API AYachtPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AYachtPlayerController();

	void TurnOnYachtWidget();

	void TurnOffYachtWidget();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> YachtWidgetClass;

	UPROPERTY()
	UYachtWidget* YachtWidget;
};