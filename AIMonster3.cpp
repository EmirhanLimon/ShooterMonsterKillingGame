// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CapsuleComponent.h"
#include "AIMonster3.h"
#include "Perception/PawnSensingComponent.h"
#include "MonsterKillingGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

// Sets default values
AAIMonster3::AAIMonster3()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	AICharacterCompCapsule3 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AICharacterCompCapsuleCpp3"));
	AICharacterCompCapsule3->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AAIMonster3::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster3::NewMovement, 0.01f);

	PawnSensing->OnSeePawn.AddDynamic(this, &AAIMonster3::SeePawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &AAIMonster3::OnHearNoise);
	AICharacterCompCapsule3->OnComponentBeginOverlap.AddDynamic(this, &AAIMonster3::BeginOverlap);
}

// Called every frame
void AAIMonster3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIMonster3::NewMovement()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster3::NewMovement, 3.0f);
	}
}
void AAIMonster3::SeePawn(APawn* Pawn)
{
	AMonsterKillingGameCharacter* AISee3 = Cast<AMonsterKillingGameCharacter>(Pawn);



	if (AISee3)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster3::NewMovement, 2.0f);

	}

}
void AAIMonster3::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AMonsterKillingGameCharacter* AIHear3 = Cast<AMonsterKillingGameCharacter>(OtherActor);

	if (AIHear3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("asd"));
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonster3::NewMovement, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
}
void AAIMonster3::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AMonsterKillingGameCharacter* Carp1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
	if (Carp1) {
		Carp1->SetHealth(Carp1->GetHealth() - (AttackPower -  + Carp1->GetDefense()));
		Destroy();
		if(Carp1->GetHealth() <= 0)
		{
			Carp1->Destroy();
			
		}
	}


}


