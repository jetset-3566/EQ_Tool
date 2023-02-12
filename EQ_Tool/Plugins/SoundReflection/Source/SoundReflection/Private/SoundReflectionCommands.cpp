// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoundReflectionCommands.h"

#define LOCTEXT_NAMESPACE "FSoundReflectionModule"

void FSoundReflectionCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SoundReflection", "Bring up SoundReflection window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
