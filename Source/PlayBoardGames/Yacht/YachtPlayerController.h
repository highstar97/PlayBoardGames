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

public:
	UFUNCTION(Server, unreliable)
	void Server_ToggleKeep(const int32 Index);	
	
	UFUNCTION(Server, unreliable)
	void Server_Roll();

	UFUNCTION(Server, unreliable)
	void Server_FixScore(const int32 PlayerNUmber, const int32 Index);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> YachtWidgetClass;

	UPROPERTY()
	UYachtWidget* YachtWidget;
};