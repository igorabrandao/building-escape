// Copyright Igor Brandão 2021

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Check if the current component has a PressurePlate set
	if (!this->PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the openDoor component on it, but no pressureplate set!"), *GetOwner()->GetName());
	}

	// Get the current door rotation
	this->DoorRotation = GetOwner()->GetActorRotation();
	this->InitialYaw = this->DoorRotation.Yaw;
	this->OpenAngle += this->InitialYaw;

	// Get the current player
	this->ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if the player cross the pressure plate zone
	if (this->PressurePlate && this->PressurePlate->IsOverlappingActor(this->ActorThatOpen))
	{
		this->OpenDoor(DeltaTime);
		this->DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - this->DoorLastOpened > this->DoorCloseDelay)
		{
			this->CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	this->DoorRotation.Yaw = FMath::FInterpTo(this->DoorRotation.Yaw, this->OpenAngle, DeltaTime, this->DoorOpenSpeed);
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	this->DoorRotation.Yaw = FMath::FInterpTo(this->DoorRotation.Yaw, this->InitialYaw, DeltaTime, this->DoorCloseSpeed);
	GetOwner()->SetActorRotation(DoorRotation);
}