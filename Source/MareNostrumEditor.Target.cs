using UnrealBuildTool;

public class MareNostrumEditorTarget : TargetRules
{
	public MareNostrumEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("MareNostrum");
	}
}
