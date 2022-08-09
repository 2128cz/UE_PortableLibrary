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


// === 1号容器操作 ===|TODO

// 对象容器按实例添加
bool UItemManagementComponent::V1_AddActorByInst(AActor* ActorInstance)
{
	// ActorInstance->IsPendingKill();
	if (ActorInstance && !IsValid(ActorInstance)) {
		int32 Eleindex = InstanceContainer.Find(ActorInstance);
		if (Eleindex >= 0) return false;
		InstanceContainer.Add(ActorInstance);
		if (!ActorInstance->OnDestroyed.IsAlreadyBound(this, &UItemManagementComponent::V1_OnDestroyed))
		ActorInstance->OnDestroyed.AddDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
		return true;
	}
	return false;
}

// 对象容器按实例移除
bool UItemManagementComponent::V1_RemoveActorByInst(AActor* ActorInstance)
{
	if (ActorInstance) {
		InstanceContainer.Remove(ActorInstance);
		ActorInstance->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
		return true;
	}
	return false;
}

// 获取对象容器实例数组
TArray<AActor*> UItemManagementComponent::V1_GetActorInst()
{
	return InstanceContainer;
}

// 清空对象容器实例组
void UItemManagementComponent::V1_CleanActorInst()
{
	for (AActor* actor_var: InstanceContainer)
		actor_var->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
	InstanceContainer.Empty();
}

// === 2号容器操作 ===|TODO

// 类容器按实例添加
bool UItemManagementComponent::V2_AddAClassByInst(AActor* ActorInstance, bool AndDestroy)
{
	if (ActorInstance && !IsValid(ActorInstance)) {
		V2_AddAClassByClass(ActorInstance->GetClass(), 1);
		if (AndDestroy) ActorInstance->Destroy();
		return true;
	}
	return false;
}

// 类容器按实例移除
bool UItemManagementComponent::V2_RemoveAClassByInst(AActor* ActorInstance)
{
	if (ActorInstance && !IsValid(ActorInstance)) {
		V2_RemoveAClassByClass(ActorInstance->GetClass(), 1);
		return true;
	}
	return false;
}

// 类容器按类数量增加
void UItemManagementComponent::V2_AddAClassByClass(UClass* ActorClass, int32 Number)
{
	const int32* findindex = ClassContainer.Find(ActorClass);
	if (findindex >= 0) {
		TArray<int32> values;
		ClassContainer.GenerateValueArray(values);
		values[*findindex] += MaxElement(Number, 0);
	}	
	ClassContainer.Add(ActorClass, MaxElement(Number, 0));
}

// 类容器按类数量减少
void UItemManagementComponent::V2_RemoveAClassByClass(UClass* ActorClass, int32 Number)
{
	const int32* findindex = ClassContainer.Find(ActorClass);
	if (findindex >= 0) {
		TArray<int32> values;
		ClassContainer.GenerateValueArray(values);
		values[*findindex] -= MaxElement(Number, 0);
		if (values[*findindex] <= 0) {
			ClassContainer.Remove(ActorClass);
		}
	}
}

// 类容器按类数量设置
void UItemManagementComponent::V2_SetAClassByClass(UClass* ActorClass, int32 Number, bool SetNumber = true)
{
	const int32* findindex = ClassContainer.Find(ActorClass);
	if (findindex >= 0) {
		TArray<int32> values;
		ClassContainer.GenerateValueArray(values);
		values[*findindex] = SetNumber ? MaxElement(Number, 0) : Number;
		if (values[*findindex] <= 0) {
			ClassContainer.Remove(ActorClass);
		}
	}
}

// 类容器按类数量添加
void UItemManagementComponent::V2_AddAClassByIndex(int32 Index, int32 Number)
{
	TArray<UClass*> keys;
	ClassContainer.GenerateKeyArray(keys);
	V2_AddAClassByClass(keys[Index], Number);
}

// 类容器按类数量减少
void UItemManagementComponent::V2_RemoveAClassByIndex(int32 Index, int32 Number)
{
	TArray<UClass*> keys;
	ClassContainer.GenerateKeyArray(keys);
	V2_RemoveAClassByClass(keys[Index], Number);
}

// 类容器按类数量设置
void UItemManagementComponent::V2_SetAClassByIndex(int32 Index, int32 Number, bool SetNumber = true)
{
	TArray<UClass*> keys;
	ClassContainer.GenerateKeyArray(keys);
	V2_SetAClassByClass(keys[Index], Number, SetNumber);
}

// 类容器按实例获取
bool UItemManagementComponent::V2_GetAClassByInst(AActor* ActorClass, int32*& Number)
{
	return V2_GetAClassByClass(ActorClass->GetClass(), Number);
}

// 类容器按类获取
bool UItemManagementComponent::V2_GetAClassByClass(UClass* ActorClass, int32*& Number)
{
	Number = ClassContainer.Find(ActorClass);
	return Number >= 0;
}

// 类容器按索引获取
bool UItemManagementComponent::V2_GetAClassByIndex(int32 Index, UClass*& ActorClass, int32*& Number)
{
	TArray<UClass*> keys;
	ClassContainer.GenerateKeyArray(keys);
	TArray<int32> values;
	ClassContainer.GenerateValueArray(values);
	ActorClass = keys[Index];
	Number = (int32*)values[Index];
	return Index <= ClassContainer.Num() && Index >= 0;
}

// 当1号容器内实例发生销毁事件 TODO
void UItemManagementComponent::V1_OnDestroyed(AActor* DestroyedActor)
{
	InstanceContainer.Remove(DestroyedActor);
	//V1_WhenDestructionArrive.Broadcast(DestroyedActor);
	//DestroyedActor->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V1_OnDestroyed);
	TESTFUNC();
}

