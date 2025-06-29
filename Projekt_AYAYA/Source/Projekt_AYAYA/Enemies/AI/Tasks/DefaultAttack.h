// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_DefaultAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_AYAYA_API UBTT_DefaultAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp);
};
