// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Task/WJTaskStopTalkersMoving.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UWJTaskStopTalkersMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* OwnerController = Cast<AWJCultController>(OwnerComp.GetOwner()))
		{
			auto AITargetController = Cast<AWJCultController>(OwnerController->TargetToConvert->GetController());
			AITargetController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsReadyToTalk"), true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsReadyToTalk"), false);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ready to talk"));
			return EBTNodeResult::Succeeded;
		}
	return EBTNodeResult::Failed;
}
