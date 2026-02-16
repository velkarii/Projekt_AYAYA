// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "PatrolRoute.generated.h"

UCLASS()
class PROJEKT_AYAYA_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolRoute();

	void IncrementPatrolRoute();
	FVector GetSplinePointAsWorldPosition();

public:
	int PatrolIndex;
	int Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Route")
	USplineComponent* PatrolRoute;
};
