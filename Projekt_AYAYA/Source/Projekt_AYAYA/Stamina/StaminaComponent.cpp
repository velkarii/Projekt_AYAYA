#include "StaminaComponent.h"
#include "Projekt_AYAYACharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterReference = Cast<AProjekt_AYAYACharacter>(GetOwner());

	if (CharacterReference != nullptr)
	{
		CharacterReference->GetWorldTimerManager().SetTimer(StaminaHandle, this, &UStaminaComponent::StaminaCycle, 0.01f, true);
		CharacterReference->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStaminaComponent::Sprint()
{
	if (CanSprint && CharacterReference->GetVelocity().Size2D() > 0.0f)
	{
		IsSprinting = true;
		CharacterReference->GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	}
}

void UStaminaComponent::StopSprint()
{
	if (!IsSprinting) return;

	IsSprinting = false;
	CharacterReference->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (!CharacterReference->GetWorldTimerManager().IsTimerActive(RegenHandle) && !bIsWaitingToRegen)
	{
		StartDelayedRegen();
	}
}

void UStaminaComponent::DrainStamina()
{
	Stamina = FMath::Clamp(Stamina - 0.10f, 0.0f, 100.0f);
}

void UStaminaComponent::RegenStamina()
{
	if (bIsWaitingToRegen)
		return;

	if (IsSprinting && CharacterReference->GetVelocity().Size2D() > 0.0f)
	{
		CharacterReference->GetWorldTimerManager().ClearTimer(RegenHandle);
		return;
	}

	Stamina += 0.10f;
	Stamina = FMath::Clamp(Stamina, 0.0f, 100.0f);

	if (!CanSprint && Stamina > 0.0f)
	{
		CanSprint = true;
	}

	if (Stamina >= 100.0f)
	{
		CharacterReference->GetWorldTimerManager().ClearTimer(RegenHandle);
	}
}

void UStaminaComponent::StartDelayedRegen()
{
	bIsWaitingToRegen = true;
	CharacterReference->GetWorldTimerManager().ClearTimer(RegenHandle);

	CharacterReference->GetWorldTimerManager().SetTimer(
		RegenHandle,
		[this]()
		{
			bIsWaitingToRegen = false;
		},
		StaminaRegenDelay,
		false
	);
}

void UStaminaComponent::StaminaCycle()
{
	CharacterSpeed = CharacterReference->GetVelocity().Size2D();
	Stamina = FMath::Clamp(Stamina, 0.0f, 100.0f);

	if (IsSprinting)
	{
		if (CharacterSpeed > 0.0f)
		{
			DrainStamina();

			if (Stamina <= 0.0f)
			{
				Stamina = 0.0f;
				CanSprint = false;
				IsSprinting = false;
				CharacterReference->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

				StartDelayedRegen();
				return;
			}

			CharacterReference->GetWorldTimerManager().ClearTimer(RegenHandle);
			bIsWaitingToRegen = false;
		}
		else
		{
			IsSprinting = false;
			CharacterReference->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

			StartDelayedRegen();
		}
	}
	else
	{
		if (!bIsWaitingToRegen && !CharacterReference->GetWorldTimerManager().IsTimerActive(RegenHandle))
		{
			RegenStamina();
		}
	}

	if (!CanSprint && Stamina > 0.0f)
	{
		CanSprint = true;
	}
}

void UStaminaComponent::Dodge(const FVector& Direction)
{
	if (!CharacterReference || Direction.IsNearlyZero() || !CanDodge()) return;

	const float DodgeStrength = 1000.f;
	CharacterReference->LaunchCharacter(Direction * DodgeStrength, true, true);

	Stamina = FMath::Clamp(Stamina - 15.0f, 0.0f, 100.0f);

	if (Stamina <= 0.0f)
	{
		CanSprint = false;
		StopSprint();
	}

	StartDelayedRegen();
}

//"koszt" staminy dla dodge
bool UStaminaComponent::CanDodge()
{
	return Stamina >= 15.0f;
}
