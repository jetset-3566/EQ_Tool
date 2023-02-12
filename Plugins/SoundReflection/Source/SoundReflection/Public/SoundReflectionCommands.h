// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SoundReflectionStyle.h"

class FSoundReflectionCommands : public TCommands<FSoundReflectionCommands>
{
public:

	FSoundReflectionCommands()
		: TCommands<FSoundReflectionCommands>(TEXT("SoundReflection"), NSLOCTEXT("Contexts", "SoundReflection", "SoundReflection Plugin"), NAME_None, FSoundReflectionStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};