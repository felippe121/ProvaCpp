// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforms.h"

// Sets default values
APlataforms::APlataforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void APlataforms::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void APlataforms::AddActiveTrigger() {
	ActiveTriggers++;
}

void APlataforms::RemoveActiveTrigger() {
	if (ActiveTriggers > 0) {
		ActiveTriggers--;
	}
}

void APlataforms::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0) {
		FVector Location = GetActorLocation();

		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();

		if (JourneyTravelled >= JourneyLength) {
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += DeltaTime * SpeedPlataform * Direction;
		SetActorLocation(Location);
	}
}
