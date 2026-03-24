#include "MNGameState.h"

AMNGameState::AMNGameState()
{
	// Initialize all 8 factions
	auto AddFaction = [this](EFaction F, const FString& Name, FLinearColor Primary, FLinearColor Secondary) {
		FFactionData Data;
		Data.Faction = F;
		Data.Name = Name;
		Data.PrimaryColor = Primary;
		Data.SecondaryColor = Secondary;
		Factions.Add(F, Data);
	};

	AddFaction(EFaction::Rome,      TEXT("Rome"),      FLinearColor(0.72f, 0.15f, 0.11f, 1), FLinearColor(1, 1, 1, 1));
	AddFaction(EFaction::Carthage,  TEXT("Carthage"),  FLinearColor(0.47f, 0.20f, 0.63f, 1), FLinearColor(0.9f, 0.85f, 0.7f, 1));
	AddFaction(EFaction::Egypt,     TEXT("Egypt"),     FLinearColor(0.78f, 0.67f, 0.16f, 1), FLinearColor(0.16f, 0.59f, 0.63f, 1));
	AddFaction(EFaction::Greece,    TEXT("Greece"),    FLinearColor(0.20f, 0.39f, 0.67f, 1), FLinearColor(0.94f, 0.92f, 0.88f, 1));
	AddFaction(EFaction::Persia,    TEXT("Persia"),    FLinearColor(0.42f, 0.16f, 0.54f, 1), FLinearColor(0.67f, 0.51f, 0.24f, 1));
	AddFaction(EFaction::Gaul,      TEXT("Gaul"),      FLinearColor(0.16f, 0.42f, 0.19f, 1), FLinearColor(0.47f, 0.39f, 0.20f, 1));
	AddFaction(EFaction::Phoenicia, TEXT("Phoenicia"), FLinearColor(0.54f, 0.06f, 0.31f, 1), FLinearColor(0.24f, 0.51f, 0.27f, 1));
	AddFaction(EFaction::SeaPeople, TEXT("Sea People"),FLinearColor(0.10f, 0.23f, 0.36f, 1), FLinearColor(0.71f, 0.16f, 0.16f, 1));
}

void AMNGameState::AdvanceDay()
{
	Day++;
	// Daily income from controlled islands
	Gold += ControlledIslands.Num() * 5;
	Food += ControlledIslands.Num() * 3;
}

bool AMNGameState::CanAfford(int32 GoldCost, int32 FoodCost, int32 WoodCost, int32 StoneCost)
{
	return Gold >= GoldCost && Food >= FoodCost && Wood >= WoodCost && Stone >= StoneCost;
}

void AMNGameState::SpendResources(int32 GoldCost, int32 FoodCost, int32 WoodCost, int32 StoneCost)
{
	Gold -= GoldCost;
	Food -= FoodCost;
	Wood -= WoodCost;
	Stone -= StoneCost;
}

bool AMNGameState::CheckMilitaryVictory()
{
	return CapturedCapitals >= 6;
}

bool AMNGameState::CheckEconomicVictory()
{
	return ControlledTradeHubs >= 4 && Gold >= 100000;
}

bool AMNGameState::CheckDiplomaticVictory()
{
	return AllianceCount >= 4 && ControlledIslands.Contains(TEXT("senate_house"));
}
