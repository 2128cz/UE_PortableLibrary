// Copyright 2128cz, Inc. All Right Reserved.


#include "ItemManagement/ItemManagementComponent.h"
#include "GameFramework/Actor.h"
#include "Templates/UnrealTemplate.h"
#include <math.h>

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
	// ActorInstance->IsPendingKill(); 可以用，但会被编译器嫌弃
	if (ActorInstance && !IsValid(ActorInstance)) {
		int32 Eleindex;
		InstanceContainer.Find(ActorInstance, Eleindex);
		if (Eleindex >= 0) return false;
		InstanceContainer.Add(ActorInstance);
		if (!
		ActorInstance->OnDestroyed.IsAlreadyBound(this, &UItemManagementComponent::V1_OnDestroyed))
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
	int32* findindex = ClassContainer.Find(ActorClass);
	if (findindex >= 0) {
		TArray<int32> values;
		ClassContainer.GenerateValueArray(values);
		values[*findindex] += (Number, (int32)0U);
	}	
	ClassContainer.Add(ActorClass, std::max(Number, (int32)0U));
}

// 类容器按类数量减少
void UItemManagementComponent::V2_RemoveAClassByClass(UClass* ActorClass, int32 Number)
{
	const int32* findindex = ClassContainer.Find(ActorClass);
	if (findindex >= 0) {
		TArray<int32> values;
		ClassContainer.GenerateValueArray(values);
		values[*findindex] -= std::max(Number, (int32)0U);
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
		values[*findindex] = SetNumber ? std::max(Number, (int32)0U) : Number;
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
bool UItemManagementComponent::V2_GetAClassByInst(AActor* ActorClass, int32& Number)
{
	return V2_GetAClassByClass(ActorClass->GetClass(), Number);
}

// 类容器按类获取
bool UItemManagementComponent::V2_GetAClassByClass(UClass* ActorClass, int32& Number)
{
	Number = *ClassContainer.Find(ActorClass);
	return Number >= 0;
}

// 类容器按索引获取
bool UItemManagementComponent::V2_GetAClassByIndex(int32 Index, UClass*& ActorClass, int32& Number)
{
	TArray<UClass*> keys;
	ClassContainer.GenerateKeyArray(keys);
	TArray<int32> values;
	ClassContainer.GenerateValueArray(values);
	ActorClass = keys[Index];
	Number = (int32)values[Index];
	return Index <= ClassContainer.Num() && Index >= 0;
}

// === 3号容器操作 ===|TODO

// 独有实例添加
void UItemManagementComponent::V3_AddSingleInst(AActor* Actor, bool Focus = false)
{
	if (Focus && IsValid(Actor)) return;
	SingleContainer = Actor;
}

// 独有实例移除（条件移除）
void UItemManagementComponent::V3_RemoveSingleInst(AActor* Actor)
{
	if (SingleContainer == Actor)
		SingleContainer = nullptr;
}

// 独有实例清空（无条件移除）
void UItemManagementComponent::V3_CleanSingleInst()
{
	SingleContainer = nullptr;
}

// 获取独有实例
bool UItemManagementComponent::V3_GetSingleInst(AActor*& Actor)
{
	Actor = SingleContainer;
	return IsValid(SingleContainer);
}

// === 4号容器操作 ===|TODO

// 对象按实例添加
bool UItemManagementComponent::V4_AddActorInst(AActor* Actor)
{
	if (IsValid(Actor) && !BooleanContainer.Array().Find(Actor)) {
		BooleanContainer.Add(Actor);
		Actor->OnDestroyed.AddDynamic(this, &UItemManagementComponent::V4_OnDestroyed);
		return true;
	}
	return false;
}

// 对象按实例移除
bool UItemManagementComponent::V4_RemoveActorInst(AActor* Actor)
{
	if (Actor) {
		BooleanContainer.Remove(Actor);
		Actor->OnDestroyed.RemoveDynamic(this, &UItemManagementComponent::V4_OnDestroyed);
		return true;
	}
	return false;
}

// 对象组按实例添加
bool UItemManagementComponent::V4_AddActorInstArray(TArray<AActor*> Actors)
{
	if(Actors.IsEmpty()) return false;
	TArray<AActor*> Transfer;
	TArray<AActor*> NotTransfer;
	if (V4_FuncIsArrayForTransfer(Actors, 0.1f, Transfer, NotTransfer))
		OnV4ChangeArrayMore.Broadcast(NotTransfer);
	else
		OnV4ChangeArrayMore.Broadcast(Actors);
	BooleanContainer.Append(Actors);
	return true;
}

// 对象组按实例移除
bool UItemManagementComponent::V4_RemoveActorInstArray(TArray<AActor*> Actors)
{
	if (Actors.IsEmpty()) return false;
	TArray<AActor*> Transfer;
	TArray<AActor*> NotTransfer;
	if (V4_FuncIsArrayForTransfer(Actors, 0.9f, Transfer, NotTransfer)) {
		for (AActor* Actor : Transfer) {
			BooleanContainer.Remove(Actor);
		}
		OnV4ChangeArrayMore.Broadcast(NotTransfer);
	}
	else
		OnV4ChangeArrayMore.Broadcast(Actors);
	return true;
}

// 对象组按实例替换
void UItemManagementComponent::V4_SetActorInstArray(TArray<AActor*> Actors)
{
	V4_CleanContainer();
	V4_AddActorInstArray(Actors);
}

// 对象组交集
bool UItemManagementComponent::V4_FuncIntersection(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output)
{
	if (Actors.IsEmpty()) { Output = BooleanContainer; return false; }
	TSet<AActor*> SetActor(Actors);
	if (AndKeepSave) {
		Output = BooleanContainer;
		return V4_RemoveActorInstArray(BooleanContainer.Difference(SetActor).Array());
	}
	Output = BooleanContainer.Intersect(SetActor);
	return true;
}

// 对象组并集
bool UItemManagementComponent::V4_FuncUnion(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output)
{
	if (Actors.IsEmpty()) { Output = BooleanContainer; return false; }
	TSet<AActor*> SetActor(Actors);
	if (AndKeepSave) {
		Output = BooleanContainer;
		return V4_AddActorInstArray(SetActor.Difference(BooleanContainer).Array());
	}
	Output = BooleanContainer.Union(SetActor);
	return true;
}

// 对象组差集
bool UItemManagementComponent::V4_FuncDifference(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output)
{
	if (Actors.IsEmpty()) { Output = BooleanContainer; return false; }
	TSet<AActor*> SetActor(Actors);
	if (AndKeepSave) {
		Output = BooleanContainer;
		return V4_RemoveActorInstArray(BooleanContainer.Intersect(SetActor).Array());
	}
	Output = BooleanContainer.Difference(SetActor);
	return true;
}

// 获取对象组
TArray<AActor*> UItemManagementComponent::V4_GetActorArray()
{
	return BooleanContainer.Array();
}

// 清空对象组
bool UItemManagementComponent::V4_CleanContainer()
{
	if (BooleanContainer.IsEmpty()) return false;
	V4_RemoveActorInstArray(BooleanContainer.Array());
	return true;
}

// 校验输入组是否为传送
bool UItemManagementComponent::V4_FuncIsArrayForTransfer(TArray<AActor*> Actors, float Threshold, TArray<AActor*>& ValidTrans, TArray<AActor*>& OtherTrans)
{
	TSet<AActor*> ArraySetA(Actors);
	TArray<AActor*> ArraySetB(Actors);
	ArraySetB = TransferContainer.Intersect(ArraySetA).Array();
	if (ArraySetB.Num() / TransferContainer.Num() >= Threshold) {
		ValidTrans = ArraySetB;
		OtherTrans = ArraySetA.Intersect(TransferContainer).Array();
		TransferContainer.Reset();
		return true;
	}
	return false;
}

// 校验对象是否为传送
bool UItemManagementComponent::V4_FuncIsActorForTransfer(AActor* Actor)
{
	return TransferContainer.Contains(Actor);
}

// === 5号容器操作 ===|TODO

// 更新对象动态组筛选器 实例区分模式
void UItemManagementComponent::V5_UpdataSizer(TArray<AActor*> TargetActors, bool IgoneVes4, TArray<AActor*>& ExcrActors, TArray<AActor*>& MissActor)
{
	TArray<AActor*> ActorsNum(SizerContainer.Array());
	if (TargetActors == ActorsNum) return;
	TSet<AActor*> ActorSet(TargetActors);
	if (IgoneVes4) ActorSet = ActorSet.Difference(BooleanContainer);
	ExcrActors = ActorSet.Difference(SizerContainer).Array();
	if (!ExcrActors.IsEmpty()) OnV5ChangeArrayMore.Broadcast(ExcrActors);
	MissActor = SizerContainer.Difference(ActorSet).Array();
	if (!MissActor.IsEmpty()) OnV5ChangeArrayLess.Broadcast(MissActor);
	SizerContainer = ActorSet;
}

// 对象组筛选器传送
TArray<AActor*> UItemManagementComponent::V5_OnTransmit()
{
	TArray<AActor*> Actors(SizerContainer.Array());
	TransferContainer.Empty(SizerContainer.Num());
	TransferContainer.Append(SizerContainer);
	SizerContainer.Empty();
	return Actors;
}

// 对象动态组重置
void UItemManagementComponent::V5_Clean()
{
	OnV5ChangeArrayLess.Broadcast(SizerContainer.Array());
	SizerContainer.Empty();
}

// 获取对象动态组
TArray<AActor*> UItemManagementComponent::V5_GetActors()
{
	return SizerContainer.Array();
}

// 筛选器数据从回收站恢复
bool UItemManagementComponent::V5_RecoveryTransferData()
{
	if (TransferContainer.IsEmpty())return false;
	SizerContainer.Empty(TransferContainer.Num());
	SizerContainer.Append(TransferContainer);
	return true;
}

// 当1号容器内实例发生销毁事件
void UItemManagementComponent::V1_OnDestroyed(AActor* DestroyedActor)
{
	OnV1DestructionArrive.Broadcast(DestroyedActor);
	V1_RemoveActorByInst(DestroyedActor);
}

void UItemManagementComponent::V4_OnDestroyed(AActor* DestroyedActor)
{
	OnV4DestructionArrive.Broadcast(DestroyedActor);
	V4_RemoveActorInst(DestroyedActor);
}

