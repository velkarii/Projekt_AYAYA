#include "EnemyAIBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIBase::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (!BehaviorTree)
        return;
    
    BBComp = GetBlackboardComponent();

    if (!UseBlackboard(BehaviorTree->BlackboardAsset, BBComp))
        return;
    
    RunBehaviorTree(BehaviorTree);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIBase::SetAttackTargetDelayed, 0.1f, false);
}

void AEnemyAIBase::SetAttackTargetDelayed()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("EnemyAI: Nie znaleziono Pawna gracza!"));
        return;
    }

    if (BBComp)
    {
        BBComp->SetValueAsObject(AttackTargetKey, PlayerPawn);
    }
}
