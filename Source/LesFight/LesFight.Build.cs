using UnrealBuildTool;
using System.IO;

public class LesFight : ModuleRules
{
	public LesFight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Add Core, Events, and Framework root directories for cross-module includes
		// Note: Data/ is intentionally excluded to avoid class name collision with Framework/Data/Core/
		// Root Data files are accessible via "Data/Filename.h" from the default ModuleDirectory include path
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Core"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Events"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Framework"));

		if (Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicDependencyModuleNames.AddRange(new string[]
			{
				"Launch",
				"ApplicationCore"
			});
		}

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayTags",
			"UMG",
			"Slate",
			"SlateCore",
			"AIModule",
			"NavigationSystem",
			"PhysicsCore",
			"Chaos",
			"Niagara",
			"MetaSound",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"MoviePlayer",
			"LevelSequence",
			"MediaAssets",
			"AudioMixer"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"RenderCore",
			"EngineSettings",
			"DeveloperSettings"
		});
	}
}
