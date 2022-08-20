// Copyright 2128cz, Inc. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestDataAsset.generated.h"

UCLASS()
class GENERALPLUGLIBRARY_API UTestDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere)
	FString StringProperty;

	UPROPERTY(EditAnyWhere)
	float FloatProperty;
};