#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UHealthComponent::TakeDamage(float DamageAmount, FVector HitDirection)
{
    if (bIsDead || DamageAmount <= 0.f) return;

    LastHitDirection = HitDirection;
    Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);

    if (Health <= 0.f)
    {
        HandleDeath();
    }
}

void UHealthComponent::Heal(float HealAmount)
{
    if (bIsDead || HealAmount <= 0.f) return;
    Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);
}

void UHealthComponent::HandleDeath()
{
    if (bIsDead) return;
    bIsDead = true;

    if (!OwnerCharacter) return;

    APlayerController* PlayerController = Cast<APlayerController>(OwnerCharacter->GetController());
    if (PlayerController)
    {
        PlayerController->DisableInput(PlayerController);
    }

    AAIController* AIController = Cast<AAIController>(OwnerCharacter->GetController());
    if (AIController)
    {
        AIController->StopMovement();
        AIController->BrainComponent->StopLogic(TEXT("Dead"));
    }

    if (UCharacterMovementComponent* Movement = OwnerCharacter->GetCharacterMovement())
    {
        Movement->StopMovementImmediately();
        Movement->DisableMovement();
    }

    if (UCapsuleComponent* Capsule = OwnerCharacter->GetCapsuleComponent())
    {
        Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    EnableRagdoll();
}

void UHealthComponent::EnableRagdoll()
{
    USkeletalMeshComponent* Mesh = OwnerCharacter->GetMesh();
    if (!Mesh) return;

    Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
    Mesh->SetCollisionProfileName(TEXT("Ragdoll"));
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Mesh->SetSimulatePhysics(true);

    if (!LastHitDirection.IsNearlyZero())
    {
        FVector Impulse = LastHitDirection.GetSafeNormal() * DeathImpulseStrength;
        Mesh->AddImpulse(Impulse, DeathImpulseBone, false);
    }
}