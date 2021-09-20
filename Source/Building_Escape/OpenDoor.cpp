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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update the door rotation within a step range
	//this->DoorRotation.Yaw = FMath::Lerp(this->DoorRotation.Yaw, this->TargetYaw, 0.02f);
	//this->DoorRotation.Yaw = FMath::FInterpConstantTo(this->DoorRotation.Yaw, this->OpenedDoorYaw, DeltaTime, 45);
	this->DoorRotation.Yaw = FMath::FInterpTo(this->DoorRotation.Yaw, this->TargetYaw, DeltaTime, 1.5);
	GetOwner()->SetActorRotation(DoorRotation);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *DoorRotation.ToString());
}
