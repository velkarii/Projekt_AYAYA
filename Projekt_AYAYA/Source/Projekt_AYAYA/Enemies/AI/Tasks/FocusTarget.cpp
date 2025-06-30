// Fill out your copyright notice in the Description page of Project Settings.
#include "FocusTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyActorBase.h"

EBTNodeResult::Type UFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));

	AIController->SetFocus(TargetActor);
	return EBTNodeResult::Succeeded;
}
