// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArtTooPluginCommands.h"

#define LOCTEXT_NAMESPACE "FArtTooPluginModule"

void FArtTooPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "替换材质", "使用选中的模型材质替换模型资源的材质", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
