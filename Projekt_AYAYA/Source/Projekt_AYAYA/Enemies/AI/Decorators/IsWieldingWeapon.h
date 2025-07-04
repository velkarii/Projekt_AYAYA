// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsWieldingWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_AYAYA_API UIsWieldingWeapon : public UBTDecorator
{
	GENERATED_BODY()

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
