#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PBGGameInstance.generated.h"

USTRUCT()
struct FPBGGame
{
	GENERATED_USTRUCT_BODY();

public:
	FPBGGame() { Name = "Null"; }
	FPBGGame(FString _Name) { Name = _Name; };

public:
	FString Name;
};

class FOnlineSessionSearch;
class UPBGMainMenuWidget;

UCLASS()
class PLAYBOARDGAMES_API UPBGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPBGGameInstance();

	virtual void Init() override;

public:
	void Host();

	void Join(uint32 Index);

	void FindServerList();

	void StartSession();

	void SetDesiredServerName(FString _DesiredServerName) { DesiredServerName = _DesiredServerName; }
	
	TArray<FPBGGame> GetPBGGames() { return PBGGames; }

	void SavePlayerStateData();

	TPair<bool, FString> LoadPlayerStateData();

private:
	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	void CreateSession();

private:
	TPair<bool, FString> PlayerStateData;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FString DesiredServerName;

	TArray<FPBGGame> PBGGames;
};