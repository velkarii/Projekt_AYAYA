// Fill out your copyright notice in the Description page of Project Settings.
#include "IsWieldingWeapon.h"
#include "AIController.h"
#include "EnemyActorBase.h"

bool UIsWieldingWeapon::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!Pawn)
	{
		return false;
	}

	AEnemyActorBase* Enemy = Cast<AEnemyActorBase>(Pawn);
	if(!Enemy)
	{
		return false;
	}

	return Enemy->IsWieldingSword;
}
