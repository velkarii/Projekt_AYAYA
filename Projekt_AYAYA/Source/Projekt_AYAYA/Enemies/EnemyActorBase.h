// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI/PatrolRoute.h"
#include "Projekt_AYAYA/Health/HealthComponent.h"
#include "EnemyActorBase.generated.h"

UCLASS()
class PROJEKT_AYAYA_API AEnemyActorBase : public ACharacter
{
	GENERATED_BODY()

public:
	void PlayAttackMontage();
	void WieldSword();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<AActor> BP_Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TSubclassOf<AActor> PatrolRoute;

	bool IsWieldingSword = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;
protected:
	AEnemyActorBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
