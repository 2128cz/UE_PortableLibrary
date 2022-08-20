// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MissionSystemStyle.h"

class FMissionSystemCommands : public TCommands<FMissionSystemCommands>
{
public:

	FMissionSystemCommands()
		: TCommands<FMissionSystemCommands>(TEXT("MissionSystem"), NSLOCTEXT("Contexts", "MissionSystem", "MissionSystem Plugin"), NAME_None, FMissionSystemStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};