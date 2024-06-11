#include "PBGMainMenuWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/PanelWidget.h"

#include "PBGGameInstance.h"
#include "PBGPlayerController.h"
#include "PBGLoginWidget.h"
#include "PBGPlayerInfoWidget.h"
#include "PBGServerRowWidget.h"

UPBGMainMenuWidget::UPBGMainMenuWidget(const FObjectInitializer& Objectinitializer) : Super(Objectinitializer)
{
	bIsPlayerLogIn = false;
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_LoginWidgetClass(TEXT("/Game/Blueprints/MainMenu/WBP_LoginMenu"));
	if (WBP_LoginWidgetClass.Succeeded())
	{
		LoginWidgetClass = WBP_LoginWidgetClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> BP_ServerRowClass(TEXT("/Game/Blueprints/MainMenu/WBP_ServerRow"));
	if (BP_ServerRowClass.Succeeded())
	{
		ServerRowClass = BP_ServerRowClass.Class;
	}
}

void UPBGMainMenuWidget::SetUp()
{
	this->AddToViewport();

	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(MainMenuInterface);
	if (!ensure(PBGPlayerController != nullptr)) return;

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetWidgetToFocus(this->TakeWidget());
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PBGPlayerController->SetInputMode(InputModeUIOnly);
	PBGPlayerController->SetShowMouseCursor(true);
}

void UPBGMainMenuWidget::TearDown()
{
	this->RemoveFromParent();

	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(MainMenuInterface);
	if (!ensure(PBGPlayerController != nullptr)) return;

	FInputModeGameOnly InputModeGameOnly;
	PBGPlayerController->SetInputMode(InputModeGameOnly);
	PBGPlayerController->SetShowMouseCursor(false);
}

void UPBGMainMenuWidget::UpdatePlayerInfo(FString InputID)
{
	PlayerInfoWidget->SetID(InputID);
}

void UPBGMainMenuWidget::UpdateServerList(TArray<FServerData> ServerDatas)
{
	ScrollBox_ServerList->ClearChildren();

	uint32 Index = 0;
	for (const FServerData& ServerData : ServerDatas)
	{
		if (!ensure(ServerRowClass != nullptr)) return;
		UPBGServerRowWidget* PBGServerRow = CreateWidget<UPBGServerRowWidget>(GetOwningPlayer(), ServerRowClass);
		if (!ensure(PBGServerRow != nullptr)) return;

		PBGServerRow->TextBlock_ServerName->SetText(FText::FromString(ServerData.Name));
		PBGServerRow->TextBlock_HostUser->SetText(FText::FromString(ServerData.HostUserName));
		// TODO : Check CurrnePlayers
		PBGServerRow->TextBlock_ConnectionFraction->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers)));
		PBGServerRow->Setup(this, Index);
		++Index;

		ScrollBox_ServerList->AddChild(PBGServerRow);
	}
}

void UPBGMainMenuWidget::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

bool UPBGMainMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(Button_Exit != nullptr)) return false;
	Button_Exit->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::ExitGame);

	if (!ensure(Button_Game1 != nullptr)) return false;
	Button_Game1->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::SwitchToJoinMenu);

	if (!ensure(Button_CancelHost != nullptr)) return false;
	Button_CancelHost->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::SwitchToSelectMenu);

	if (!ensure(Button_HostServer != nullptr)) return false;
	Button_HostServer->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::HostServer);

	if (!ensure(Button_CancelJoin != nullptr)) return false;
	Button_CancelJoin->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::SwitchToSelectMenu);

	if (!ensure(Button_MakeServer != nullptr)) return false;
	Button_MakeServer->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::SwitchToHostMenu);

	if (!ensure(Button_JoinServer != nullptr)) return false;
	Button_JoinServer->OnClicked.AddDynamic(this, &UPBGMainMenuWidget::JoinServer);

	return true;
}

void UPBGMainMenuWidget::NativeConstruct()
{
	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	TArray<FPBGGame> PBGGames = PBGGameInstance->GetPBGGames();
	if (PBGGames.IsEmpty()) return;

	// ToDo : Make it more simple.
	if (!ensure(TextBlock_Game1 != nullptr)) return;
	if (!PBGGames.IsValidIndex(1)) return;
	TextBlock_Game1->SetText(FText::FromString(PBGGames[1].Name));
}

void UPBGMainMenuWidget::ExitGame()
{
	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(MainMenuInterface);
	if (!ensure(PBGPlayerController != nullptr)) return;

	PBGPlayerController->ConsoleCommand("quit");
}

void UPBGMainMenuWidget::HostServer()
{
	if (MainMenuInterface != nullptr)
	{
		FString ServerName = EditableTextBox_ServerHostName->GetText().ToString();
		MainMenuInterface->Host(ServerName);
	}
}

void UPBGMainMenuWidget::JoinServer()
{
	if (MainMenuInterface != nullptr)
	{
		if (SelectedIndex.IsSet())
		{
			MainMenuInterface->Join(SelectedIndex.GetValue());
		}
	}
}

void UPBGMainMenuWidget::SwitchToSelectMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(SelectMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(SelectMenu);
}

void UPBGMainMenuWidget::SwitchToHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UPBGMainMenuWidget::SwitchToJoinMenu()
{
	if (!bIsPlayerLogIn)
	{
		if (!ensure(LoginWidgetClass != nullptr)) return;
		UPBGLoginWidget* PBGLoginWidget = CreateWidget<UPBGLoginWidget>(GetOwningPlayer(), LoginWidgetClass);
		if (!ensure(PBGLoginWidget != nullptr)) return;

		PBGLoginWidget->SetUp(this);
		return;
	}

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (!ensure(MainMenuInterface != nullptr)) return;
	MainMenuInterface->FindServerList();
}

void UPBGMainMenuWidget::UpdateChildren()
{
	for (int32 i = 0; i < ScrollBox_ServerList->GetChildrenCount(); ++i)
	{
		UPBGServerRowWidget* PBGServerRow = Cast<UPBGServerRowWidget>(ScrollBox_ServerList->GetChildAt(i));
		if (PBGServerRow != nullptr)
		{
			PBGServerRow->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}