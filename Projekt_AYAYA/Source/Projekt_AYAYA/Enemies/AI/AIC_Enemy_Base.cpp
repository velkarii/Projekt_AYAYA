#include "AIC_Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

void AAIC_Enemy_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (BehaviorTree)
    {
        BBComp = GetBlackboardComponent();

        if (UseBlackboard(BehaviorTree->BlackboardAsset, BBComp))
        {
            RunBehaviorTree(BehaviorTree);
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAIC_Enemy_Base::SetAttackTargetDelayed, 0.1f, false);
        }
    }
}

void AAIC_Enemy_Base::SetAttackTargetDelayed()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (Player)
    {
        GetBlackboardComponent()->SetValueAsObject(AttackTargetKey, (UObject*)Player);
    }
}
