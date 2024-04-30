#include "LobbyPlayerRowWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "LobbyWidget.h"

void ULobbyPlayerRowWidget::Setup(ULobbyWidget* _Parent, bool _bIsHost)
{
	Parent = _Parent;
	bIsHost = _bIsHost;

	if (bIsHost)
	{
		Image_Hoster->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Button_Kick->SetVisibility(ESlateVisibility::Visible);
		Button_Kick->OnClicked.AddDynamic(this, &ULobbyPlayerRowWidget::OnClicked);
	}
}

void ULobbyPlayerRowWidget::OnClicked()
{
	Parent->KickOut(this);
}