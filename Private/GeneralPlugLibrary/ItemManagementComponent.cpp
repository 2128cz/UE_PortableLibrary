// Copyright 2128cz, Inc. All Right Reserved.


#include "GeneralPlugLibrary/ItemManagementComponent.h"

// Sets default values for this component's properties
UItemManagementComponent::UItemManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemManagementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemManagementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UItemManagementComponent::V1_AddActorByInst(AActor* ActorInstance)
{
	//int32 index;
	InstanceContainer.Emplace(ActorInstance);
	return false;
}

