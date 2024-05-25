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

	void TurnOnTransitionWidget();

	void TurnOffTransitionWidget();

	UFUNCTION(Server, unreliable)
	void Server_UpdatePlayerState(const bool _bIsHost, const FString& _UserName);

	UFUNCTION(Client , unreliable)
	void Client_UpdatePlayerState();

	UFUNCTION(Server, unreliable)
	void Server_UpdatePlayerListToAllClient();

	UFUNCTION(Client, unreliable)
	void Client_UpdatePlayerList(const TArray<APBGPlayerState*>& ConnectedPlayerStates);
	
	void LoadToMainMenuLevel();

protected:
	virtual void BeginPlay() override;

private:
	bool bIsLobbyWidgetTurnOn;
	
	UPROPERTY()
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY()
	ULobbyWidget* LobbyWidget;

	bool bIsTransitionWidgetTurnOn;

	UPROPERTY()
	TSubclassOf<UUserWidget> TransitionWidgetClass;

	UPROPERTY()
	UUserWidget* TransitionWidget;

	FTimerHandle UpdatePlyaerListTimer;

	bool bIsHost;

	FString UserName;
};