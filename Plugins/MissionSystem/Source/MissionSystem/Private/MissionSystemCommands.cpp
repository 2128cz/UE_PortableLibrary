// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionSystemCommands.h"

#define LOCTEXT_NAMESPACE "FMissionSystemModule"

void FMissionSystemCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MissionSystem", "Bring up MissionSystem window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
