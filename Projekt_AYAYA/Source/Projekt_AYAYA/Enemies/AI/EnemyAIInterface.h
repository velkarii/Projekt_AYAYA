#pragma once

#include "PatrolRoute.h"

class EnemyAIInterface
{
public:
	virtual TSubclassOf<AActor> GetPatrolRoute();
};