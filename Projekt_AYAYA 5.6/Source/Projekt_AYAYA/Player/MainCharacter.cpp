#include "MainCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
    }
}

// ---- Movement ----

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