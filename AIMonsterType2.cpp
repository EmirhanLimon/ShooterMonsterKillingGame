// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "AIMonsterType2.h"
#include "Perception/PawnSensingComponent.h"
#include "MonsterKillingGameCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

// Sets default values
AAIMonsterType2::AAIMonsterType2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	AICharacterCompCapsule2 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AICharacterCompCapsuleCpp2"));
	AICharacterCompCapsule2->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAIMonsterType2::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType2::NewMovement, 0.01f);

	PawnSensing->OnSeePawn.AddDynamic(this, &AAIMonsterType2::SeePawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &AAIMonsterType2::OnHearNoise);
	AICharacterCompCapsule2->OnComponentBeginOverlap.AddDynamic(this, &AAIMonsterType2::BeginOverlap);
}

// Called every frame
void AAIMonsterType2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIMonsterType2::NewMovement()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType2::NewMovement, 3.0f);
	}
}

void AAIMonsterType2::SeePawn(APawn* Pawn)
{
	AMonsterKillingGameCharacter* AISee2 = Cast<AMonsterKillingGameCharacter>(Pawn);



	if (AISee2)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType2::NewMovement, 2.0f);

	}

}

void AAIMonsterType2::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AMonsterKillingGameCharacter* AIHear2 = Cast<AMonsterKillingGameCharacter>(OtherActor);

	if (AIHear2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("asd"));
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAIMonsterType2::NewMovement, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
}
void AAIMonsterType2::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AMonsterKillingGameCharacter* Carp1 = Cast<AMonsterKillingGameCharacter>(OtherActor);
	if (Carp1) {
		Carp1->SetHealth(Carp1->GetHealth() - AttackPower);
		Destroy();
		
	}

	
}