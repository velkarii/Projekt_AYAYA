// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projekt_AYAYAGameMode.h"
#include "Projekt_AYAYACharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjekt_AYAYAGameMode::AProjekt_AYAYAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
