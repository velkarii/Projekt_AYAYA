#include "HealthComponent.h"
#include "MainCharacter.h"
#include "Engine/Engine.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    CharacterReference = Cast<AMainCharacter>(GetOwner());
    Health = MaxHealth;
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
    Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);

    if (Health <= 0.f && CharacterReference)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s died!"), *CharacterReference->GetName());
    }
}

void UHealthComponent::Heal(float HealAmount)
{
    Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);
}