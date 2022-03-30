#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "MonsterKillingGameProjectile.h"
#include "Components/CapsuleComponent.h"
#include "MonsterType1.h"
#include <MonsterKillingGame/MonsterKillingGameCharacter.h>


AMonsterType1::AMonsterType1()
{
	
	PrimaryActorTick.bCanEverTick = true;

}


void AMonsterType1::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMonsterType1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



