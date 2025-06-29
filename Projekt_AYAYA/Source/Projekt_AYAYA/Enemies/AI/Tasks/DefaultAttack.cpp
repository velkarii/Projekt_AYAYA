// Fill out your copyright notice in the Description page of Project Settings.
#include "BTT_DefaultAttack.h"
#include "AIController.h"
#include "Enemy_Base.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

EBTNodeResult::Type UBTT_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	AEnemy_Base* Enemy = Cast<AEnemy_Base>(ControlledPawn);
	UAnimInstance* AnimInstance = Enemy->GetMesh()->GetAnimInstance();

	if (!AnimInstance || !Enemy || !Enemy->AttackMontage)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->PlayAttackMontage();

	FOnMontageEnded MontageEndedDelegate;
	MontageEndedDelegate.BindUObject(this, &UBTT_DefaultAttack::OnAttackMontageEnded, &OwnerComp);
	AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, Enemy->AttackMontage);

	return EBTNodeResult::InProgress;
}

void UBTT_DefaultAttack::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		// Consider failing the task if montage was interrupted, or succeed otherwise
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}
