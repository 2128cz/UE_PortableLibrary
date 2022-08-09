// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemManagementComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FWhenDestructionArrive, AActor, OnDestroyed, AActor*, DestroyedActor);

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

private:
	UFUNCTION()
		void V1_OnDestroyed(AActor* DestroyedActor);

	//========================================================
	// TODO
	// 1号容器：实例容器
	// 可以使用 V1_AddActorByInst() 和 V1_RemoveActorByInst() 来移除其中的项目
	// 主要功能是可以在保存实例的同时能够在实例被外部销毁时一同清理此处的项目
	// 
	//========================================================

protected:
	UPROPERTY( EditAnywhere, 
		BlueprintReadOnly,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DisplayName = "纯实例容器(容器1)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
	TArray<AActor*> InstanceContainer;

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DisplayName = "容器1内发生融毁事件时")
	)
	FWhenDestructionArrive V1_WhenDestructionArrive;

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagement")
	void TESTFUNC();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "向容器1添加一个实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES1"),
		meta = (KeyWords = "add set instance 1"), 
		meta = (ShortToolTip = "向容器添加一个实例"),
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
		meta = (ShortToolTip = "移除容器中一个实例"),
		meta = (ToolTip = "移除容器1中一个对象实例。")
	)
	bool V1_RemoveActorByInst(AActor* ActorInstance);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "获取容器集合"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "GET VES1"),
		meta = (KeyWords = "get instance 1"),
		meta = (ShortToolTip = "获取实例容器内容"),
		meta = (ToolTip = "获取1号实例容器内容，你也可以直接获取变量 @InstanceContainer")
	)
	TArray<AActor*> V1_GetActorInst();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "清空容器"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "VES1 REMOVE"),
		meta = (KeyWords = "Remove clean instance 1"),
		meta = (ShortToolTip = "1号实例容器清空"),
		meta = (ToolTip = "清空1号实例容器，这个操作可以同时解放目标的与此处的清理相关绑定")
	)
	void V1_CleanActorInst();

	//========================================================
	// TODO
	// 2号容器：实例类容器
	// 可以根据实例的类型来保存一个类索引，每次的实例添加将转为这个类索引下的计数
	// 
	//========================================================

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DisplayName = "类容器(容器2)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
		TMap<UClass*, int32> ClassContainer;



	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按实例添加"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES2"),
		meta = (KeyWords = " add class instance 2"),
		meta = (ShortToolTip = "2号实例类容器增加"),
		meta = (ToolTip = "按实例类型向实例类容器添加一个项目，@AndDestroy 可选择删除")
	)
		bool V2_AddAClassByInst(AActor* ActorInstance, bool AndDestroy);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按实例移除"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		// meta = (CompactNodeTitle = "REMOVE VES2"),
		meta = (KeyWords = "remove class instance 2"),
		meta = (ShortToolTip = "2号实例类容器减少"),
		meta = (ToolTip = "按实例类型移除实例类容器中的一个项目")
	)
		bool V2_RemoveAClassByInst(AActor* ActorInstance);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按类增加"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "class item add ++ instance 2"),
		meta = (ShortToolTip = "2号实例类容器增加"),
		meta = (ToolTip = "按类增加实例类容器中的项目数量，只考虑正数，负数会被忽略")
	)
		void V2_AddAClassByClass(UClass* ActorClass, int32 Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按类减少"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "class item sub -- instance 2"),
		meta = (ShortToolTip = "2号实例类容器减少"),
		meta = (ToolTip = "按类减少实例类容器中的项目数量，只考虑正数，负数会被忽略")
	)
		void V2_RemoveAClassByClass(UClass* ActorClass, int32 Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按类设置"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "class item change instance 2"),
		meta = (ShortToolTip = "2号实例类容器变更"),
		meta = (ToolTip = "按类设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
		void V2_SetAClassByClass(UClass* ActorClass, int32 Number, bool SetNumber = true);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按索引增加"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "index item add ++ instance 2"),
		meta = (ShortToolTip = "2号实例类容器增加"),
		meta = (ToolTip = "按索引增加实例类容器中的项目数量，只考虑正数，负数会被忽略")
	)
		void V2_AddAClassByIndex(int32 Index, int32 Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按索引减少"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "index item sub -- instance 2"),
		meta = (ShortToolTip = "2号实例类容器减少"),
		meta = (ToolTip = "按索引减少实例类容器中的项目数量，只考虑正数，负数会被忽略")
	)
		void V2_RemoveAClassByIndex(int32 Index, int32 Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按索引设置"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "index item change instance 2"),
		meta = (ShortToolTip = "2号实例类容器变更"),
		meta = (ToolTip = "按索引设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
		void V2_SetAClassByIndex(int32 Index, int32 Number, bool SetNumber = true);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按实例获取对象类容器2内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "get instance 2"),
		meta = (ShortToolTip = "2号实例类容器减少"),
		meta = (ToolTip = "按索引减少实例类容器中的项目数量，只考虑正数，负数会被忽略")
	)
		bool V2_GetAClassByInst(AActor* ActorClass, int32*& Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按类获取对象类容器2内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "get instance 2"),
		meta = (ShortToolTip = "2号实例类容器变更"),
		meta = (ToolTip = "按索引设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
		bool V2_GetAClassByClass(UClass* ActorClass, int32*& Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按索引获取对象类容器2内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "VES2 "),
		meta = (KeyWords = "get instance 2"),
		meta = (ShortToolTip = "2号实例类容器变更"),
		meta = (ToolTip = "按索引设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
		bool V2_GetAClassByIndex(int32 Index, UClass*& ActorClass, int32*& Number);

	//========================================================
	// 
	// 3号容器：实例容器
	//  
	// 
	//========================================================




};

