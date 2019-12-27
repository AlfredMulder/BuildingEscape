// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BuildingEscapeEditorTarget : TargetRules
{
    public BuildingEscapeEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;

        bUseUnityBuild = false;
        bUsePCHFiles = false;

        ExtraModuleNames.AddRange(new string[] {"BuildingEscape"});
    }
}