// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/SparseDelegate.h"
#include "ItemManagementComponent.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnV1DestructionArriveSignature, AActor*, DestroyedActor);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnV4DestructionArriveSignature, AActor*, DestroyedActor);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnV4ChangeArrayMoreSignature, TArray<AActor*>, ChangeActors);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnV4ChangeArrayLessSignature, TArray<AActor*>, ChangeActors);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnV5ChangeArrayMoreSignature, TArray<AActor*>, ChangeActors);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnV5ChangeArrayLessSignature, TArray<AActor*>, ChangeActors);



UCLASS( Blueprintable, 
	ClassGroup=(GeneralPlugLibrary),
	meta = (BlueprintSpawnableComponent),
	meta = (ToolTip = "物品管理组件")
)
class GENERALPLUGLIBRARY_API UItemManagementComponent : public UActorComponent
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

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DisplayName = "容器1内发生融毁事件时")
	)
		FOnV1DestructionArriveSignature OnV1DestructionArrive;

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|4_InstanceContainer",
		meta = (DisplayName = "容器4内发生融毁事件时")
	)
		FOnV4DestructionArriveSignature OnV4DestructionArrive;

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|4_InstanceContainer",
		meta = (DisplayName = "容器4内发生内容变更时_增加组")
	)
		FOnV4ChangeArrayMoreSignature OnV4ChangeArrayMore;

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|4_InstanceContainer",
		meta = (DisplayName = "容器4内发生内容变更时_减少组")
	)
		FOnV4ChangeArrayLessSignature OnV4ChangeArrayLess;

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DisplayName = "容器5内发生内容变更时_增加组")
	)
		FOnV5ChangeArrayMoreSignature OnV5ChangeArrayMore;

	UPROPERTY(BlueprintAssignable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DisplayName = "容器5内发生内容变更时_减少组")
	)
		FOnV5ChangeArrayLessSignature OnV5ChangeArrayLess;

	UFUNCTION()
		void V1_OnDestroyed(AActor* DestroyedActor);
	UFUNCTION()
		void V4_OnDestroyed(AActor* DestroyedActor);

	//========================================================
	// TODO
	// 1号容器：实例容器 （多形体碰撞管理）
	// 容器插槽1用于纯实例对象加入或移除，依赖于运行中的实例，如果某实例在这之后被销毁，那么将会自动清理废引用，并产生一个发生销毁事件
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

	UFUNCTION(BlueprintCallable, BlueprintPure, 
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
	// 2号容器：实例类容器 （物品捡拾买卖管理）
	// 容器插槽2用于存储对象类，最好在存储后进行移除，否则有可能造成多次加入，
	// 在添加时勾选“添加时移除实例”即可。针对有可能使用索引回调的控件事件，提供了按索引更新的函数
	// 
	//========================================================

protected:

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "ItemManagement|2_ClassContainer",
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
		//meta = (CompactNodeTitle = "ADD VES2 BY ACTOR"),
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
		// meta = (CompactNodeTitle = "REMOVE VES2 BY ACTOR"),
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
		//meta = (CompactNodeTitle = "ADD VES2 BY CLASS"),
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
		//meta = (CompactNodeTitle = "SUB VES2 BY CLASS"),
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
		//meta = (CompactNodeTitle = "SET VES2 BY CLASS"),
		meta = (KeyWords = "class item change instance 2"),
		meta = (ShortToolTip = "2号实例类容器变更"),
		meta = (ToolTip = "按类设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
	void V2_SetAClassByClass(UClass* ActorClass, int32 Number, bool SetNumber);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "对象类容器2按索引增加"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES2 BY INDEX"),
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
		//meta = (CompactNodeTitle = "SUB VES2 BY INDEX"),
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
		//meta = (CompactNodeTitle = "SET VES2 VALUE BY INDEX"),
		meta = (KeyWords = "index item change instance 2"),
		meta = (ShortToolTip = "2号实例类容器变更"),
		meta = (ToolTip = "按索引设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
	void V2_SetAClassByIndex(int32 Index, int32 Number, bool SetNumber);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按实例获取对象类容器2内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "GET VES2 BY ACTOR"),
		meta = (KeyWords = "get class 2"),
		meta = (ShortToolTip = "获取2号实例类容器"),
		meta = (ToolTip = "按索引减少实例类容器中的项目数量，只考虑正数，负数会被忽略")
	)
	bool V2_GetAClassByInst(AActor* ActorClass, int32& Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按类获取对象类容器2内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "GET VES2 BY CLASS"),
		meta = (KeyWords = "change class 2"),
		meta = (ShortToolTip = "获取2号实例类容器"),
		meta = (ToolTip = "按索引设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
	bool V2_GetAClassByClass(UClass* ActorClass, int32& Number);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|2_ClassContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按索引获取对象类容器2内容"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "GET VES2 BY INDEX"),
		meta = (KeyWords = "get class 2"),
		meta = (ShortToolTip = "获取2号实例类容器"),
		meta = (ToolTip = "按索引设置实例类容器中项目数量，@SetNumber 可选择是否直接设置为数值，否则将基于当前值进行运算")
	)
	bool V2_GetAClassByIndex(int32 Index, UClass*& ActorClass, int32& Number);

	//========================================================
	// TODO
	// 3号容器：独有容器 （单形体捕捉）
	// 容器插槽3只存储一个对象，但可以用于有多形体碰撞的情况，
	// 通过勾选“当插槽为空时添加”选项，限制加入的对象，
	// 并且在移除时，可以只针对插槽内的对象，也就是说可以和插槽1放置在一起使用。
	// 
	//========================================================

protected:

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "ItemManagement|3_SingleContainer",
		meta = (DisplayName = "独有容器(容器3)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
	AActor* SingleContainer;

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|3_SingleContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "添加实例到独有容器3"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES3"),
		meta = (KeyWords = "add instance 3"),
		meta = (ShortToolTip = "向3号独有容器添加实例"),
		meta = (ToolTip = "保存一个独特实例，取消专注选项 @Focus 可以不论保存值如何直接写入")
	)
	void V3_AddSingleInst(AActor* Actor, bool Focus);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|3_SingleContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "移除独有容器3的实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "REMOVE VES3"),
		meta = (KeyWords = "remove instance 3"),
		meta = (ShortToolTip = "移除3号独有容器中的实例"),
		meta = (ToolTip = "移除一个独特实例")
	)
	void V3_RemoveSingleInst(AActor* Actor);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|3_SingleContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "清空独有容器3"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "CLEAN VES3"),
		meta = (KeyWords = "remove instance 3"),
		meta = (ShortToolTip = "移除3号独有容器中的实例"),
		meta = (ToolTip = "移除一个独特实例")
	)
	void V3_CleanSingleInst();

	UFUNCTION(BlueprintCallable, BlueprintPure,
		Category = "ItemManagement|3_SingleContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "获取独有容器3的实例"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		meta = (CompactNodeTitle = "GET VES3"),
		meta = (KeyWords = " instance 3"),
		meta = (ShortToolTip = "获取3号独有容器中的实例"),
		meta = (ToolTip = "获取独特实例")
	)
	bool V3_GetSingleInst(AActor*& Actor);

	//========================================================
	// TODO
	// 4号容器：布尔容器 （对象数组带布尔运算管理）
	// 容器插槽4用于一次性存储多个对象，可以用于玩家框选时的操作，
	// 并且针对框选，框选组布尔，编组等操作封装了特有函数，其主要操作功能和插槽1基本类似
	// 移除了手动开启自动清理的选项，默认开启，这可能会影响到插槽5行为。
	//========================================================

