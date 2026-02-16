// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI/PatrolRoute.h"
#include "EnemyActorBase.generated.h"

UCLASS()
class PROJEKT_AYAYA_API AEnemyActorBase : public ACharacter
{
	GENERATED_BODY()

public:
	void PlayAttackMontage();
	void WieldSword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<AActor> BP_Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TSubclassOf<AActor> PatrolRoute;

	bool IsWieldingSword = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override; // Called every frame

};
