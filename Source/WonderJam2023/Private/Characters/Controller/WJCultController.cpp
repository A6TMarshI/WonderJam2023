// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controller/WJCultController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Controller/BlackboardKeys.h"

AWJCultController::AWJCultController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create components
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AWJCultController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Get possessed pawn
	AWJCultCharacter* CultPawn = Cast<AWJCultCharacter>(InPawn);
	checkf(CultPawn, TEXT("Controller not possessing a cult pawn"));
	ControlledPawn = CultPawn;

	// Initialize blackboard and start behavior tree
	if (UBehaviorTree* BehaviorTree = CultPawn->BehaviorTree; ensureMsgf(IsValid(BehaviorTree), TEXT("No assigned behavior tree on cult character")))
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*BehaviorTree);

		GetBlackboard()->SetValueAsObject(BBKeys::SelfActor, CultPawn);
	}
}

void AWJCultController::StartConvert()
{
	ControlledPawn->Convert();
}
