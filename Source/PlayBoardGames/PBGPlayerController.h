#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuInterface.h"
#include "PBGPlayerController.generated.h"

struct FServerData;
class UUserWidget;
class UPBGMainMenuWidget;

UCLASS()
class PLAYBOARDGAMES_API APBGPlayerController : public APlayerController, public IMainMenuInterface
{
	GENERATED_BODY()
	
public:
	APBGPlayerController();

	virtual void Host(FString ServerName) override;

	virtual void Join(uint32 Index) override;

	virtual void  LoadToMainMenuLevel() override;

	virtual void FindServerList() override;

public:
	void UpdateServerList(TArray<FServerData> ServerDatas);

	void TurnOnMainMenu();

	void TurnOffMainMenu();

	UFUNCTION(Server, unreliable)
	void Server_SetbIsHost(const bool _bIsHost);

	UFUNCTION(Server, unreliable)
	void Server_SetUserName(const FString& _UserName);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> PBGMainMenuClass;

	UPROPERTY()
	UPBGMainMenuWidget* PBGMainMenu;
};