// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractableInterface.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract,AActor*,HitActor);

UCLASS()
class TASK_BALOON_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	// Function to handle character interaction
	void Interact();

	UPROPERTY()
	FOnInteract OnInteract;

	// Variables
	float InteractRange; // Range of interaction
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	// Character movement component
	UCharacterMovementComponent* MovementComponent;

	// Mouse sensitivity
	UPROPERTY(EditAnywhere)
	float BaseTurnRate;

	UPROPERTY(EditAnywhere)
	float BaseLookUpRate;
};
