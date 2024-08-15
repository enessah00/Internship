// Fill out your copyright notice in the Description page of Project Settings.


#include "Buttonv2.h"

#include "Lightv2.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
// Sets default values
AButtonv2::AButtonv2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AButtonv2::Interact()
{
	Activate();
}

void AButtonv2::Activate()
{
	
	if (Lightv2) {

		ALightv2* Light = Cast<ALightv2>(Lightv2);
		if (Light)
		{
			Light->PointLight->SetIntensity(5000);
		}
	}
	
	LightOn.Broadcast();
	
}

// Called when the game starts or when spawned
void AButtonv2::BeginPlay()
{
	Super::BeginPlay();
	
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button is Received Interface"));
		MyCharacter->OnInteract.AddDynamic(this, &AButtonv2::HandleInteract);
	}
}

// Called every frame
void AButtonv2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonv2::HandleInteract(AActor* InteractedActor)
{
	if (InteractedActor == this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button is Received Dispatcher"));
		Activate();
	}
}

