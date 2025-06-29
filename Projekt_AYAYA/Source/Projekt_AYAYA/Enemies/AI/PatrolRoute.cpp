// Fill out your copyright notice in the Description page of Project Settings.
#include "PatrolRoute.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
	PatrolRoute = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRoute"));
	PatrolRoute->RegisterComponent();
	PatrolRoute->SetupAttachment(RootComponent);
}

void APatrolRoute::IncrementPatrolRoute()
{
	PatrolIndex += Direction;
	if ((PatrolRoute->GetNumberOfSplinePoints() - 1) == PatrolIndex)
	{
		Direction = -1;
	}
	else if (PatrolIndex == 0)
	{
		Direction = 1;
	}
}

FVector APatrolRoute::GetSplinePointAsWorldPosition()
{
	return PatrolRoute->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);
}

