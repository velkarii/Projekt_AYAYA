#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AMainCharacter;

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

    AMainCharacter* CharacterReference;

    void TakeDamage(float DamageAmount);
    void Heal(float HealAmount);
    bool IsDead() const { return Health <= 0.f; }

    // Funkcje do widgetu
    UFUNCTION(BlueprintCallable) float GetHealthNumber() const { return Health; }
    UFUNCTION(BlueprintCallable) float GetHealthPercent() const { return Health / MaxHealth; }

protected:
    virtual void BeginPlay() override;
};
