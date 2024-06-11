#include "PBGLoginwidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

#include "PBGGameInstance.h"
#include "PBGMainMenuWidget.h"

void UPBGLoginWidget::SetUp(UPBGMainMenuWidget* _MainMenu)
{
	this->AddToViewport();
	MainMenu = _MainMenu;
}

void UPBGLoginWidget::TearDown()
{
	this->RemoveFromParent();
}

void UPBGLoginWidget::OnTextCommitted(const FText& _Text, ETextCommit::Type _CommitMethod)
{
	ID = EditableTextBox_ID->GetText().ToString();
}

void UPBGLoginWidget::Login()
{
	// Check ID is Valid
	if (ID.IsEmpty())
	{
		EditableTextBox_ID->SetHintText(FText::FromString("Wrong ID :("));
		return;
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(World->GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	PBGGameInstance->LoadGameData(ID);

	MainMenu->SetbIsPlayerLogin(true);
	MainMenu->UpdatePlayerInfo(ID);

	this->RemoveFromParent();
}

bool UPBGLoginWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(EditableTextBox_ID != nullptr)) return false;
	EditableTextBox_ID->OnTextCommitted.AddDynamic(this, &UPBGLoginWidget::OnTextCommitted);

	if (!ensure(Button_Cancel != nullptr)) return false;
	Button_Cancel->OnClicked.AddDynamic(this, &UPBGLoginWidget::TearDown);

	if (!ensure(Button_Login != nullptr)) return false;
	Button_Login->OnClicked.AddDynamic(this, &UPBGLoginWidget::Login);

	return true;
}