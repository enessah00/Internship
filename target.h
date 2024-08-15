// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "target.generated.h"

UCLASS()
class TASK_BALOON_API Atarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Atarget();

	UFUNCTION()
	void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;
	float Health = 0;


	UFUNCTION()
	void DamageTaken2(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator2, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPointv2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClassv2;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
