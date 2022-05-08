// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "Ammo.h"
#include "MonsterKillingGameCharacter.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AmmoCompCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AICharacterCompCapsuleCpp"));
	AmmoCompCapsule->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	AmmoCompCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::BeginOverlap);
	
}

void AAmmo::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AMonsterKillingGameCharacter* Carp1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
	if(Carp1)
	{
		if(Carp1->ReserveAmmo < 210)
		{
			MissingAmmo = 210 - Carp1->ReserveAmmo;
			if(Carp1->ReserveAmmo <= 180)
			{
				Carp1->ReserveAmmo +=30;
			}
			else
			{
				Carp1->ReserveAmmo = 210;
			}
			Destroy();
		}
	}
		
		
}