protected:

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DisplayName = "布尔容器(容器4)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
	TSet<AActor*> BooleanContainer;

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按实例添加到布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES4"),
		meta = (KeyWords = "add instance 4"),
		meta = (ShortToolTip = "添加实例到4号布尔容器"),
		meta = (ToolTip = "布尔容器添加一个实例")
	)
	bool V4_AddActorInst(AActor* Actor);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按实例移除布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "REMOVE VES4"),
		meta = (KeyWords = "remove instance 4"),
		meta = (ShortToolTip = "移除实例到4号布尔容器"),
		meta = (ToolTip = "布尔容器移除一个实例")
	)
	bool V4_RemoveActorInst(AActor* Actor);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按实例组添加布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD ARRAY VES4"),
		meta = (KeyWords = "add instance 4"),
		meta = (ShortToolTip = "添加一组实例到4号布尔容器"),
		meta = (ToolTip = "布尔容器添加一组实例")
	)
	bool V4_AddActorInstArray(TArray<AActor*> Actors);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "按实例组移除布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "REMOVE ARRAY VES4"),
		meta = (KeyWords = "remove instance 4"),
		meta = (ShortToolTip = "移除一组实例到4号布尔容器"),
		meta = (ToolTip = "布尔容器移除一组实例")
	)
	bool V4_RemoveActorInstArray(TArray<AActor*> Actors);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "替换布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "SET VES4"),
		meta = (KeyWords = "set instance 4"),
		meta = (ShortToolTip = "替换4号布尔容器"),
		meta = (ToolTip = "布尔容器替换，此操作不会产生回收回调等事件，类似初始化")
	)
	void V4_SetActorInstArray(TArray<AActor*> Actors);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "交集操作布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "INTERSECTION  VES4"),
		meta = (KeyWords = "operation logic add + instance 4"),
		meta = (ShortToolTip = "4号布尔容器交集运算"),
		meta = (ToolTip = "布尔容器交集运算/n如果需要将计算进行分步操作，可以开启 @AndKeepSave以维持存储不变")
	)
	bool V4_FuncIntersection(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "并集操作布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "UNION VES4"),
		meta = (KeyWords = "operation logic add + instance 4"),
		meta = (ShortToolTip = "4号布尔容器并集运算"),
		meta = (ToolTip = "布尔容器并集运算/n如果需要将计算进行分步操作，可以开启 @AndKeepSave以维持存储不变")
	)
	bool V4_FuncUnion(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "差集操作布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "DIFFERENCE VES4"),
		meta = (KeyWords = "operation logic sub - instance 4"),
		meta = (ShortToolTip = "4号布尔容器差集运算"),
		meta = (ToolTip = "布尔容器差集运算/n如果需要将计算进行分步操作，可以开启 @AndKeepSave以维持存储不变")
	)
	bool V4_FuncDifference(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output);

	UFUNCTION(BlueprintCallable, BlueprintPure,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "获取对象组布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "GET VES4"),
		meta = (KeyWords = "get instance 4"),
		meta = (ShortToolTip = "获取4号布尔容器"),
		meta = (ToolTip = "获取布尔容器内容")
	)
	TArray<AActor*> V4_GetActorArray();

	UFUNCTION(BlueprintCallable, 
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "清空布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "CLEAN VES4"),
		meta = (KeyWords = "clean array instance 4"),
		meta = (ShortToolTip = "清空4号布尔容器"),
		meta = (ToolTip = "清空布尔容器内容")
	)
	bool V4_CleanContainer();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "校验输入是为传送布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "IS TRANSFER VES4"),
		meta = (KeyWords = "check valid instance 4"),
		meta = (ShortToolTip = "校验输入与4号布尔容器"),
		meta = (ToolTip = "输入对象与本地传送对象进行比较，当输入值匹配度超过阈值时将其视作完整传送对象。")
	)
	bool V4_FuncIsArrayForTransfer(TArray<AActor*> Actors, float Threshold, TArray<AActor*>& ValidTrans, TArray<AActor*>& OtherTrans);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|4_BooleanContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "校验传送对象布尔容器4"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "IS TRANSFER VES4"),
		meta = (KeyWords = "check valid instance 4"),
		meta = (ShortToolTip = "校验对象与4号布尔容器"),
		meta = (ToolTip = "将单个对象与布尔容器传送内容进行校验")
	)
	bool V4_FuncIsActorForTransfer(AActor* Actor);

	//========================================================
	// TODO
	// 5号容器：即时容器 （即时对象数组对象变动管理）
	// 用于检测时多对象内容发生变更的对象，并产生相应事件；
	// 此插槽可以用来保存对象，但并不固定，且没有清理计划，不建议从此处获取持久引用。
	// 主要功能和插槽4类似；独立使用时可以用分发器获取物品变动。
	// 
	// 如需和插槽4配合使用，可以使用特别封装的传送函数，将减少移动物品引用时变更分发器事件的发生；
	// 更新时如果需要忽略浏览的高亮事件作用于已选择的对象（指插槽4中的内容），勾选忽略选项即可。
	// 
	// 当前版本的传送后回收功能受插槽4的自动清理功能限制
	// 会在不自动清理时不检查传送内容，导致回收站保持内容，本意是可以通过不清理来执行多次运算。
	// 
	//========================================================

