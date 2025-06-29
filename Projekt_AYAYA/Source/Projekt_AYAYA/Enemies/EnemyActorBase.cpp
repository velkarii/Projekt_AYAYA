// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyActorBase.h"
#include "Kismet/GameplayStatics.h"

void AEnemyActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyActorBase::Tick(float DeltaTime)
{
}

void AEnemyActorBase::PlayAttackMontage()
{
    if (!AttackMontage) return;

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
    {
        AnimInstance->Montage_Play(AttackMontage);
    }
}

void AEnemyActorBase::WieldSword()
{
	if (BP_Weapon == nullptr) return;

	AActor* Weapon = GetWorld()->SpawnActor<AActor>(BP_Weapon, GetActorLocation(), GetActorRotation());
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("WeaponSocketR")));
	IsWieldingSword = true;
}
