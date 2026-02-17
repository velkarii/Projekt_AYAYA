#include "HitDetection.h"
#include "Projekt_AYAYA/Health/HealthComponent.h"
#include "Projekt_AYAYA/Player/MainCharacter.h"
#include "Projekt_AYAYA/Enemies/EnemyActorBase.h"

UHitDetection::UHitDetection()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UHitDetection::StartDetection(USkeletalMeshComponent* MeshComp, AActor* Owner, TSubclassOf<UAttackTypeBase> AttackType)
{
	HitActors.Empty();

	if (AttackType)
	{
		CurrentAttack = NewObject<UAttackTypeBase>(this, AttackType);
		CurrentAttack->InitializeAttack(MeshComp, Owner, &HitActors);

		SetComponentTickEnabled(true);
	}
}

void UHitDetection::StopDetection()
{
	SetComponentTickEnabled(false);
	int i = 0;
	for (auto HitActor : HitActors)
	{
		if (!HitActor)
			continue;

		GEngine->AddOnScreenDebugMessage(i++, 5.f, FColor::Red, FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetClass()->GetFName().ToString()));

		AMainCharacter* Character = Cast<AMainCharacter>(HitActor);
		AEnemyActorBase* Enemy = Cast<AEnemyActorBase>(HitActor);

		if (Character && Character->HealthComponent && !Character->HealthComponent->IsDead())
		{
			Character->HealthComponent->TakeDamage(25.f);
			
		}
		else if (Enemy && Enemy->HealthComponent && !Enemy->HealthComponent->IsDead())
		{
			Enemy->HealthComponent->TakeDamage(25.f);
		}


	}
}

void UHitDetection::BeginPlay()
{
	Super::BeginPlay();
}

void UHitDetection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentAttack)
	{
		CurrentAttack->ExecuteAttack();
	}
}