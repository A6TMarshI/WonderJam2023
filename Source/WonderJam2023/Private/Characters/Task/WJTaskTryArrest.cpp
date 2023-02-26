// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskTryArrest.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/WJCopsController.h"
#include "Characters/Controller/WJCultController.h"

EBTNodeResult::Type UWJTaskTryArrest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* OwnerController = Cast<AWJCopsController>(OwnerComp.GetOwner()))
	{
		if(auto AITargetController = Cast<AWJCultController>(OwnerController->TargetToArrest->GetController()))
		{
			int chance = FMath::RandRange(1, 4);
			if(chance == 1)
			{
				AITargetController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsConvertedToCult"), false);
				AITargetController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsArrested"), true);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Arrested"));
			}
			OwnerComp.GetBlackboardComponent()->ClearValue(FName("TargetToArrest"));
			OwnerController->TargetToArrest->bIsTargeted = false;
			OwnerController->TargetToArrest = nullptr;
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
