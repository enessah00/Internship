// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "balloon.h"
#include "EngineUtils.h"


void AMyGameModeBase::AMyGameMode()
{
    FVector SpawnLocation = FMath::RandPointInBox(FBox(FVector(100, 100, 3000), FVector(20000, 20000, 4500)));

    // Balonu olu�tur ve rastgele konumda yerle�tir
    Aballoon* Balloon = GetWorld()->SpawnActor<Aballoon>(Aballoon::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
    if (Balloon) {
        UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BALLON CAST SUCCESS"));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BALLON CAST FAILED"));
    }
}
