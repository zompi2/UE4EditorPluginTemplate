// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;

public class MyPluginEditor : ModuleRules
{
	public MyPluginEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add("MyPluginEditor/Private");
		PrivateIncludePaths.Add("MyPlugin/Private");

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"InputCore"
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"MyPlugin",
                "Engine",
				"CoreUObject",
                "Slate",
                "SlateCore",
                "UnrealEd",
				"WorkspaceMenuStructure",
				"DesktopPlatform",
                "Blutility",
                "UMG",
                "UMGEditor",
				"EditorStyle",
				"Projects"
			}
		);
	}
}
