#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MNGameState.generated.h"

UENUM(BlueprintType)
enum class EFaction : uint8
{
	Rome,
	Carthage,
	Egypt,
	Greece,
	Persia,
	Gaul,
	Phoenicia,
	SeaPeople
};

UENUM(BlueprintType)
enum class EIslandType : uint8
{
	Capital,
	TradeHub,
	Resource,
	Military,
	Diplomatic
};

USTRUCT(BlueprintType)
struct FFactionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) EFaction Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor PrimaryColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor SecondaryColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Gold = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Food = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Wood = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Stone = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Reputation = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bDefeated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bAllied = false;
};

UCLASS()
class MARENOSTRUM_API AMNGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMNGameState();

	// Player faction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	EFaction PlayerFaction = EFaction::Rome;

	// Day counter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 Day = 1;

	// Player resources
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Gold = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Food = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Wood = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Stone = 20;

	// Faction data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Factions")
	TMap<EFaction, FFactionData> Factions;

	// Controlled islands
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Islands")
	TArray<FString> ControlledIslands;

	// Army
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Army")
	int32 ArmySize = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Army")
	int32 ArmyCap = 30;

	// Victory tracking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Victory")
	int32 CapturedCapitals = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Victory")
	int32 ControlledTradeHubs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Victory")
	int32 AllianceCount = 0;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Game")
	void AdvanceDay();

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool CanAfford(int32 GoldCost, int32 FoodCost, int32 WoodCost, int32 StoneCost);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SpendResources(int32 GoldCost, int32 FoodCost, int32 WoodCost, int32 StoneCost);

	UFUNCTION(BlueprintCallable, Category = "Victory")
	bool CheckMilitaryVictory();

	UFUNCTION(BlueprintCallable, Category = "Victory")
	bool CheckEconomicVictory();

	UFUNCTION(BlueprintCallable, Category = "Victory")
	bool CheckDiplomaticVictory();
};
