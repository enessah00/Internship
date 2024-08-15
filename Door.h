// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Door.generated.h"


UCLASS()
class TASK_BALOON_API ADoor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	
	ADoor();

	virtual void Interact() override;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void OpenDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UFUNCTION()
	void HandleInteract(AActor* InteractedActor);

	bool bIsOpen;

	FRotator InitialRotation;
};
