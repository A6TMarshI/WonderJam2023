// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskTryConvert.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskTryConvert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* OwnerController = Cast<AWJCultController>(OwnerComp.GetOwner()))
		{
			int chance = FMath::RandRange(1, 4);
			if(chance == 1)
			{
				OwnerController->TargetToConvert->ConvertToCult();
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("converted"));
			}
			OwnerComp.GetBlackboardComponent()->ClearValue(FName("TargetToConvert"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("not converted"));
			return EBTNodeResult::Succeeded;
		}
	return EBTNodeResult::Failed;
}
