#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBGPlayerInfoWidget.generated.h"

class UTextBlock;

UCLASS()
class PLAYBOARDGAMES_API UPBGPlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetID(const FString& InputID);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_ID;
};