// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIMonster1.generated.h"

class UPawnSensingComponent;

UCLASS()
class MONSTERKILLINGGAME_API AAIMonster1 : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAIMonster1();

UFUNCTION()
		void NewMovement();
	UFUNCTION()
		void SeePawn(APawn* Pawn);
	UFUNCTION()
		void OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume);
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UPawnSensingComponent* PawnSensing;
	UPROPERTY()
	AAIController* AIC_Ref;
	UPROPERTY()
	FTimerHandle Timer;
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* AICharacterCompCapsule;
private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	float Health = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float Defense = 10;
	UPROPERTY(EditDefaultsOnly)
	float AttackPower = 15;
public:
	FORCEINLINE void SetHealth(float NewHealth) { Health = NewHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE void SetDefense(float NewDefense) { Health = NewDefense; }
	FORCEINLINE float GetDefense() { return Defense; }

	FORCEINLINE void SetAttackPower(float NewAttackPower) { AttackPower = NewAttackPower; }
	FORCEINLINE float GetAttackPower() { return AttackPower; }
};
	
	


