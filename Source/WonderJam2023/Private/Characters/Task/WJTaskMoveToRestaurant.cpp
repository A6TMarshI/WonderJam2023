// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskMoveToRestaurant.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskMoveToRestaurant::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	if(auto* OwnerController = Cast<AWJCultController>(OwnerComp.GetOwner()))
	{
		if(auto* AICharacter = Cast<AWJCultCharacter>(OwnerController->GetCharacter()))
		{
			AICharacter->Food = 100;
			AICharacter->OnIdle(5);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Has eaten"));
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("bNeedToEat"), false);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
