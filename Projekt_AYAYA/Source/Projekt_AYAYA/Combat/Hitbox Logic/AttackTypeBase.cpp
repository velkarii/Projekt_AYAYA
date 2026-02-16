#include "AttackTypeBase.h"

void UAttackTypeBase::InitializeAttack(USkeletalMeshComponent* InMeshComp, AActor* InOwner, TSet<TObjectPtr<AActor>>* InHitActors)
{
	MeshComponent = InMeshComp;
	Owner = InOwner;
	HitActors = InHitActors;
}