#include "PBGPlayerInfoWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

#include "PBGPlayerController.h"
#include "PBGGameState.h"
#include "PBGPlayerState.h"

void UPBGPlayerInfoWidget::OnClicked()
{
	if (!ensure(NameSwitcher != nullptr)) return;

	NameSwitcher->SetActiveWidgetIndex(1);
}

void UPBGPlayerInfoWidget::OnTextCommitted(const FText& _Text, ETextCommit::Type _CommitMethod)
{
	if (!ensure(TextBlock_UserName != nullptr)) return;

	TextBlock_UserName->SetText(_Text);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APBGGameState* PBGGameState = Cast<APBGGameState>(World->GetGameState());
	if (!ensure(PBGGameState != nullptr)) return;

	APBGPlayerController* PBGPlayerController = Cast<APBGPlayerController>(GetOwningPlayer());
	if (!ensure(PBGPlayerController != nullptr)) return;

	for (TObjectPtr<APlayerState>& PlayerState : PBGGameState->PlayerArray)
	{
		if (PlayerState->GetUniqueID() == PBGPlayerController->GetPlayerState<APBGPlayerState>()->GetUniqueID())
		{
			UE_LOG(LogTemp, Warning, TEXT("OwningPlayerController : %s"), *PBGPlayerController->GetName());
						
			APBGPlayerState* PBGPlayerState = Cast<APBGPlayerState>(PlayerState);
			if (!ensure(PBGPlayerState != nullptr)) return;

			UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), PBGPlayerState->GetbIsHost() ? TEXT("True") : TEXT("False"));
			UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), *PBGPlayerState->GetUserName());

			PBGPlayerState->SetUserName(_Text.ToString());

			UE_LOG(LogTemp, Warning, TEXT("PBGPlayerState's UserName : %s"), *PBGPlayerState->GetUserName());
		}
	}

	if (!ensure(NameSwitcher != nullptr)) return;

	NameSwitcher->SetActiveWidgetIndex(0);
}

bool UPBGPlayerInfoWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess)	return false;

	if (!ensure(Button_UserName != nullptr)) return false;
	Button_UserName->OnClicked.AddDynamic(this, &UPBGPlayerInfoWidget::OnClicked);

	if (!ensure(EditableText_NewUserName != nullptr)) return false;
	EditableText_NewUserName->OnTextCommitted.AddDynamic(this, &UPBGPlayerInfoWidget::OnTextCommitted);

	return true;
}