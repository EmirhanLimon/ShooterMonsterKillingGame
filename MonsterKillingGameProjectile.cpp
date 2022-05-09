// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterKillingGameProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "AIMonster1.h"
#include "AIMonster2.h"
#include "AIMonster3.h"
#include "MonsterKillingGameCharacter.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Ammo.h"
//#include "../../../../../../Program Files/Epic Games/UE_4.27/Engine/Shaders/Private/SolidColorPixelShader.ush"

AMonsterKillingGameProjectile::AMonsterKillingGameProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMonsterKillingGameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 10000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}




void AMonsterKillingGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MainCharacter = Cast<AMonsterKillingGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	AAIMonster1* Carp1 = Cast<AAIMonster1>(OtherActor);
	AAIMonster2* Carp2 = Cast<AAIMonster2>(OtherActor);
	AAIMonster3* Carp3 = Cast<AAIMonster3>(OtherActor);
	
	
	if (Carp1)
	{
		Carp1->SetHealth((Carp1->GetHealth()+Carp1->GetDefense()) - MainCharacter->GetAttack());		
		if(Carp1->GetHealth() <= 0)
		{
			Carp1->Destroy();
			MainCharacter->SetExperience(MainCharacter->GetExperience() + 100);
		}
		
	}
	if (Carp2)
	{
		Carp2->SetHealth(Carp2->GetHealth() + Carp2->GetDefense() - MainCharacter->GetAttack());
		Carp2->SetHealth((Carp2->GetHealth()+Carp2->GetDefense()) - MainCharacter->GetAttack());		
        		if(Carp2->GetHealth() <= 0)
        		{
        			Carp2->Destroy();
        			MainCharacter->SetExperience(MainCharacter->GetExperience() + 100);
        		}
	}
	if (Carp3)
	{
		Carp3->SetHealth(Carp3->GetHealth() + Carp3->GetDefense() - MainCharacter->GetAttack());
		Carp3->SetHealth((Carp3->GetHealth()+Carp3->GetDefense()) - MainCharacter->GetAttack());		
        		if(Carp3->GetHealth() <= 0)
        		{
        			Carp3->Destroy();
        			MainCharacter->SetExperience(MainCharacter->GetExperience() + 100);
        		}
	}
	Destroy();
}


