#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PBGPlayerState.generated.h"

UCLASS()
class PLAYBOARDGAMES_API APBGPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APBGPlayerState();

	virtual void CopyProperties(APlayerState* PlayerState) override;

	virtual void OverrideWith(APlayerState* PlayerState) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool GetbIsHost() const { return bIsHost; }

	void SetbIsHost(bool _bIsHost) { bIsHost = _bIsHost; }

	UFUNCTION(BlueprintCallable)
	FString GetUserName() const { return UserName; }

	UFUNCTION(BlueprintCallable)
	void SetUserName(const FString& _UserName) { UserName = _UserName; }

private:
	UPROPERTY(Replicated)
	bool bIsHost;

	UPROPERTY(Replicated)
	FString UserName;
};