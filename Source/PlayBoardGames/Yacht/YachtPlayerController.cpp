#include "YachtPlayerController.h"

#include "GameFramework/GameplayMessageSubsystem.h"

#include "YachtGameMode.h"
#include "YachtGameState.h"
#include "YachtPlayerState.h"
#include "YachtAchievementComponent.h"
#include "YachtWidget.h"
#include "YachtAchieveWidget.h"

AYachtPlayerController::AYachtPlayerController()
{
	static ConstructorHelpers::FClassFinder<UYachtWidget> BP_YachtWidgetClass(TEXT("/Game/Blueprints/Yacht/WBP_YachtWidget"));
	if (BP_YachtWidgetClass.Succeeded())
	{
		YachtWidgetClass = BP_YachtWidgetClass.Class;
	}

	AchievementDataMap =
	{
		{ 0, FAchievementScoreMessage(0, "One")},
		{ 1, FAchievementScoreMessage(0, "Two")},
		{ 2, FAchievementScoreMessage(0, "Three")},
		{ 3, FAchievementScoreMessage(0, "Four")},
		{ 4, FAchievementScoreMessage(0, "Five")},
		{ 5, FAchievementScoreMessage(0, "Six")},
		{ 6, FAchievementScoreMessage(0, "Choice")},
		{ 7, FAchievementScoreMessage(0, "4OfAKind")},
		{ 8, FAchievementScoreMessage(0, "FullHouse")},
		{ 9, FAchievementScoreMessage(0, "SmallStraight")},
		{ 10, FAchievementScoreMessage(0, "LargeStraight")},
		{ 11, FAchievementScoreMessage(0, "Yacht")},
	};

	AchievementComponent = CreateDefaultSubobject<UYachtAchievementComponent>(TEXT("AchievementComponent"));
}

void AYachtPlayerController::Server_ToggleKeep_Implementation(const int32 Index)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = this->GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	// Check Player Turn
	if (YachtGameState->GetWhichPlayerTurn() != YachtPlayerState->GetPlayerNumber()) return;

	// Keep Dice
	YachtGameState->ToggleKeep(Index);

	YachtGameState->ForceNetUpdate();
}

void AYachtPlayerController::Server_Roll_Implementation()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = this->GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	// Check Player Turn
	if (YachtGameState->GetWhichPlayerTurn() != YachtPlayerState->GetPlayerNumber()) return;

	// Is My Turn Remaining?
	if (YachtGameState->GetRemainingTurn() <= 0) return;

	// Roll Dice
	YachtGameState->Roll();

	// Predict Score
	YachtGameState->SetbIsPredicting(true);
	YachtGameState->PredictScore();

	// Next Turn;
	YachtGameState->NextTurn();

	YachtGameState->ForceNetUpdate();
	YachtPlayerState->ForceNetUpdate();
}

void AYachtPlayerController::Server_FixScore_Implementation(const int32 PlayerNumber, const int32 Index)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	AYachtGameState* YachtGameState = Cast<AYachtGameState>(World->GetGameState());
	if (!ensure(YachtGameState != nullptr)) return;

	AYachtPlayerState* YachtPlayerState = this->GetPlayerState<AYachtPlayerState>();
	if (!ensure(YachtPlayerState != nullptr)) return;

	// Check Player Turn
	if (YachtGameState->GetWhichPlayerTurn() != YachtPlayerState->GetPlayerNumber()) return;

	// Check CurrentPlayerTurn != Button's OwnerPlayerNumber
	if (YachtGameState->GetWhichPlayerTurn() != PlayerNumber) return;

	// Need to Roll at least once
	if (YachtGameState->GetRemainingTurn() == YachtGameState->GetMaxTurn()) return;

	// Check PlayerState's FixedArray[Index]
	if (YachtPlayerState->GetFixedArray()[Index] == true) return;

	// Set Fixed Array true
	YachtPlayerState->SetFixedArray(true, Index);

	// Update ScoreArray[Index]
	YachtPlayerState->SetScoreArray(YachtGameState->GetPredictArray()[Index], Index);

	// Update ScoreArray[12]~[14]
	YachtPlayerState->UpdateSpecialScore();

	// Set GameState's bIsPredicting false
	YachtGameState->SetbIsPredicting(false);
	
	// Set Init Keep & Dice Array
	YachtGameState->InitArray();

	// Call GameState's FinishTurn()
	YachtGameState->FinishTurn();

	// [Client] Boradcast Message
	Client_SendAchieveScoreMessage(YachtGameState->GetPredictArray()[Index], Index);

	YachtGameState->ForceNetUpdate();
	YachtPlayerState->ForceNetUpdate();
}

void AYachtPlayerController::ShowAchieveWidget(int32 NumOfAchieve, const FString& AchieveScore)
{
	if (!ensure(YachtWidget != nullptr)) return;

	YachtWidget->ShowAchieveWidget(NumOfAchieve, AchieveScore);
}

void AYachtPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (!ensure(YachtWidgetClass != nullptr)) return;
		YachtWidget = CreateWidget<UYachtWidget>(this, YachtWidgetClass);
		
		if (!ensure(YachtWidget != nullptr)) return;
		YachtWidget->SetUp();
	}
}

void AYachtPlayerController::Client_SendAchieveScoreMessage_Implementation(const int32 FixedScore, int32 AchieveHandIndex)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	FGameplayTag Channel = FGameplayTag::RequestGameplayTag(FName("Achieve.Score"));
	FAchievementScoreMessage Message = AchievementDataMap[AchieveHandIndex];
	Message.EarnedScore = FixedScore;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(World);
	MessageSystem.BroadcastMessage(Channel, Message);
}