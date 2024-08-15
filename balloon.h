// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "balloon.generated.h"
UCLASS()
class TASK_BALOON_API Aballoon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aballoon();

	UFUNCTION()
	void ClearTimerFunction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Fire();
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
//	UPrimitiveComponent* PrimitiveComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	float TimeElapsed = 0;
//	FVector StartLocation;

	FVector TargetLocation;
	float TargetZ;

	UPROPERTY (EditAnywhere, Category="Lerp")
	float LerpDuration = 3;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 3;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 0.1;
	float RunningTime;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeedv2 = 1000;


	UFUNCTION()
	void DamageTaken2(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator2, AActor* DamageCauser);

	FVector MovementDirection = FVector(0, 1, 0);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
