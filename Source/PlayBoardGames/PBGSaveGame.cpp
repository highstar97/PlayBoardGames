#include "PBGSaveGame.h"

UPBGSaveGame::UPBGSaveGame()
{
	SaveSlotName = "Guest";
	UserIndex = 0;
	ID = SaveSlotName;
	YachtSaveData.NumOfAchieves.Empty();
	YachtSaveData.NumOfAchieves =
	{
		{"One", 0},
		{"Two", 0},
		{"Three",0},
		{"Four",0},
		{"Five", 0},
		{"Six", 0},
		{"Choice",0},
		{"4OfAKind",0},
		{"FullHouse", 0},
		{"SmallStraight", 0},
		{"LargeStraight",0},
		{"Yacht",0}
	};
}