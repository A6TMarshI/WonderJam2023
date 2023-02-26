// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controller/WJCopsController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AWJCopsController::AWJCopsController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AWJCopsController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWJCopsController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(auto* AICharacter = Cast<AWJCopsCharacter>(InPawn))
	{
		if(!AICharacter->BehaviorTree || !AICharacter->BehaviorTree->BlackboardAsset)return;

		BlackboardComponent->InitializeBlackboard(*AICharacter->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*AICharacter->BehaviorTree);
	}
}

