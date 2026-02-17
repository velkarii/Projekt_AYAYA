#include "MainCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h"

AMainCharacter::AMainCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    // Components
    StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("Stamina Component"));
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PlayerStaminaWidget = CreateWidget<UUserWidget>(PC, PlayerStaminaWidgetClass);
        if (PlayerStaminaWidget)
        {
            PlayerStaminaWidget->AddToViewport();
        }
    }
    
    if (USkeletalMeshComponent* PlayerMesh = GetMesh())
    {
        if (UAnimInstance* AnimInstance = PlayerMesh->GetAnimInstance())
        {
            AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AMainCharacter::OnMontageNotifyBegin);
            AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnAttackMontageEnded);
        }
    }
}

void AMainCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMapping, 0);
        }
    }

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Movement
        Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

        // Actions
        Input->BindAction(DodgeAction, ETriggerEvent::Started, this, &AMainCharacter::Dodge);
        Input->BindAction(SprintAction, ETriggerEvent::Started, this, &AMainCharacter::Sprint);
        Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainCharacter::StopSprint);

        // Damage / Heal
        Input->BindAction(DebugDamageAction, ETriggerEvent::Started, this, &AMainCharacter::Damage);
        Input->BindAction(DebugHealAction, ETriggerEvent::Started, this, &AMainCharacter::HealCharacter);
        Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainCharacter::Attack);
    }
}

void AMainCharacter::Attack()
{
    if (bIsAttacking)
    {
        bSaveAttack = true;
    }
    else
    {
        if (AttackMontage && StaminaComponent)
        {
            if (StaminaComponent->Stamina >= AttackStaminaCost)
            {
                StaminaComponent->Stamina -= AttackStaminaCost;
                StaminaComponent->StartDelayedRegen();
                bIsAttacking = true;
                ComboCount = 1;
                PlayAnimMontage(AttackMontage, 1.0f, FName("Attack1"));
            }
        }
    }
}

void AMainCharacter::ResetCombo()
{
    if (bSaveAttack)
    {
        bSaveAttack = false;
        if (ComboCount >= 3)
        {
            SetMovementLock(false);
            return;
        }

        if (StaminaComponent && StaminaComponent->Stamina >= AttackStaminaCost)
        {
            ComboCount++;
            StaminaComponent->Stamina -= AttackStaminaCost;
            StaminaComponent->StartDelayedRegen();

            FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), ComboCount));

            if (AttackMontage)
            {
                if (AttackMontage->GetSectionIndex(SectionName) != INDEX_NONE)
                {
                    if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
                    {
                        AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
                    }
                    return;
                }
            }
        }
    }

    SetMovementLock(false);
}

void AMainCharacter::SetMovementLock(bool bLocked)
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->SetIgnoreMoveInput(bLocked);
    }
}

void AMainCharacter::Move(const FInputActionValue& InputValue)
{
    FVector2D InputVector = InputValue.Get<FVector2D>();

    if (IsValid(Controller))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        FVector MoveDir = (ForwardDirection * InputVector.Y + RightDirection * InputVector.X).GetSafeNormal();
        AddMovementInput(MoveDir);

        if (!MoveDir.IsNearlyZero())
        {
            LastMovementInput = MoveDir;
        }
    }
}

void AMainCharacter::Look(const FInputActionValue& InputValue)
{
    FVector2D InputVector = InputValue.Get<FVector2D>();

    if (IsValid(Controller))
    {
        AddControllerYawInput(InputVector.X);
        AddControllerPitchInput(InputVector.Y);
    }
}

void AMainCharacter::Dodge()
{
    if (!IsValid(Controller)) return;

    if (!LastMovementInput.IsNearlyZero() && StaminaComponent && StaminaComponent->CanDodge())
    {
        StaminaComponent->Dodge(LastMovementInput);
    }
}

void AMainCharacter::Sprint()
{
    if (StaminaComponent)
        StaminaComponent->Sprint();
}

void AMainCharacter::StopSprint()
{
    if (StaminaComponent)
        StaminaComponent->StopSprint();
}

// ---- Damage / Heal ----

void AMainCharacter::Damage()
{
    if (HealthComponent)
    {
        HealthComponent->TakeDamage(10.f);
        UE_LOG(LogTemp, Warning, TEXT("DAMAGE pressed | HP = %f"), HealthComponent->Health);
    }
}

void AMainCharacter::HealCharacter()
{
    if (HealthComponent)
    {
        HealthComponent->Heal(10.f);
        UE_LOG(LogTemp, Warning, TEXT("HEAL pressed | HP = %f"), HealthComponent->Health);
    }
}

void AMainCharacter::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    if (NotifyName == FName("ANS_ResetCombo") || NotifyName == FName("AN_ResetCombo"))
    {
        ResetCombo();
    }
    else if (NotifyName == FName("ANS_LockMove"))
    {
        SetMovementLock(true);
    }
    else if (NotifyName == FName("ANS_UnlockMove"))
    {
        SetMovementLock(false);
    }
}

void AMainCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (Montage == AttackMontage)
    {
        bIsAttacking = false;
        bSaveAttack = false;
        ComboCount = 0;

        SetMovementLock(false);
    }
}