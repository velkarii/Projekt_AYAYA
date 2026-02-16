#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_AYAYA_API AEnemyAIBase : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

private:
	UPROPERTY()
	UBlackboardComponent* BBComp;

	FTimerHandle TimerHandle;

	const FName AttackTargetKey = TEXT("AttackTarget");

	void SetAttackTargetDelayed();

	virtual void OnPossess(APawn* InPawn) override;
};
