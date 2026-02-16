#pragma once

#include "CoreMinimal.h"
#include "AttackTypeBase.h"
#include "MeleeWeaponAttack.generated.h"

UCLASS()
class PROJEKT_AYAYA_API UMeleeWeaponAttack : public UAttackTypeBase
{
	GENERATED_BODY()
public:
	void SetupWeapons();
	void PerformSweep();
	void ExecuteAttack() override;
private:
	TArray<AActor*> Weapons;
	TArray<UStaticMeshComponent*> WeaponsMeshes;
	TArray<TArray<FName>> WeaponsSockets;
};
