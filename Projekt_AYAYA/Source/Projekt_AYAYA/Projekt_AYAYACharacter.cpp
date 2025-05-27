#include "Projekt_AYAYACharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AProjekt_AYAYACharacter::AProjekt_AYAYACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	//creating stamina component on build
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("Stamina Component"));
}

void AProjekt_AYAYACharacter::BeginPlay()
{
	Super::BeginPlay();

	// Stamina widget added to viewport
	if (PlayerStaminaWidgetClass != nullptr)
	{
		PlayerStaminaWidget = CreateWidget(GetWorld(), PlayerStaminaWidgetClass);
		PlayerStaminaWidget->AddToViewport();
	}
}

void AProjekt_AYAYACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjekt_AYAYACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Move
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjekt_AYAYACharacter::Move);
		//Look
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjekt_AYAYACharacter::Look);
		//Dodge
		Input->BindAction(DodgeAction, ETriggerEvent::Started, this, &AProjekt_AYAYACharacter::Dodge);
		//Sprint
		Input->BindAction(SprintAction, ETriggerEvent::Started, this, &AProjekt_AYAYACharacter::Sprint);
		//Stop Sprint
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AProjekt_AYAYACharacter::StopSprint);
	}

}

void AProjekt_AYAYACharacter::Move(const FInputActionValue& InputValue)
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

void AProjekt_AYAYACharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

		if (IsValid(Controller))
		{
			AddControllerYawInput(InputVector.X);
			AddControllerPitchInput(InputVector.Y);
		}
}

void AProjekt_AYAYACharacter::Dodge()
{
	if (!IsValid(Controller)) return;

		if (!LastMovementInput.IsNearlyZero())
		{
			const float DodgeStrength = 1000.f;
			LaunchCharacter(LastMovementInput * DodgeStrength, true, true);
		}
}

void AProjekt_AYAYACharacter::Sprint()
{
	StaminaComponent->Sprint();
}

void AProjekt_AYAYACharacter::StopSprint()
{
	StaminaComponent->StopSprint();
}
