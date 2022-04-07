// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "AIMonsterType1.h"
#include "Perception/PawnSensingComponent.h"
#include "MonsterKillingGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
// Sets default values
AAIMonsterType1::AAIMonsterType1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	AICharacterCompCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AICharacterCompCapsuleCpp"));
	AICharacterCompCapsule->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAIMonsterType1::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType1::NewMovement, 0.01f);
	
	PawnSensing->OnSeePawn.AddDynamic(this, &AAIMonsterType1::SeePawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &AAIMonsterType1::OnHearNoise);
	AICharacterCompCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAIMonsterType1::BeginOverlap);
}

void AAIMonsterType1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIMonsterType1::NewMovement()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType1::NewMovement, 3.0f);
	}
}
void AAIMonsterType1::SeePawn(APawn* Pawn)
{
	AMonsterKillingGameCharacter* AISee1 = Cast<AMonsterKillingGameCharacter>(Pawn);



	if (AISee1)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType1::NewMovement, 2.0f);

	}

}
void AAIMonsterType1::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AMonsterKillingGameCharacter* AIHear1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
	
	if (AIHear1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("asd"));
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType1::NewMovement, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
}


void AAIMonsterType1::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		AMonsterKillingGameCharacter* Carp1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
		if (Carp1) { 
			
			if (Carp1) {
				Carp1->SetHealth(Carp1->GetHealth() - AttackPower);
				Destroy();

			}
		} 
		
		
}
