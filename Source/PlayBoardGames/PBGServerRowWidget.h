#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBGServerRowWidget.generated.h"

class UPBGMainMenuWidget;
class UTextBlock;
class UButton;

UCLASS()
class PLAYBOARDGAMES_API UPBGServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup(UPBGMainMenuWidget* _Parent, uint32 _Index);

private:
	UFUNCTION()
	void OnClicked();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_ServerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_HostUser;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_ConnectionFraction;

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false;

private:
	UPROPERTY()
	UPBGMainMenuWidget* Parent;

	uint32 Index;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ServerRow;
};