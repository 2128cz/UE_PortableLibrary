// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stats/Stats.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectBaseUtility.h"
#include "UObject/Object.h"
#include "InputCoreTypes.h"
#include "Templates/SubclassOf.h"
#include "UObject/CoreNet.h"
#include "Engine/EngineTypes.h"
#include "Engine/EngineBaseTypes.h"
#include "ComponentInstanceDataCache.h"
#include "Components/ChildActorComponent.h"
#include "RenderCommandFence.h"
#include "Misc/ITransaction.h"
#include "Engine/Level.h"

#include "ItemManagementComponent.generated.h"

//多用途定义
#define CUSLANG 1
#define CUSNAPI 0

UCLASS( Blueprintable, 
	ClassGroup=(ItemManagement), 
	meta = (BlueprintSpawnableComponent),
	meta = (ToolTip = "物品管理组件")
)
#if CUSNAPI
class Your project name_API UItemManagementComponent : public UActorComponent
#else
class AUE5TESTPRO_API UItemManagementComponent : public UActorComponent
#endif
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemManagementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		TArray<AActor*> InstanceContainer;

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
#if CUSLANG
		meta = (DefaultToSelf),
		meta = (DisplayName = "向容器1添加一个实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES1"),
		meta = (KeyWords = "add set instance 1"), 
		meta = (ShortToolTip = "向实例容器1添加一个实例"),
		meta = (ToolTip = "向1号实例容器添加一个实例")
#endif
	)
	bool V1_AddActorByInst(AActor* ActorInstance);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
#if CUSLANG
		meta = (DefaultToSelf),
		meta = (DisplayName = "在容器1中移除一个对象实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "SUB VES1"),
		meta = (KeyWords = "sub remove instance 1"),
		meta = (ShortToolTip = "移除容器1中一个对象实例"),
		meta = (ToolTip = "移除容器1中一个对象实例。")
#endif
	)
	bool V1_RemoveActorByInst(AActor* ActorInstance);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
#if CUSLANG
		meta = (DefaultToSelf),
		meta = (DisplayName = "获取容器1内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "GET V1"),
		meta = (KeyWords = "get instance 1"),
		meta = (ShortToolTip = "获取1号实例容器内容"),
		meta = (ToolTip = "获取1号实例容器内容，你也可以直接获取变量 @InstanceContainer")
#endif
	)
	TArray<AActor*> V1_GetActorInst();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
#if CUSLANG
		meta = (DefaultToSelf),
		meta = (DisplayName = "清空容器1"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "V1 REMOVE"),
		meta = (KeyWords = "Remove clean instance 1"),
		meta = (ShortToolTip = "1号实例容器清空"),
		meta = (ToolTip = "清空1号实例容器，这个操作可以同时解放目标的与此处的清理相关绑定")
#endif
	)
	void V1_CleanActorInst();

	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FActorDestroyedSignature, AActor, OnDestroyed, AActor*, DestroyedActor);
	void V1_WhenDestructionArrive();
};

