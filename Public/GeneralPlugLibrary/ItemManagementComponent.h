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
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		TArray<AActor*> InstanceContainer;

protected:
	UFUNCTION(BlueprintCallable,
		Category = "ItemManagement|1_InstanceContainer",
		meta = (DefaultToSelf),
		meta = (DisplayName = "向1号实例容器添加一个实例"),
		meta = (ExpandEnumAsExecs = "ActorInstance"),
		meta = (HideSelfPin),
		//meta = (CompactNodeTitle = "ADD VES1"),
		meta = (KeyWords = "add set actor instance 1"), 
		//meta = (ShortToolTip = "向实例容器1添加一个实例"),
		meta = (ToolTip = "向容器1中添加一个对象实例。建议使用实例而不是容器的索引作为查找索引。")
	)
		bool V1_AddActorByInst(AActor* ActorInstance);

};

