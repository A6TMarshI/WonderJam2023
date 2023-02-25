// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTAskMoveToPoliceStation.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTAskMoveToPoliceStation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if(NavigationSystem)
	{
		TargetLocation = PoIPoliceStation->GetTransform().GetLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), TargetLocation);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
