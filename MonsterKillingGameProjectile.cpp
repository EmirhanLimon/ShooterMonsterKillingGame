// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonsterKillingGameProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MonsterType1.h"
#include "MonsterType2.h"
#include "AIMonsterType1.h"
#include "AIMonsterType2.h"
#include "AIMonsterType3.h"

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

	AAIMonsterType1* Carp1 = Cast<AAIMonsterType1>(OtherActor);
	AAIMonsterType2* Carp2 = Cast<AAIMonsterType2>(OtherActor);
	AAIMonsterType3* Carp3 = Cast<AAIMonsterType3>(OtherActor);
	if (Carp1)
	{
		Carp1->SetHealth((Carp1->GetHealth()+Carp1->GetDefense())-25.f);		
		if (Carp1->GetHealth() <= 0) {
			Carp1->Destroy();
		}
	}
	if (Carp2)
	{
		Carp2->SetHealth((Carp2->GetHealth() + Carp2->GetDefense()) - 25.f);
		if (Carp2->GetHealth() <= 0) {
			Carp2->Destroy();
		}
	}
	if (Carp3)
	{
		Carp3->SetHealth(Carp3->GetHealth() + Carp3->GetDefense() - 25.f);
		if (Carp3->GetHealth() <= 0)
		{
			Carp3->Destroy();
		}
	}
	Destroy();


	
	
} 