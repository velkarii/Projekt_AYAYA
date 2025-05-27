#include "StaminaComponent.h"
#include "Projekt_AYAYACharacter.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
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

// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStaminaComponent::Sprint()
{
	if (CanSprint)
	{
		IsSprinting = true;
		CharacterReference->GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	}
}

void UStaminaComponent::StopSprint()
{
	IsSprinting = false;
	CharacterReference->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void UStaminaComponent::RegenStamina()
{
	if (IsSprinting && CharacterReference->GetVelocity().Size2D() > 0.0f)
	{
		CharacterReference->GetWorldTimerManager().ClearTimer(RegenHandle);
		bIsWaitingToRegen = false;
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
		bIsWaitingToRegen = false;
	}
}

void UStaminaComponent::DrainStamina()
{
	Stamina = FMath::Clamp(Stamina - 0.10f, 0.0f, 100.0f);
}

void UStaminaComponent::StartDelayedRegen()
{
	if (bIsWaitingToRegen || CharacterReference->GetWorldTimerManager().IsTimerActive(RegenHandle))
		return;

	bIsWaitingToRegen = true;

	CharacterReference->GetWorldTimerManager().SetTimer(
		RegenHandle,
		[this]()
		{
			CharacterReference->GetWorldTimerManager().SetTimer(RegenHandle, this, &UStaminaComponent::RegenStamina, 0.01f, true);
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
		DrainStamina();

		if (Stamina <= 0.0f)
		{
			Stamina = 0.0f;
			CanSprint = false;
			StopSprint();
		}

		CharacterReference->GetWorldTimerManager().ClearTimer(RegenHandle);
		bIsWaitingToRegen = false;
	}
	else
	{
		StartDelayedRegen();
	}

	if (!CanSprint && Stamina > 0.0f)
	{
		CanSprint = true;
	}
}
