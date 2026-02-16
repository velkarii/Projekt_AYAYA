// Fill out your copyright notice in the Description page of Project Settings.
#include "DefaultAttack.h"
#include "AIController.h"
#include "EnemyActorBase.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

EBTNodeResult::Type UDefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControlledPawn)
		return EBTNodeResult::Failed;

	AEnemyActorBase* Enemy = Cast<AEnemyActorBase>(ControlledPawn);
	UAnimInstance* AnimInstance = Enemy->GetMesh()->GetAnimInstance();

	if (!AnimInstance || !Enemy || !Enemy->AttackMontage)
		return EBTNodeResult::Failed;
	
	Enemy->PlayAttackMontage();

	FOnMontageEnded MontageEndedDelegate;
	MontageEndedDelegate.BindUObject(this, &UDefaultAttack::OnAttackMontageEnded, &OwnerComp);
	AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, Enemy->AttackMontage);

	return EBTNodeResult::InProgress;
}

void UDefaultAttack::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp && !bInterrupted)
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	else
		FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
}
