// Fill out your copyright notice in the Description page of Project Settings.
#include "BTD_IsWieldingWeapon.h"
#include "AIController.h"
#include "Enemy_Base.h"

bool UBTD_IsWieldingWeapon::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!Pawn)
	{
		return false;
	}

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(Pawn);
	if(!Enemy)
	{
		return false;
	}

	return Enemy->IsWieldingSword;
}
