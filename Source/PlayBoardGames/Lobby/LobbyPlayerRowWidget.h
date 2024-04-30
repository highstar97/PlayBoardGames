#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "LobbyPlayerRowWidget.generated.h"

class ULobbyWidget;
class UImage;
class UTextBlock;
class UButton;

UCLASS()
class PLAYBOARDGAMES_API ULobbyPlayerRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(ULobbyWidget* _Parent, bool _bIsHost);

	void SetPlayerName(FText _PlayerName) { TextBlock_PlayerName->SetText(_PlayerName); }

private:
	UFUNCTION()
	void OnClicked();

private:
	UPROPERTY()
	ULobbyWidget* Parent;

	bool bIsHost;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Hoster;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_PlayerName;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Kick;
};