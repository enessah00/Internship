// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightInterface.h"
#include "Lightv2.generated.h"


class UPointLightComponent;

UCLASS()
class TASK_BALOON_API ALightv2 : public AActor, public ILightInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightv2();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* ButtonRef;

	virtual void LightOnInterface() override;

	UFUNCTION()
	void LightOn();
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
