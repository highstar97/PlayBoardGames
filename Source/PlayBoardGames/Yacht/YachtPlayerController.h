#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YachtPlayerController.generated.h"

class UYachtWidget;

UCLASS()
class PLAYBOARDGAMES_API AYachtPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AYachtPlayerController();
	
	virtual void InitPlayerState() override;

	void TurnOnYachtWidget();

	void TurnOffYachtWidget();

	bool IsPlayerTurn();

	bool IsTurnRemain();

	UFUNCTION(Server, reliable)
	void Server_FinishTurn();

	UFUNCTION(Server, reliable)
	void Server_NextTurn();

	UFUNCTION(Server, reliable)
	void Server_UpdateValueToAllClient(const TArray<int32>& ValueArray);

	UFUNCTION(Client, reliable)
	void Client_UpdateValue(const TArray<int32>& ValueArray);

	UFUNCTION(Server, reliable)
	void Server_UpdateKeepToAllClient(const TArray<bool>& KeepArray);

	UFUNCTION(Client, reliable)
	void Client_UpdateKeep(const TArray<bool>& KeepArray);

	UFUNCTION(Server, reliable)
	void Server_UpdateScoreTableToAllClient(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray);

	UFUNCTION(Client, reliable)
	void Client_UpdateScoreTable(const int& OwnerNumber, const TArray<bool>& SelectedArray, const TArray<int32>& ScoreArray);

	UFUNCTION(Server, reliable)
	void Server_UpdateSpecialScoreToAllClient(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray);

	UFUNCTION(Client, reliable)
	void Client_UpdateSpecialScore(const int& OwnerNumber, const TArray<int32>& SpecialScoreArray);

	UFUNCTION(Server, reliable)
	void Server_UpdateYourNumberToAllClient();

	UFUNCTION(Client, reliable)
	void Client_UpdateYourNumber(const int32 YourNumber);

	UFUNCTION(Server, reliable)
	void Server_UpdatePlayerNumberToAllClient();

	UFUNCTION(Client, reliable)
	void Client_UpdatePlayerNumber(const int32 PlayerNumber);

	UFUNCTION(Server, reliable)
	void Server_UpdateRemainingTurnToAllClient();

	UFUNCTION(Client, reliable)
	void Client_UpdateRemainingTurn(const int32 RemainingTurn);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> YachtWidgetClass;

	UPROPERTY()
	UYachtWidget* YachtWidget;
};