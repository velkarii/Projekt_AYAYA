#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Components/CapsuleComponent.h"
#include "AttackTypeBase.h"
#include "InvokeHitboxLogic.generated.h"

UCLASS()
class PROJEKT_AYAYA_API UInvokeHitboxLogic : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	UHitDetection* HitDetection;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAttackTypeBase> AttackType;
};