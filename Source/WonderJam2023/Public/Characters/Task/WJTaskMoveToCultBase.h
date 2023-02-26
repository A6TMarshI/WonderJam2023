// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WJTaskMoveToCultBase.generated.h"

/**
 * 
 */
UCLASS()
class WONDERJAM2023_API UWJTaskMoveToCultBase : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY()
	AActor* PoIHCultBase; 
private:
	FVector TargetLocation;

	class UNavigationSystemV1* NavigationSystem;
};
