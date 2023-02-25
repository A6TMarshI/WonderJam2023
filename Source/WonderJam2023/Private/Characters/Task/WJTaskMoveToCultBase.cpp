// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskMoveToCultBase.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskMoveToCultBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(NavigationSystem)
	{
		TArray<AActor*> FoundPointOfInterest;
		FName TagToFind = TEXT("PoI-CultBase");
		UWorld* world = GetWorld();
		UGameplayStatics::GetAllActorsWithTag(world, TagToFind, FoundPointOfInterest);

		if(!FoundPointOfInterest.IsEmpty())
		{
			TargetLocation =  FoundPointOfInterest[0]->GetTargetLocation();
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), TargetLocation);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
