// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADoor::Interact()
{
    OpenDoor();
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialRotation = GetActorRotation();

    AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (MyCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("Door is Received Interface"));
        MyCharacter->OnInteract.AddDynamic(this, &ADoor::HandleInteract);
    }
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::HandleInteract(AActor* InteractedActor)
{
    if (InteractedActor!=nullptr && InteractedActor == this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Door is Received Dispatcher"));
        OpenDoor(); 
    }
}

void ADoor::OpenDoor()
{
    if (!bIsOpen)
    {
        FRotator NewRotation = InitialRotation + FRotator(0.f, 90.f, 0.f);
        SetActorRotation(NewRotation);
        bIsOpen = true;
    }
}

