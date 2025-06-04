// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_InvokeAttackLogic.h"

void UANS_InvokeAttackLogic::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

#if WITH_EDITOR
	InvokeHitboxLogic(MeshComp, Owner);
#endif

}

void UANS_InvokeAttackLogic::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	const FAnimNotifyEvent* Event = EventReference.GetNotify();

	float Begin = Event->GetTriggerTime();
	float End = Event->GetEndTriggerTime();
	float Current = MeshComp->GetAnimInstance()->GetActiveMontageInstance()->GetPosition();

	if ((Current - 0.001f) < Begin || (Current + 0.001f) > End)
	{
		for (TObjectPtr<UCapsuleComponent> hitbox : Hitboxes)
		{
			hitbox->DestroyComponent();
		}
		Hitboxes.Empty();
	}
	
}

void UANS_InvokeAttackLogic::InvokeHitboxLogic(USkeletalMeshComponent* MeshComp, AActor* Owner)
{
	for (const FWeapon& Weapon : Weapons)
	{
		TObjectPtr<UStaticMeshComponent> WeaponMeshComp = NewObject<UStaticMeshComponent>();
		WeaponMeshComp->RegisterComponent();
		WeaponMeshComp->SetStaticMesh(Weapon.WeaponMesh);

		TArray<FName> Sockets = WeaponMeshComp->GetAllSocketNames();
		const int NumberOfSockets = Sockets.Num();

		if (NumberOfSockets % 2 != 0) return;

		for (int i = 0; i < NumberOfSockets; i += 2)
		{
			TObjectPtr<UCapsuleComponent> Hitbox = NewObject<UCapsuleComponent>(MeshComp);
			Hitbox->RegisterComponent();

			Hitbox->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Weapon.AttachSocketName);

			FVector Start = WeaponMeshComp->GetSocketLocation(Sockets[i]);
			FVector End = WeaponMeshComp->GetSocketLocation(Sockets[i + 1]);

			FVector MidPoint = (Start + End) / 2;
			Hitbox->SetRelativeLocation(MidPoint);

			FRotator Rotation = FRotationMatrix::MakeFromZ(MidPoint).Rotator();

			Hitbox->SetRelativeRotation(Rotation);

			double DistanceBetweenSockets = FVector::Distance(Start, End);
			Hitbox->SetCapsuleHalfHeight(DistanceBetweenSockets / 2);

			Hitbox->SetCapsuleRadius(Weapon.Radius);

			Hitboxes.Add(Hitbox);
		}

	}
}
