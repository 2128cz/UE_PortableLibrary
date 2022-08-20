// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestDataAsset.generated.h"

UCLASS()
class UTestDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere)
	FString StringProperty;

	UPROPERTY(EditAnyWhere)
	float FloatProperty;
};