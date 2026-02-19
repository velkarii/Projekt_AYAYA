#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ACharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJEKT_AYAYA_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float MaxHealth = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float Health;

    UPROPERTY(EditDefaultsOnly, Category = "Death")
    FName DeathImpulseBone = FName("spine_03");

    UPROPERTY(EditDefaultsOnly, Category = "Death")
    float DeathImpulseStrength = 2000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Death")
    float BodyLifespan = 5.f;

    void TakeDamage(float DamageAmount, FVector HitDirection = FVector::ZeroVector);
    void Heal(float HealAmount);
    void HandleDeath();
    bool IsDead() const { return bIsDead; }

    UFUNCTION(BlueprintCallable) float GetHealthNumber()  const { return Health; }
    UFUNCTION(BlueprintCallable) float GetHealthPercent() const { return Health / MaxHealth; }

protected:
    virtual void BeginPlay() override;

private:
    bool    bIsDead = false;
    FVector LastHitDirection = FVector::ZeroVector;
    ACharacter* OwnerCharacter = nullptr;

    void EnableRagdoll();
};