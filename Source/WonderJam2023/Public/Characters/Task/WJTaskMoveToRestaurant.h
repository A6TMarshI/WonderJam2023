// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WJTaskMoveToRestaurant.generated.h"

/**
 * 
 */
UCLASS()
class WONDERJAM2023_API UWJTaskMoveToRestaurant : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY()
	AActor* PoIRestaurant;
private:
	FVector TargetLocation;

	class UNavigationSystemV1* NavigationSystem;
	
};
