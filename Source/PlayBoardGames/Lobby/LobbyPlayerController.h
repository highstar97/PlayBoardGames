#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class ULobbyWidget;
class APBGPlayerState;

UCLASS()
class PLAYBOARDGAMES_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyPlayerController();

	void TurnOnLobbyWidget();

	UFUNCTION(Client, unreliable)
	void Client_TurnOffLobbyWidget();

	void UpdatePlayerList();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY()
	ULobbyWidget* LobbyWidget;
};