// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class Projekt_AYAYATarget : TargetRules
{
	public Projekt_AYAYATarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("Projekt_AYAYA");
	}
}
