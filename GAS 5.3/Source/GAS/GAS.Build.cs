// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAS : ModuleRules
{
	public GAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,
			"GameplayAbilities",    // GAS 核心运行时模块
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			
			"GameplayTags",         // 游戏玩法标签系统
			"GameplayTasks",        // 游戏玩法任务系统
			"GameplayAbilitiesEditor", // GAS 编辑器模块（包含缺失的头文件）
			"Slate",                // UI 系统（如果需要编辑器界面）
			"SlateCore",            // Slate 核心
			"EditorStyle"           // 编辑器样式（如果需要编辑器 UI）
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
