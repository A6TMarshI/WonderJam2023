// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controller/WJCultController.h"
#include "NavigationSystem.h"

AWJCultController::AWJCultController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWJCultController::StartConvert()
{
	ControlledPawn->Convert();
}

void AWJCultController::RandomPatrol()
{
	NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(),
		   RandomLocation, 15000.0f);

	MoveToLocation(RandomLocation);
}

void AWJCultController::BeginPlay()
{
	Super::BeginPlay();
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	RandomPatrol();
}
