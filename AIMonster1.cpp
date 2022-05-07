// Fill out your copyright notice in the Description page of Project Settings.
#include "AIMonster1.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "MonsterKillingGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

// Sets default values
AAIMonster1::AAIMonster1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	AICharacterCompCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AICharacterCompCapsuleCpp"));
	AICharacterCompCapsule->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AAIMonster1::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster1::NewMovement, 0.01f);
	
	PawnSensing->OnSeePawn.AddDynamic(this, &AAIMonster1::SeePawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &AAIMonster1::OnHearNoise);
	AICharacterCompCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAIMonster1::BeginOverlap);
	
}

// Called every frame
void AAIMonster1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIMonster1::NewMovement()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster1::NewMovement, 3.0f);
	}
}
void AAIMonster1::SeePawn(APawn* Pawn)
{
	AMonsterKillingGameCharacter* AISee1 = Cast<AMonsterKillingGameCharacter>(Pawn);



	if (AISee1)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster1::NewMovement, 2.0f);

	}

}
void AAIMonster1::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AMonsterKillingGameCharacter* AIHear1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
	
	if (AIHear1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("asd"));
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster1::NewMovement, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
}


void AAIMonster1::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AMonsterKillingGameCharacter* Carp1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
	if (Carp1) { 
		Carp1->SetHealth(Carp1->GetHealth() - (AttackPower - Carp1->GetDefense()));
		Destroy();
		if(Carp1->GetHealth() <= 0)
		{
			Carp1->Destroy();
			
		}
	} 
		
		
}



