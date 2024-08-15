// Fill out your copyright notice in the Description page of Project Settings.


#include "balloon.h"

#include "Projectile.h"
#include "target.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
Aballoon::Aballoon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
//	PrimitiveComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Primitive Comp"));
//	PrimitiveComp->SetupAttachment(CapsuleComp);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(CapsuleComp);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(mesh);

}

// Called when the game starts or when spawned
void Aballoon::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> TargetArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Atarget::StaticClass(), TargetArray);
	if (TargetArray.Num() > 0) {
		Atarget* TargetRef = Cast<Atarget>(TargetArray[0]);
		if (TargetRef) {
			TargetLocation = TargetRef->GetActorLocation();
			TargetLocation.X = TargetLocation.X;
			TargetLocation.Y = TargetLocation.Y;
			TargetLocation.Z = GetActorLocation().Z;
			
		//	TargetZ = TargetLocation.Z;
		}
	}
	

	Health = MaxHealth;

	OnTakeAnyDamage.AddDynamic(this, &Aballoon::DamageTaken2);

	
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &Aballoon::Fire, FireRate, true);


}

void Aballoon::ClearTimerFunction()
{
	GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
}

void Aballoon::DamageTaken2(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator2, AActor* DamageCauser)
{
	if (Damage <= 0) return;
	Health -= Damage;
	if (Health <= 0) {
		Destroy();
	}
}



// Called every frame
void Aballoon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// titremeyi önle
	float DistanceXY = FVector::DistXY(GetActorLocation(), TargetLocation);
	if (DistanceXY >= 50.f) {
		FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
		SetActorLocation(GetActorLocation() + Direction * MovementSpeedv2 * DeltaTime);
		if (DistanceXY <= 3000.f) {
			TargetLocation.Z = 2000;
		}
		else {
			TargetLocation.Z = GetActorLocation().Z;
		}
	}
	
	//belirli yere geldikten sonra balon aþaðý hareket etsin
	
//	PrimitiveComp->AddForce(Direction * MovementSpeed * DeltaTime);

/*	float DistanceXY = FVector::DistXY(GetActorLocation(), TargetLocation);
	if (DistanceXY <= 2000.f) {
		TargetLocation.Z = TargetZ;
	}
	else {
		TargetLocation.Z = GetActorLocation().Z;
	}
*/
/*
	FVector CurrentLocation = GetActorLocation();
	FVector TargetDirection = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocationMove = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MovementSpeed);
	SetActorLocation(NewLocationMove);
*/

	//sað sol salýným hareketi
	
	float SinValue = FMath::Sin(RunningTime + DeltaTime); 
	RunningTime += DeltaTime;
	if (DistanceXY <= 3000.f) {
		
	}
	FVector Movement = MovementDirection * SinValue * MovementSpeedv2 * DeltaTime;
	if (mesh) {
		FVector NewLocation = mesh->GetRelativeLocation() + Movement;
		mesh->SetRelativeLocation(NewLocation);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("mesh access doesnt work"));
	}
	
	
	

	/*
	if (TimeElapsed < LerpDuration) {
		
		SetActorLocation(FMath::Lerp(StartLocation,TargetLocation,TimeElapsed/LerpDuration));
		TimeElapsed += DeltaTime;
	}
	*/
	
	
}

void Aballoon::Fire()
{
	if (ProjectileClass != nullptr ) {

		FVector Loc = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rot = ProjectileSpawnPoint->GetComponentRotation();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Loc, Rot);
		if (Projectile) {
			Projectile->SetOwner(this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("SetOwner Doesnt Work"));
		}
	}
	
}

