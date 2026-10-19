// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP_Quest : ModuleRules
{
	public TP_Quest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TP_Quest",
			"TP_Quest/Variant_Platforming",
			"TP_Quest/Variant_Platforming/Animation",
			"TP_Quest/Variant_Combat",
			"TP_Quest/Variant_Combat/AI",
			"TP_Quest/Variant_Combat/Animation",
			"TP_Quest/Variant_Combat/Gameplay",
			"TP_Quest/Variant_Combat/Interfaces",
			"TP_Quest/Variant_Combat/UI",
			"TP_Quest/Variant_SideScrolling",
			"TP_Quest/Variant_SideScrolling/AI",
			"TP_Quest/Variant_SideScrolling/Gameplay",
			"TP_Quest/Variant_SideScrolling/Interfaces",
			"TP_Quest/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
