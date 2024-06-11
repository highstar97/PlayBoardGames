#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBGLoginWidget.generated.h"

class UPBGMainMenuWidget;
class UEditableTextBox;
class UButton;

UCLASS()
class PLAYBOARDGAMES_API UPBGLoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUp(UPBGMainMenuWidget* _MainMenu);

	UFUNCTION()
	void TearDown();

	UFUNCTION()
	void OnTextCommitted(const FText& _Text, ETextCommit::Type _CommitMethod);

	UFUNCTION()
	void Login();

protected:
	virtual bool Initialize() override;

private:
	UPBGMainMenuWidget* MainMenu;

	UPROPERTY()
	FString ID;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditableTextBox_ID;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Cancel;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Login;
};