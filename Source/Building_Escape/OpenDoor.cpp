// Copyright Igor Brandão 2021

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Get the current door rotation
	this->DoorRotation = GetOwner()->GetActorRotation();
	this->InitialYaw = this->DoorRotation.Yaw;
	this->TargetYaw += this->InitialYaw;

	// Check if the current component has a PressurePlate set
	if (!this->PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the openDoor component on it, but no pressureplate set!"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if the player cross the pressure plate zone
	if (this->PressurePlate && this->PressurePlate->IsOverlappingActor(this->ActorThatOpen))
	{
		this->OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	this->DoorRotation.Yaw = FMath::FInterpTo(this->DoorRotation.Yaw, this->TargetYaw, DeltaTime, 1.5);
	GetOwner()->SetActorRotation(DoorRotation);
}