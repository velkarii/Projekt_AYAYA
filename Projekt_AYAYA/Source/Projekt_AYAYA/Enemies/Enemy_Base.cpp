// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy_Base.h"
#include "Kismet/GameplayStatics.h"

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Base::Tick(float DeltaTime)
{
}

void AEnemy_Base::PlayAttackMontage()
{
    if (!AttackMontage) return;

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
    {
        AnimInstance->Montage_Play(AttackMontage);
    }
}

void AEnemy_Base::WieldSword()
{
	if (BP_Weapon == nullptr) return;

	AActor* Weapon = GetWorld()->SpawnActor<AActor>(BP_Weapon, GetActorLocation(), GetActorRotation());
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("WeaponSocketR")));
	IsWieldingSword = true;
}
