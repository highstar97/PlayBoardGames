#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class APBGPlayerState;
class ULobbyPlayerRowWidget;
class UTextBlock;
class UPanelWidget;
class UButton;

UCLASS()
class PLAYBOARDGAMES_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	ULobbyWidget(const FObjectInitializer& Objectinitializer);

	void UpdatePlayerList(TArray<APBGPlayerState*> ConnectedPlayerStates);

	void KickOut(ULobbyPlayerRowWidget* PlayerRow);

protected:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ExitGame();

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_GameName;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ScrollBox_PlayerList;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CancelGame;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartGame;

	TSubclassOf<UUserWidget> PlayerRowClass;

	TOptional<uint32> SelectedIndex;
};