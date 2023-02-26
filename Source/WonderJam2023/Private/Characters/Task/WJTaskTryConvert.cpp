// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskTryConvert.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/WJCultController.h"
#include "Characters/WJCultCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskTryConvert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	if(auto* OwnerController = Cast<AWJCultController>(OwnerComp.GetOwner()))
	{
		auto AITargetController = Cast<AWJCultController>(OwnerController->TargetToConvert->GetController());
		if(auto* AICharacter = Cast<AWJCultCharacter>(OwnerController->GetCharacter()))
		{
			int chance;
			if(!AICharacter->bisLuckyToConvert)
			{
				chance = FMath::RandRange(1, 4);
			}
			else
			{
				chance = FMath::RandRange(1, 2);
			}
			if(chance == 1)
			{
				OwnerController->TargetToConvert->ConvertToCult();
				AITargetController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsConvertedToCult"), true);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("converted"));
			}
		}
		OwnerComp.GetBlackboardComponent()->ClearValue(FName("TargetToConvert"));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsReadyToTalk"), false);
		AITargetController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsReadyToTalk"), false);
		OwnerController->TargetToConvert->bIsTargeted = false;
		OwnerController->TargetToConvert = nullptr;
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
