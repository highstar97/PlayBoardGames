#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBGMainMenuWidget.generated.h"

class UButton;

UCLASS()
class PLAYBOARDGAMES_API UPBGMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:
	virtual bool Initialize() override;

private:
	void ExitGame();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game1;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game2;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game3;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game4;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game5;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game6;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game7;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Game8;
};