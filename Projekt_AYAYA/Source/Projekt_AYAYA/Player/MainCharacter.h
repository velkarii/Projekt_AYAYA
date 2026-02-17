#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "StaminaComponent.h"
#include "Projekt_AYAYA/Health/HealthComponent.h"
#include "MainCharacter.generated.h"

class UStaminaComponent;
class UHealthComponent;

UCLASS()
class PROJEKT_AYAYA_API AMainCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    // Kamera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArm;

    // Input
    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputMappingContext* InputMapping;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* DodgeAction;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* SprintAction;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* DebugDamageAction;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* DebugHealAction;

    // Widget
    UPROPERTY(EditAnywhere, Category = "UI") TSubclassOf<UUserWidget> PlayerStaminaWidgetClass;
    UUserWidget* PlayerStaminaWidget;

public:
    AMainCharacter();

    // Components
    UPROPERTY(BlueprintReadOnly)
    UStaminaComponent* StaminaComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* AttackAction;

    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsAttacking = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bSaveAttack = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    int32 ComboCount = 0;

    void Attack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ResetCombo();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetMovementLock(bool bLocked);

    UPROPERTY(EditAnywhere, Category = "Combat")
    float AttackStaminaCost = 15.0f;

    UFUNCTION()
    void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

    UFUNCTION()
    void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    bool bIsComboing = false;
protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Movement
    void Move(const FInputActionValue& InputValue);
    void Look(const FInputActionValue& InputValue);
    FVector LastMovementInput;
    void Dodge();
    void Sprint();
    void StopSprint();

    // Debug / Damage
    void Damage();
    void HealCharacter();
};
