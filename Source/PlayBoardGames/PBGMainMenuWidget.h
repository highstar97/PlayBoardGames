#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBGMainMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class PLAYBOARDGAMES_API UPBGMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UPBGMainMenuWidget(const FObjectInitializer& Objectinitializer);

	void SetUp();

	void TearDown();

protected:
	virtual bool Initialize() override;
	
	virtual void NativeConstruct() override; // Widget이 뷰포트에 추가되고 초기화될 때 호출됨

private:
	UFUNCTION()
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

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game4;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game5;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game6;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game7;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Game8;
};