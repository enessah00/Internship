// Fill out your copyright notice in the Description page of Project Settings.


#include "Lightv2.h"
#include "Buttonv2.h"

#include "Components/PointLightComponent.h"
// Sets default values
ALightv2::ALightv2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
 
    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->Intensity = 0.0f;
    PointLight->AttenuationRadius = 500.0f;
    PointLight->SetLightColor(FLinearColor::White);
    RootComponent = PointLight;
}

void ALightv2::LightOnInterface()
{
    LightOn();
    UE_LOG(LogTemp, Warning, TEXT("Light is Received Second Interface"));
}

void ALightv2::LightOn()
{
    PointLight->SetIntensity(5000);
}

void ALightv2::BeginPlay()
{
    Super::BeginPlay();

    AButtonv2* ButtonRefe = Cast<AButtonv2>(ButtonRef);
    if (ButtonRefe) {
        UE_LOG(LogTemp, Warning, TEXT("Light is Received Second Dispatcher"));
        ButtonRefe->LightOn.AddDynamic(this, &ALightv2::LightOn);
    }
    
}



