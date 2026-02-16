#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackTypeBase.h"
#include "HitDetection.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJEKT_AYAYA_API UHitDetection : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitDetection();

	void StartDetection(USkeletalMeshComponent* MeshComp, AActor* Owner, TSubclassOf<UAttackTypeBase> AttackType);
	void StopDetection();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<UAttackTypeBase> CurrentAttack;

	TSet<TObjectPtr<AActor>> HitActors;
};