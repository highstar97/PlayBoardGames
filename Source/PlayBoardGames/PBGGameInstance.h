#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MainMenuInterface.h"
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
class PLAYBOARDGAMES_API UPBGGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UPBGGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	virtual void Host(FString ServerName) override;

	UFUNCTION(Exec)
	virtual void Join(uint32 Index) override;

	virtual void  LoadMainMenu() override;

	virtual void RefreshServerList() override;

	void StartSession();

	TArray<FPBGGame> GetPBGGames() { return PBGGames; }

private:
	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	void CreateSession();

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> PBGMainMenuClass;

	UPBGMainMenuWidget* MainMenu;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FString DesiredServerName;

	TArray<FPBGGame> PBGGames;
};