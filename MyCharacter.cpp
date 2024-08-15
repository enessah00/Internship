// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Door.h"
#include "Elevator.h"
#include "Buttonv2.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MovementComponent = GetCharacterMovement();
    MovementComponent->bOrientRotationToMovement = true; // Character will rotate to the direction of movement
    MovementComponent->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // Rotation rate for the character
    MovementComponent->JumpZVelocity = 600.0f; // Jump velocity
    MovementComponent->AirControl = 0.2f; // Air control while jumping

    // Set default interact range
    InteractRange = 500.0f;

    BaseTurnRate = 45.0f;
    BaseLookUpRate = 45.0f;

}

void AMyCharacter::Interact()
{
    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector End = Start + (ForwardVector * InteractRange); 

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); //karakter linetrace e çarpmamasý için

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {/*
     ADoor* Door = Cast<ADoor>(HitResult.GetActor());
        if (Door){
            Door->OpenDoor();
        }
        else {
            AElevator* Elevator = Cast<AElevator>(HitResult.GetActor());
            if (Elevator){
                Elevator->GoUp();
            }
            else {
                AButtonv2* Button = Cast<AButtonv2>(HitResult.GetActor());
                if (Button) {
                    Button->Activate();
            }
            }
        }
     */
      if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
            {
                IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(HitResult.GetActor());
                if (InteractableActor)
                {
                    UE_LOG(LogTemp, Warning, TEXT("MyCharacter is Calling Interface"));
                    InteractableActor->Interact();
                }
            }
     
    
     
        OnInteract.Broadcast(HitResult.GetActor());
     
    }
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // Move forward
        AddMovementInput(Direction, Value);
    }
}

void AMyCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // Find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Move right
        AddMovementInput(Direction, Value);
    }
}

void AMyCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUpAtRate);


	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);
}

