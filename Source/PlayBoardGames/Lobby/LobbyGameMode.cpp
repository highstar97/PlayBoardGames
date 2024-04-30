#include "LobbyGameMode.h"

#include "TimerManager.h"

#include "LobbyPlayerController.h"
#include "../PBGPlayerState.h"
#include "../PBGGameState.h"
#include "../PBGGameInstance.h"

ALobbyGameMode::ALobbyGameMode()
{
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
	PlayerStateClass = APBGPlayerState::StaticClass();
	GameStateClass = APBGGameState::StaticClass();

	NumberOfPlayers = 0;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++NumberOfPlayers;

	if (NumberOfPlayers == 2)
	{
		//SetStartGame(true);
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ALobbyGameMode::StartGame, 5, false);
	}
}

void ALobbyGameMode::Logout(AController* ExitPlayer)
{
	Super::Logout(ExitPlayer);

	--NumberOfPlayers;
	if (NumberOfPlayers < 2)
	{
		//SetStartGame(false);
	}
}

void ALobbyGameMode::SetStartGame(bool _CanStart)
{
	// TODO : LobbyWidget Start Button È°¼ºÈ­

	
}

void ALobbyGameMode::StartGame()
{
	UPBGGameInstance* PBGGameInstance = Cast<UPBGGameInstance>(GetGameInstance());
	if (!ensure(PBGGameInstance != nullptr)) return;

	PBGGameInstance->StartSession();
	
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ALobbyPlayerController* LobbyPlayerController = Cast<ALobbyPlayerController>(*It);
		if (LobbyPlayerController)
		{
			LobbyPlayerController->Client_TurnOffLobbyWidget();
		}
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/Maps/Yacht");
}