#include "LobbyWidget.h"

#include "Components/PanelWidget.h"

#include "../PBGPlayerState.h"
#include "LobbyPlayerRowWidget.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& Objectinitializer) : Super(Objectinitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_PlayerRowClass(TEXT("/Game/Blueprints/Lobby/WBP_PlayerRow"));
	if (BP_PlayerRowClass.Succeeded())
	{
		PlayerRowClass = BP_PlayerRowClass.Class;
	}
}

void ULobbyWidget::UpdatePlayerList(TArray<APBGPlayerState*> ConnectedPlayerStates)
{
	ScrollBox_PlayerList->ClearChildren();

	for (APBGPlayerState*& PBGPlayerState : ConnectedPlayerStates)
	{
		if (!ensure(PlayerRowClass != nullptr)) return;
		ULobbyPlayerRowWidget* PlayerRow = CreateWidget<ULobbyPlayerRowWidget>(GetOwningPlayer(), PlayerRowClass);
		if (!ensure(PlayerRow != nullptr)) return;

		PlayerRow->SetPlayerName(FText::FromString(PBGPlayerState->GetUserName()));
		PlayerRow->Setup(this, PBGPlayerState->GetbIsHost());

		ScrollBox_PlayerList->AddChild(PlayerRow);
	}
}

void ULobbyWidget::KickOut(ULobbyPlayerRowWidget* PlayerRow)
{

}