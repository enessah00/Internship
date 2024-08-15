// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "balloon.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = Projectile;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(Projectile);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->MaxSpeed = 1300;
	ProjectileMovement->InitialSpeed = 1300;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//  Projectile->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
				
				AActor* MyOwner = GetOwner();
				
				if (MyOwner) {
					FString Message = MyOwner->GetName();
					UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
				}
				if (MyOwner == nullptr) {
	 				UE_LOG(LogTemp, Warning, TEXT("Owner == nullptr"));
					Destroy();
					return;
				}
				AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

				UClass* DamageTypeClass = UDamageType::StaticClass();
				if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
					
					UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, GetOwner(), DamageTypeClass);
				}
				Destroy();
} 
/*
overlap olduðu zaman aþaðýdan yukarý top spawn et
*/

 void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	 /*
	 UE_LOG(LogTemp, Warning, TEXT("Projectile Hit"));
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Projectile MyOwner == nullptr"));
		Destroy();
		return;
	}
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UE_LOG(LogTemp, Warning, TEXT("Projectile ApplyDamage"));
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, GetOwner(), DamageTypeClass);
	}
	Destroy();
	 */
	 
}

 




// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AProjectile::ProjectileCallFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Function Call Success"));
}

