// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"

#include "Engine/World.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationData.h"

#include "Kismet/GameplayStatics.h"
#include "balloon.h"
// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
   
    FVector RandomLocation = FMath::RandPointInBox(FBox(FVector(-10000.0f, -10000.0f, 4000.0f), FVector(10000.0f, 10000.0f, 5000.0f)));

    FActorSpawnParameters SpawnParams;
    GetWorld()->SpawnActor<Aballoon>(BalloonClass, RandomLocation, FRotator::ZeroRotator, SpawnParams);
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

