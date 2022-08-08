// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemManagementComponent.generated.h"


UCLASS( Blueprintable, 
	ClassGroup=(ItemManagement), 
	meta = (BlueprintSpawnableComponent),
	meta = (ToolTip = "物品管理组件")
)
class AUE5TESTPRO_API UItemManagementComponent : public UActorComponent
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
	UPROPERTY( EditAnywhere, 
		BlueprintReadOnly,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DisplayName = "纯实例容器(容器1)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
	TArray<AActor*> InstanceContainer;

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "向容器1添加一个实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES1"),
		meta = (KeyWords = "add set instance 1"), 
		meta = (ShortToolTip = "向实例容器1添加一个实例"),
		meta = (ToolTip = "向1号实例容器添加一个实例")
	)
	bool V1_AddActorByInst(AActor* ActorInstance);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "在容器1中移除一个对象实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "SUB VES1"),
		meta = (KeyWords = "sub remove instance 1"),
		meta = (ShortToolTip = "移除容器1中一个对象实例"),
		meta = (ToolTip = "移除容器1中一个对象实例。")
	)
	bool V1_RemoveActorByInst(AActor* ActorInstance);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "获取容器1内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "GET V1"),
		meta = (KeyWords = "get instance 1"),
		meta = (ShortToolTip = "获取1号实例容器内容"),
		meta = (ToolTip = "获取1号实例容器内容，你也可以直接获取变量 @InstanceContainer")
	)
	TArray<AActor*> V1_GetActorInst();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "清空容器1"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "V1 REMOVE"),
		meta = (KeyWords = "Remove clean instance 1"),
		meta = (ShortToolTip = "1号实例容器清空"),
		meta = (ToolTip = "清空1号实例容器，这个操作可以同时解放目标的与此处的清理相关绑定")
	)
	void V1_CleanActorInst();

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagement|1_InstanceContainer")
		void TESTFUNC();

	/*DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FWhenDestructionArrive, AActor, OnDestroyed, AActor*, DestroyedActor);
	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DisplayName = "容器1内发生融毁事件时")
	)
		FWhenDestructionArrive V1_WhenDestructionArrive;*/

private:
	UFUNCTION()
	void V1_OnDestroyed(AActor* DestroyedActor);

};

