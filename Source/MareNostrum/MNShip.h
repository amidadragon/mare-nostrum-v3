#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MNGameState.h"
#include "MNShip.generated.h"

UCLASS()
class MARENOSTRUM_API AMNShip : public APawn
{
	GENERATED_BODY()

public:
	AMNShip();

	// Visual
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* HullMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SailMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* FollowCamera;

	// Ship properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	EFaction ShipFaction = EFaction::Rome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float MoveSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float TurnSpeed = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float BobAmplitude = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float BobFrequency = 1.f;

	// State
	UPROPERTY(BlueprintReadOnly, Category = "Ship")
	bool bIsSailing = false;

	UPROPERTY(BlueprintReadOnly, Category = "Ship")
	class AMNIsland* NearestIsland = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Ship")
	float DistToNearestIsland = 99999.f;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void StartSailing();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void StopSailing();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void DockAtIsland(AMNIsland* Island);

	UFUNCTION(BlueprintCallable, Category = "Ship")
	AMNIsland* FindNearestIsland();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	float BobTimer = 0.f;
	FVector BaseLocation;
};
