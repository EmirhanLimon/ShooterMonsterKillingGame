// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterKillingGameGameMode.h"
#include "MonsterKillingGameHUD.h"
#include "MonsterKillingGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMonsterKillingGameGameMode::AMonsterKillingGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMonsterKillingGameHUD::StaticClass();
}
