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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update the door rotation within a step range
	this->DoorRotation.Yaw = FMath::Lerp(this->DoorRotation.Yaw, this->OpenedDoorYaw, 0.02f);
	GetOwner()->SetActorRotation(DoorRotation);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *DoorRotation.ToString());
}

