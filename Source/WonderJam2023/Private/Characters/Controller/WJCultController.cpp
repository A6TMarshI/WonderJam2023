// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controller/WJCultController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AWJCultController::AWJCultController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCOmponent"));
}

void AWJCultController::StartConvert()
{
	//ControlledPawn->Convert();
}

void AWJCultController::RandomPatrol()
{
	/*NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(),
		   RandomLocation, 15000.0f);

	MoveToLocation(RandomLocation);*/
}

void AWJCultController::BeginPlay()
{
	Super::BeginPlay();
	/*NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	RandomPatrol();*/
}

void AWJCultController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(auto* AICharacter = Cast<AWJCultCharacter>(InPawn))
	{
		if(!AICharacter->BehaviorTree || !AICharacter->BehaviorTree->BlackboardAsset)return;

		BlackboardComponent->InitializeBlackboard(*AICharacter->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*AICharacter->BehaviorTree);
	}
}
