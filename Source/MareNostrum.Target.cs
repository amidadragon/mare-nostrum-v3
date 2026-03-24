using UnrealBuildTool;

public class MareNostrumTarget : TargetRules
{
	public MareNostrumTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("MareNostrum");
	}
}
