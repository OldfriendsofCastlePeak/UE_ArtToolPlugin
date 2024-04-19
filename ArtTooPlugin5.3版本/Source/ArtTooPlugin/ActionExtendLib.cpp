// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionExtendLib.h"
#include "Public/ArtTooPlugin.h"
#include "LevelEditor.h"
#include "Misc/FeedbackContext.h"
#include "Modules/ModuleManager.h"

void UActionExtendLib::AddSceneMenuItem()
{
	//获取LevelEditor模块
	FLevelEditorModule* LevelEditorModule=&FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	if (!LevelEditorModule)
	{
		UE_LOG(LogTemp,Warning,TEXT("1111"));
		return;
	}
	
	//获取场景右键选中Actor菜单的所有条目
	TArray<FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors>& LevelActorSelectMenuItems=LevelEditorModule->GetAllLevelViewportContextMenuExtenders();

	//右键选中Actor菜单的所有条目基础上添加条目
	LevelActorSelectMenuItems.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateStatic(&UActionExtendLib::SceneActorSelectMenuAction));
}

// void UActionExtendLib::RemoveMenuItem()
// {
// 	//获取LevelEditor模块
// 	FLevelEditorModule* LevelEditorModule=&FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
// 	if (LevelEditorModule)
// 	{
// 		UE_LOG(FArtToolPluginLog,Warning,TEXT("LevelEditorModule is invalid"));
// 		return;
// 	}
// 	
// 	//获取场景右键选中Actor菜单的所有条目
// 	TArray<FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors>& LevelActorSelectMenuItems=LevelEditorModule->GetAllLevelViewportContextMenuExtenders();
//
// 	
// }

TSharedRef<FExtender> UActionExtendLib::SceneActorSelectMenuAction(
	const TSharedRef<FUICommandList> InFUICommandList,
	const TArray<AActor*>InSelecteActors)
{
	//创建一个扩展对象
	TSharedRef<FExtender> MenuExtender(new FExtender());
	if (InSelecteActors.Num()>0)
	{
		//DECLARE_DELEGATE_OneParam( FMenuExtensionDelegate, class FMenuBuilder& );
		MenuExtender->AddMenuExtension(
			"ActorOptions",
			EExtensionHook::Before,
			nullptr,
			FMenuExtensionDelegate::CreateLambda(
				[InSelecteActors](FMenuBuilder& InFMenuBuilder)
				{
					InFMenuBuilder.AddMenuEntry(
						FText::FromString(TEXT("替换材质")),
						FText::FromString(TEXT("使用选中的模型材质替换模型资源的材质")),
						FSlateIcon("ArtTooPluginStyle","ArtTooPlugin.PluginAction"),
						FUIAction(FExecuteAction::CreateLambda ([&InSelecteActors]()
						{
							UActionExtendLib::UseSceneModelMaterialReplaceModelResourceMaterial(InSelecteActors);
						})));
				}));
	};
	return MenuExtender;
}
#pragma region 具体执行内容
void UActionExtendLib::UseSceneModelMaterialReplaceModelResourceMaterial(const TArray<AActor*>& InSelecteActors)
{
	if (InSelecteActors.Num()==0) return;
	//创建进度条
	GWarn->BeginSlowTask( FText::FromString(TEXT("正在替换模型材质")),true );

	//遍历选中的数组
	int CurrentIndex=0;
	int MaxIndex=InSelecteActors.Num();
	for (const AActor* TemActor:InSelecteActors)
	{
		//TemActor应该不可能为空,判断一下更为保险
		if (!TemActor) continue;
		
		//获取Actor的静态网格体组件
		TArray<UStaticMeshComponent*>UStaticMeshComponentArray;
		TemActor->GetComponents<UStaticMeshComponent>(UStaticMeshComponentArray);

		//遍历静态网格体数组
		for (const UStaticMeshComponent* TemUStaticMeshComponent:UStaticMeshComponentArray)
		{
			//TemUStaticMeshComponent应该不可能为空,判断一下更为保险
			if (!TemUStaticMeshComponent) continue;

			//获取UStaticMeshComponent的UStaticMesh
			UStaticMesh* Tem= TemUStaticMeshComponent->GetStaticMesh();

			TArray<UMaterialInterface*> TemArray=TemUStaticMeshComponent->GetMaterials();
			//遍历材质数量,进行替换
			for(int i=0;i<TemArray.Num();i++)
			{
				Tem->SetMaterial(i,TemArray[i]);
			}
		}
		CurrentIndex++;
		GWarn->UpdateProgress(CurrentIndex,MaxIndex);
	}

	//关闭进度条
	GWarn->EndSlowTask();





	
}









#pragma endregion