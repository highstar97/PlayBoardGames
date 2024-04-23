#include "PBGGameInstance.h"

UPBGGameInstance::UPBGGameInstance()
{
	// ToDo : Make it more simply.
	PBGGames.Empty();
	FPBGGame Null;
	PBGGames.Add(Null);
	FPBGGame Yacht("Yacht");
	PBGGames.Add(Yacht);
}