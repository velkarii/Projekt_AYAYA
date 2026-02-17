#include "InvokeHitboxLogic.h"
#include "HitDetection.h"

void UInvokeHitboxLogic::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (!MeshComp) return;

    UWorld* World = MeshComp->GetWorld();

    if (World && World->IsGameWorld())
    {
        AActor* Owner = MeshComp->GetOwner();
        if (!Owner) return;
		
        UHitDetection* HitDetectionComp = Cast<UHitDetection>(Owner->GetComponentByClass(UHitDetection::StaticClass()));

        if (HitDetectionComp)
        {
            HitDetectionComp->StartDetection(MeshComp, Owner, AttackType);
        }
    }
}

void UInvokeHitboxLogic::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (!MeshComp) return;

    UWorld* World = MeshComp->GetWorld();
    if (World && World->IsGameWorld())
    {
        AActor* Owner = MeshComp->GetOwner();
        if (!Owner) return;

        UHitDetection* HitDetectionComp = Cast<UHitDetection>(Owner->GetComponentByClass(UHitDetection::StaticClass()));

        if (HitDetectionComp)
        {
            HitDetectionComp->StopDetection();
        }
    }
}