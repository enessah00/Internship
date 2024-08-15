// Fill out your copyright notice in the Description page of Project Settings.


#include "target.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "balloon.h"

// Sets default values
Atarget::Atarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
	ProjectileSpawnPointv2 = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPointv2->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void Atarget::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	OnTakeAnyDamage.AddDynamic(this, &Atarget::DamageTaken2);
	
}

void Atarget::Fire()
{
	if (ProjectileClassv2 != nullptr) {

		FVector Loc = ProjectileSpawnPointv2->GetComponentLocation();
		FRotator Rot = ProjectileSpawnPointv2->GetComponentRotation();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClassv2, Loc, Rot);

		if (Projectile) {
			Projectile->SetOwner(this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("SetOwner Doesnt Work"));
		}
	
	
	}
}

void Atarget::DamageTaken2(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator2, AActor* DamageCauser)
{
	
	TArray<AActor*> BalloonArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aballoon::StaticClass(), BalloonArray);
	Aballoon* balloonref = Cast<Aballoon>(BalloonArray[0]);
	
	/*
	* balloonref concreate class olmadýðý için hata verdi.
	*/
	if (balloonref) {
		Fire();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("balloonref nullptr"));
	}
	
	if (Damage <= 0) return;
	Health -= Damage;
	if (Health <= 0 ) {
		
		if (balloonref != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Target->Balloon Cast True"));
			balloonref->ClearTimerFunction();
		}

		if (IsValid(this)) {
			Destroy();
		}
	}
}
/*
damagecauser actorü balona cast et *
timerhandle destroy dan önce invalid et

timerhandle ulaþabilecek mi bak
damagecauser ý düzgün setupladýn mý

damagecauser projectile mý projectile ý çaðýran sahip


*/



// Called every frame
void Atarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

