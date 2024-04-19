// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArtTooPluginStyle.h"
#include "ArtTooPlugin.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FArtTooPluginStyle::StyleInstance = nullptr;

void FArtTooPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FArtTooPluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FArtTooPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ArtTooPluginStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FArtTooPluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ArtTooPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("ArtTooPlugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("ArtTooPlugin.PluginAction", new IMAGE_BRUSH(TEXT("Icon128"), Icon20x20));
	return Style;
}

void FArtTooPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FArtTooPluginStyle::Get()
{
	return *StyleInstance;
}
