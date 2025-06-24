// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Projekt_AYAYA : ModuleRules
{
	public Projekt_AYAYA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AIModule","GameplayTasks", "AnimationCore", "AnimGraphRuntime" });

        PublicIncludePaths.AddRange(
    new string[] {
        "Projekt_AYAYA/GameMode",
        "Projekt_AYAYA/Player",
        "Projekt_AYAYA/Stamina",
        "Projekt_AYAYA/Enemies"
        });

    PrivateIncludePaths.AddRange(
    new string[] {
        "Projekt_AYAYA/GameMode",
        "Projekt_AYAYA/Player",
        "Projekt_AYAYA/Stamina"
        });

    }
}
