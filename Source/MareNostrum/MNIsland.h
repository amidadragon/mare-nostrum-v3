#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MNGameState.h"
#include "MNIsland.generated.h"

UCLASS()
class MARENOSTRUM_API AMNIsland : public AActor
{
	GENERATED_BODY()

public:
	AMNIsland();

	// Island identity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	FString IslandKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	FString IslandName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	EIslandType IslandType = EIslandType::Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	EFaction OwnerFaction = EFaction::Rome;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	int32 Defense = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	int32 GarrisonSize = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	bool bCaptured = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	bool bPlayerOwned = false;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* IslandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* DockingZone;

	// Dock position (where ships land)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
	FVector DockPosition;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Island")
	bool CanDock();

	UFUNCTION(BlueprintCallable, Category = "Island")
	void CaptureIsland(EFaction NewOwner);

	UFUNCTION(BlueprintCallable, Category = "Island")
	int32 GetDefenseStrength();

protected:
	virtual void BeginPlay() override;
};
