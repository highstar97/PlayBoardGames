#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuInterface.h"
#include "PBGMainMenuWidget.generated.h"

class UPBGPlayerInfoWidget;
class UWidgetSwitcher;
class UWidget;
class UButton;
class UTextBlock;
class UPanelWidget;
class UEditableTextBox;

USTRUCT()
struct FServerData
{
	GENERATED_USTRUCT_BODY()

public:
	FString Name;

	FString HostUserName;

	uint16 CurrentPlayers;

	uint16 MaxPlayers;
};

UCLASS()
class PLAYBOARDGAMES_API UPBGMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPBGMainMenuWidget(const FObjectInitializer& Objectinitializer);

public:
	void SetMainMenuInterface(IMainMenuInterface* _MainMenuInterface) { this->MainMenuInterface = _MainMenuInterface; }

	void SetbIsPlayerLogin(bool _bIsPlayerLogin) { bIsPlayerLogIn = _bIsPlayerLogin; }

public:
	void SetUp();

	void TearDown();

	void UpdatePlayerInfo(FString InputID);

	void UpdateServerList(TArray<FServerData> ServerDatas);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;
	
	virtual void NativeConstruct() override; // Widget이 뷰포트에 추가되고 초기화될 때 호출됨

private:
	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void HostServer();
	
	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void SwitchToSelectMenu();

	UFUNCTION()
	void SwitchToHostMenu();

	UFUNCTION()
	void SwitchToJoinMenu();

	void UpdateChildren();

private:
// LogIn
	bool bIsPlayerLogIn;

	TSubclassOf<UUserWidget> LoginWidgetClass;

// PlayerInfo
	UPROPERTY(meta = (BindWidget))
	UPBGPlayerInfoWidget* PlayerInfoWidget;

// MainMenu
	IMainMenuInterface* MainMenuInterface;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

// Select Menu Widget
	UPROPERTY(meta = (BindWidget))
	UWidget* SelectMenu;

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

// Host Menu Widget
	UPROPERTY(meta = (BindWidget))
	UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditableTextBox_ServerHostName;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CancelHost;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_HostServer;

// Join Menu Widget
	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CancelJoin;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_MakeServer;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_JoinServer;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ScrollBox_ServerList;

	TSubclassOf<UUserWidget> ServerRowClass;

	TOptional<uint32> SelectedIndex;
};