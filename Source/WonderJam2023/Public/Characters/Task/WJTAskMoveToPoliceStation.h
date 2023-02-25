// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WJTAskMoveToPoliceStation.generated.h"

/**
 * 
 */
UCLASS()
class WONDERJAM2023_API UWJTAskMoveToPoliceStation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY()
	AActor* PoIPoliceStation;
private:
	FVector TargetLocation;

	class UNavigationSystemV1* NavigationSystem;
	
};
