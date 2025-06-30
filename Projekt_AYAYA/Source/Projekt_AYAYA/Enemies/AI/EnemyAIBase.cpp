#include "EnemyAIBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIBase::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (BehaviorTree)
    {
        BBComp = GetBlackboardComponent();

        if (UseBlackboard(BehaviorTree->BlackboardAsset, BBComp))
        {
            RunBehaviorTree(BehaviorTree);
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIBase::SetAttackTargetDelayed, 0.1f, false);
        }
    }
}

void AEnemyAIBase::SetAttackTargetDelayed()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (Player)
    {
        GetBlackboardComponent()->SetValueAsObject(AttackTargetKey, (UObject*)Player);
    }
}
