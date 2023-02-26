// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskCopsPatrol.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/WJCopsController.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskCopsPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(NavigationSystem)
	{
		if(auto* OwnerController = Cast<AWJCopsController>(OwnerComp.GetOwner()))
		{
			if(NavigationSystem->K2_GetRandomReachablePointInRadius(GetWorld(), OwnerController->GetPawn()->GetActorLocation(),
		   TargetLocation, 15000.0f))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), TargetLocation);
				return EBTNodeResult::Succeeded;
			}
		}
		
	}
	
	return EBTNodeResult::Failed;
}
