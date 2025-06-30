// Fill out your copyright notice in the Description page of Project Settings.
#include "WieldSword.h"
#include "EnemyActorBase.h"
#include "AIController.h"

EBTNodeResult::Type UWieldSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AEnemyActorBase> Enemy = Cast<AEnemyActorBase>(OwnerComp.GetAIOwner()->GetPawn());
	Enemy->WieldSword();
	return EBTNodeResult::Succeeded;
}
