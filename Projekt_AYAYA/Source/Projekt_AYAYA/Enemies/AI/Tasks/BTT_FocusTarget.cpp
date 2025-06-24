// Fill out your copyright notice in the Description page of Project Settings.
#include "BTT_FocusTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_Base.h"

EBTNodeResult::Type UBTT_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<AAIController> AIController = OwnerComp.GetAIOwner();

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));

	AIController->SetFocus(TargetActor);
	return EBTNodeResult::Succeeded;
}
