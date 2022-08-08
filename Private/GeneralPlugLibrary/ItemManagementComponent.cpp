// Copyright 2128cz, Inc. All Right Reserved.


#include "GeneralPlugLibrary/ItemManagementComponent.h"
#include "GameFramework/Actor.h"

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
	if (ActorInstance && !ActorInstance->IsPendingKill()) {
		int32 Eleindex = InstanceContainer.Find(ActorInstance);
		if (Eleindex >= 0) return false;
		InstanceContainer.Emplace(ActorInstance);
		ActorInstance->OnDestroyed.AddDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
		return true;
	}
	return false;
}

bool UItemManagementComponent::V1_RemoveActorByInst(AActor* ActorInstance)
{
	if (ActorInstance) {
		InstanceContainer.Remove(ActorInstance);
		ActorInstance->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
		return true;
	}
	return false;
}

TArray<AActor*> UItemManagementComponent::V1_GetActorInst()
{
	return InstanceContainer;
}

void UItemManagementComponent::V1_CleanActorInst()
{
	for (AActor* actor_var: InstanceContainer)
		actor_var->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
	InstanceContainer.Empty();
}

void UItemManagementComponent::V1_OnDestroyed(AActor* DestroyedActor)
{
	InstanceContainer.Remove(DestroyedActor);
	DestroyedActor->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
	TESTFUNC();
}

