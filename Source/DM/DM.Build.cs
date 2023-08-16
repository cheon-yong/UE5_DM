// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DM : ModuleRules
{
	public DM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"AnimGraphRuntime",
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks",
			"UMG"
		});
	}
}
