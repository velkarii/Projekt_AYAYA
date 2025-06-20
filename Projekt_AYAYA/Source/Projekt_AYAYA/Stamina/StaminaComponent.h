#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StaminaComponent.generated.h"

class AProjekt_AYAYACharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJEKT_AYAYA_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaminaComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float Stamina = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float CharacterSpeed = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool IsSprinting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool CanSprint = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float WalkSpeed = 300.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float MaxSpeed = 500.0f;

	UPROPERTY(VisibleAnywhere) FTimerHandle StaminaHandle;
	UPROPERTY(VisibleAnywhere) FTimerHandle RegenHandle;
	UPROPERTY(VisibleAnywhere) FTimerHandle StaminaRegenDelayHandle;

	AProjekt_AYAYACharacter* CharacterReference;

	void Sprint();
	void StopSprint();
	void RegenStamina();
	void DrainStamina();
	void StaminaCycle();
	void Dodge(const FVector& Direction);
	bool CanDodge();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void StartDelayedRegen();

	bool bIsWaitingToRegen = false;

	//ustawienie delay dla startu regeneracji
	float StaminaRegenDelay = 2.0f;
};
