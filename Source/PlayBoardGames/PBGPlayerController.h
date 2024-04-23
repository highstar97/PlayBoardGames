#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBGPlayerController.generated.h"

class UUserWidget;
class UPBGMainMenuWidget;

UCLASS()
class PLAYBOARDGAMES_API APBGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void TurnOnPBGMainMenuWidget();

	void TurnOffPBGMainMenuWidget();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPBGMainMenuWidget* MainMenuWidget;
};