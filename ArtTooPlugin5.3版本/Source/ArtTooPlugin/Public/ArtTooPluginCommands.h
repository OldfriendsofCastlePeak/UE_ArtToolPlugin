// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ArtTooPluginStyle.h"

class FArtTooPluginCommands : public TCommands<FArtTooPluginCommands>
{
public:

	FArtTooPluginCommands()
		: TCommands<FArtTooPluginCommands>(TEXT("ArtTooPlugin"), NSLOCTEXT("Contexts", "ArtTooPlugin", "ArtTooPlugin Plugin"), NAME_None, FArtTooPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
