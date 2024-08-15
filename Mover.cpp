// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MovePlatform(DeltaTime);

}

void UMover::MovePlatform(float DeltaTime) {

	if (ShouldPlatformReturn()) {

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		GetOwner()->SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else {
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		GetOwner()->SetActorLocation(CurrentLocation);
	}
}

bool UMover::ShouldPlatformReturn()const {

	return GetDistanceMoved() > MoveDistance;
}

float UMover::GetDistanceMoved()const {
	return FVector::Dist(StartLocation, GetOwner()->GetActorLocation());
}

