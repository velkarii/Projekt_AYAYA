#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackTypeBase.generated.h"

UCLASS(Abstract)
class PROJEKT_AYAYA_API UAttackTypeBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void InitializeAttack(USkeletalMeshComponent* InMeshComp, AActor* InOwner, TSet<TObjectPtr<AActor>>* InHitActors);

	virtual void ExecuteAttack() PURE_VIRTUAL(UAttackTypeBase::ExecuteAttack, );

	USkeletalMeshComponent* MeshComponent;

	UPROPERTY()
	AActor* Owner;

	TSet<TObjectPtr<AActor>>* HitActors;
};