protected:

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DisplayName = "即时容器(容器5)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
		TSet<AActor*> SizerContainer;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DisplayName = "传送容器(容器5)"),
		meta = (HideAlphaChannel),
		meta = (NoGetter)
	)
		TSet<AActor*> TransferContainer;

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "更新对象组筛选器即时容器5"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "UPDATA VES5"),
		meta = (KeyWords = "add updata instance 5"),
		meta = (ShortToolTip = "更新对象组5号即时容器"),
		meta = (ToolTip = "更新即时容器内容")
	)
		void V5_UpdataSizer(TArray<AActor*> TargetActors, bool IgoneVes4, TArray<AActor*>& ExcrActors, TArray<AActor*>& MissActor);

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "传送即时容器5"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "TRANSFER VES5"),
		meta = (KeyWords = "get for transfer instance 5"),
		meta = (ShortToolTip = "5号即时容器传送"),
		meta = (ToolTip = "此操作将即时容器内容标记为传送，下一步可以连接到容器4的布尔操作中，目的是减少从框选到选定的内容转移时多出的操作")
	)
		TArray<AActor*> V5_OnTransmit();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "清除即时容器5"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "TRANSFER VES5"),
		meta = (KeyWords = "remove instance 5"),
		meta = (ShortToolTip = "5号即时容器清除"),
		meta = (ToolTip = "此操作将即时容器内容清除，这通常用于取消上一步操作，如果是传送数据则不需要使用清除，此操作不能恢复")
	)
		void V5_Clean();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "获取即时容器5"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "TRANSFER VES5"),
		meta = (KeyWords = "get instance 5"),
		meta = (ShortToolTip = "获取5号即时容器"),
		meta = (ToolTip = "获取即时容器内容")
	)
		TArray<AActor*> V5_GetActors();

	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|5_ImmediatelyContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "取消传送即时容器5"),
		//meta = (ExpandEnumAsExecs = ""),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "TRANSFER VES5"),
		meta = (KeyWords = "recover instance 5"),
		meta = (ShortToolTip = "5号即时容器取消传送"),
		meta = (ToolTip = "此操作将即时容器上一步已经传送的内容恢复到本身容器中，这会清除掉已经存在于容器中的数据，这些数据将无法恢复")
	)
		bool V5_RecoveryTransferData();
};

