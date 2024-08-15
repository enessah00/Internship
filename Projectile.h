// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TASK_BALOON_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USphereComponent* CollisionSphere;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlapedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:
	



	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UProjectileMovementComponent* ProjectileMovement;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	
	UPROPERTY(EditAnywhere)
	float Damage = 50;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ProjectileCallFunc();
	
};
