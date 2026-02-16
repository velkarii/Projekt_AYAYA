// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Components/CapsuleComponent.h"
#include "InvokeAttackLogic.generated.h"

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core", meta = (GetOptions = "GetSocketOptions"))
	FName AttachSocketName = "SocketHandR";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UStaticMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float Radius = 12.f;
};

UCLASS()
class PROJEKT_AYAYA_API UInvokeAttackLogic : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	
public:
	void InvokeHitboxLogic(USkeletalMeshComponent* MeshComp, AActor* Owner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeapon> Weapons;

	UFUNCTION()
	TArray<FString> GetSocketOptions() const
	{
		return {
			TEXT("SocketHandR"),
			TEXT("SocketHandL")
		};
	}

private:
	TArray<TObjectPtr<UCapsuleComponent>> Hitboxes;

	float error_margin = 0.0001f;
};
