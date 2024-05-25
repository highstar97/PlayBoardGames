#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBGPlayerInfoWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UTextBlock;
class UEditableText;

UCLASS()
class PLAYBOARDGAMES_API UPBGPlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnTextCommitted(const FText& _Text, ETextCommit::Type _CommitMethod);

protected:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void TurnOnEditableTextBox();

	void TurnOffEditableTextBox();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_UserName;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* NameSwitcher;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_UserName;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText_NewUserName;
};