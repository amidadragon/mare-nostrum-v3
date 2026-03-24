using UnrealBuildTool;

public class MareNostrum : ModuleRules
{
	public MareNostrum(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"EnhancedInput", "UMG", "NavigationSystem",
			"AIModule", "GameplayTasks", "Water"
		});
	}
}
