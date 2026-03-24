#include "MNIsland.h"
#include "Components/SphereComponent.h"

AMNIsland::AMNIsland()
{
	PrimaryActorTick.bCanEverTick = false;

	// Island mesh (set in Blueprint)
	IslandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IslandMesh"));
	RootComponent = IslandMesh;

	// Docking zone — sphere around dock position
	DockingZone = CreateDefaultSubobject<USphereComponent>(TEXT("DockingZone"));
	DockingZone->SetupAttachment(RootComponent);
	DockingZone->SetSphereRadius(500.f);
	DockingZone->SetCollisionProfileName(TEXT("OverlapAll"));
	DockingZone->SetRelativeLocation(FVector(0, -400, 0)); // South side by default
}

void AMNIsland::BeginPlay()
{
	Super::BeginPlay();
	DockPosition = GetActorLocation() + FVector(0, -400, 0);
}

bool AMNIsland::CanDock()
{
	return true; // All islands are dockable
}

void AMNIsland::CaptureIsland(EFaction NewOwner)
{
	OwnerFaction = NewOwner;
	bCaptured = true;
	bPlayerOwned = true;
	GarrisonSize = 0;
}

int32 AMNIsland::GetDefenseStrength()
{
	return Defense + Level * 100 + GarrisonSize * 50;
}
