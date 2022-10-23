// Copyright (c) 2022 Damian Nowakowski. All rights reserved.

using UnrealBuildTool;

public class MyPlugin : ModuleRules
{
	public MyPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add("MyPlugin/Private");

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine"
			}
		);
	}
}
