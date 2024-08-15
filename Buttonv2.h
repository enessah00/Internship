// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Buttonv2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightOn);

UCLASS()
class TASK_BALOON_API AButtonv2 : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonv2();
	virtual void Interact() override;

	UPROPERTY()
	FLightOn LightOn;

	void Activate();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* Lightv2;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void HandleInteract(AActor* InteractedActor);

};
