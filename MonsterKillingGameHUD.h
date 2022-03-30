// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MonsterKillingGameHUD.generated.h"

UCLASS()
class AMonsterKillingGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMonsterKillingGameHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

