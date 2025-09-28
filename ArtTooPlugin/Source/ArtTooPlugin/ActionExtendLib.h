// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionExtendLib.generated.h"

/**
 * 
 */
UCLASS()
class ARTTOOPLUGIN_API UActionExtendLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure,Category="UActionExtendLib")
	static UWorld* GetEditorWorld()
	{
		return GEditor->GetEditorWorldContext().World();
	}


	
#pragma region 添加扩展行为
	static void AddSceneMenuItem();
	


	
	//static void RemoveMenuItem();
	//
	static TSharedRef<FExtender> SceneActorSelectMenuAction(const TSharedRef<FUICommandList>InFUICommandList,const TArray<AActor*>InSelecteActors);
	
#pragma endregion



#pragma region 具体执行内容
	/**
	 * 使用场景中的模型的材质替换模型资源的材质
	 * @param InSelecteActors 传入在场景中选择的Actor
	 */
	static void UseSceneModelMaterialReplaceModelResourceMaterial(const TArray<AActor*>&InSelecteActors);

	



#pragma endregion
	
};
