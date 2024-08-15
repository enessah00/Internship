// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AElevator::Interact()
{
    GoUp();
}



// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (MyCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("Elevator is Received Interface"));
        MyCharacter->OnInteract.AddDynamic(this, &AElevator::HandleInteract);
    }
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}
void AElevator::HandleInteract(AActor* InteractedActor)
{
    if (InteractedActor == this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Elevator is Received Dispatcher"));
        GoUp();
    }
}
void AElevator::GoUp()
{
    if (!bIsUp)
    {
        FVector NewLocation = InitialLocation + FVector(0.f, 0.f, 90.f);
        SetActorLocation(NewLocation);
        bIsUp = true;
    }
}
