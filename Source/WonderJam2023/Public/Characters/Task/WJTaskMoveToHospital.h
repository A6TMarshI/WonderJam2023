// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WJTaskMoveToHospital.generated.h"

/**
 * 
 */
UCLASS()
class WONDERJAM2023_API UWJTaskMoveToHospital : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY()
	AActor* PoIHospital; 
private:
	FVector TargetLocation;
	
	class UNavigationSystemV1* NavigationSystem;
};
