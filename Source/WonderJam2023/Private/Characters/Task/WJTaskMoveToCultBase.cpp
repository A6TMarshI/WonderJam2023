// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskMoveToCultBase.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskMoveToCultBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* OwnerController = Cast<AWJCultController>(OwnerComp.GetOwner()))
	{
		if(auto* AICharacter = Cast<AWJCultCharacter>(OwnerController->GetCharacter()))
		{
			AICharacter->Faith = 100;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Have Mercy God"));
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("bNeedToPray"), false);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
