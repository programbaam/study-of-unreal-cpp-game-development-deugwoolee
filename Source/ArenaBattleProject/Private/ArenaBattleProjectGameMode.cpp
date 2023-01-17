// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArenaBattleProjectGameMode.h"
#include "ArenaBattleProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArenaBattleProjectGameMode::AArenaBattleProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
