// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/SparseDelegate.h"
#include "TriggerTransceiverIntegraionComponent.generated.h"

UCLASS(Blueprintable,
	ClassGroup = (GeneralPlugLibrary),
	meta = (BlueprintSpawnableComponent),
	meta = (ToolTip = "逻辑收发集成组件")
)
class GENERALPLUGLIBRARY_API UTriggerTransceiverIntegraionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerTransceiverIntegraionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;




};