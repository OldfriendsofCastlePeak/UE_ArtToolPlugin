// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArtTooPlugin.h"
#include "ArtTooPluginStyle.h"
#include "ArtTooPluginCommands.h"
#include "../ActionExtendLib.h"
#include "Misc/MessageDialog.h"

#include "Selection.h"
#include "ToolMenus.h"

DEFINE_LOG_CATEGORY(FArtToolPluginLog);

static FName ArtTooPluginTabName("ArtTooPlugin");
#define LOCTEXT_NAMESPACE "FArtTooPluginModule"

void FArtTooPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FArtTooPluginStyle::Initialize();
	FArtTooPluginStyle::ReloadTextures();

	FArtTooPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FArtTooPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FArtTooPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FArtTooPluginModule::RegisterMenus));


	//�����չ
	UActionExtendLib::AddSceneMenuItem();
	//UActionExtendLib::Test();
}

void FArtTooPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	//�Ƴ���չ
	//UActionExtendLib::RemoveMenuItem();
	
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FArtTooPluginStyle::Shutdown();

	FArtTooPluginCommands::Unregister();
}

void FArtTooPluginModule::PluginButtonClicked()
{
	// ��ȡ��ǰ�༭����World
	const UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
    
	// ���World�Ƿ����
	if (!EditorWorld)
	{
		UE_LOG(FArtToolPluginLog,Warning,TEXT("GEditor is invalid"));
		return;
	}

	//��ȡѡ�е�Actor����
	TArray<AActor*> SelectedActors;
	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActors);

	//ִ�о���ĺ���
	UActionExtendLib::UseSceneModelMaterialReplaceModelResourceMaterial(SelectedActors);
}

void FArtTooPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FArtTooPluginCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FArtTooPluginCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FArtTooPluginModule, ArtTooPlugin)