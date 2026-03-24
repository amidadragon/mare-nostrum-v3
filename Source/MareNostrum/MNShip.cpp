#include "MNShip.h"
#include "MNIsland.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

AMNShip::AMNShip()
{
	PrimaryActorTick.bCanEverTick = true;

	// Hull mesh (set in Blueprint)
	HullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullMesh"));
	RootComponent = HullMesh;
	HullMesh->SetSimulatePhysics(false);

	// Sail mesh (child of hull)
	SailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SailMesh"));
	SailMesh->SetupAttachment(HullMesh);
	SailMesh->SetRelativeLocation(FVector(0, 0, 100));

	// Camera boom (top-down)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-55.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.f;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void AMNShip::BeginPlay()
{
	Super::BeginPlay();
	BaseLocation = GetActorLocation();
}

void AMNShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Bobbing on water
	BobTimer += DeltaTime * BobFrequency;
	FVector Loc = GetActorLocation();
	Loc.Z = BaseLocation.Z + FMath::Sin(BobTimer * 2.f * PI) * BobAmplitude;
	SetActorLocation(Loc);

	// Update base location for horizontal movement
	BaseLocation.X = Loc.X;
	BaseLocation.Y = Loc.Y;

	// Find nearest island
	NearestIsland = FindNearestIsland();
	if (NearestIsland)
	{
		DistToNearestIsland = FVector::Dist(GetActorLocation(), NearestIsland->GetActorLocation());
	}
	else
	{
		DistToNearestIsland = 99999.f;
	}
}

void AMNShip::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);
	InputComp->BindAxis("MoveForward", this, &AMNShip::MoveForward);
	InputComp->BindAxis("MoveRight", this, &AMNShip::MoveRight);
}

void AMNShip::MoveForward(float Value)
{
	if (FMath::Abs(Value) > 0.01f)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value * MoveSpeed);
		// Simple direct movement
		FVector Loc = GetActorLocation();
		Loc += Forward * Value * MoveSpeed * GetWorld()->GetDeltaSeconds();
		Loc.Z = BaseLocation.Z; // Keep Z stable (bob handles it)
		SetActorLocation(Loc);
		BaseLocation = Loc;
	}
}

void AMNShip::MoveRight(float Value)
{
	if (FMath::Abs(Value) > 0.01f)
	{
		// Turn the ship
		FRotator Rot = GetActorRotation();
		Rot.Yaw += Value * TurnSpeed * GetWorld()->GetDeltaSeconds();
		SetActorRotation(Rot);
	}
}

void AMNShip::StartSailing()
{
	bIsSailing = true;
}

void AMNShip::StopSailing()
{
	bIsSailing = false;
}

void AMNShip::DockAtIsland(AMNIsland* Island)
{
	if (!Island) return;
	StopSailing();
	SetActorLocation(Island->DockPosition);
}

AMNIsland* AMNShip::FindNearestIsland()
{
	TArray<AActor*> Islands;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMNIsland::StaticClass(), Islands);

	AMNIsland* Nearest = nullptr;
	float MinDist = 99999.f;

	for (AActor* Actor : Islands)
	{
		float Dist = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
		if (Dist < MinDist)
		{
			MinDist = Dist;
			Nearest = Cast<AMNIsland>(Actor);
		}
	}

	return Nearest;
}
