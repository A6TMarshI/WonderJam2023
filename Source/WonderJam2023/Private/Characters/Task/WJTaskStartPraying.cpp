// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskStartPraying.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"

EBTNodeResult::Type UWJTaskStartPraying::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* OwnerController = Cast<AWJCultController>(OwnerComp.GetOwner()))
		{
			if(auto* AICharacter = Cast<AWJCultCharacter>(OwnerController->GetCharacter()))
			{
				//Fire Animation ?
				AICharacter->bisLuckyToConvert = true;
				OwnerController->BehaviorTreeComponent->GetBlackboardComponent()->ClearValue(FName("SacrifyLocation"));
				return EBTNodeResult::Succeeded;
			}
		}
	return EBTNodeResult::Failed;
}
