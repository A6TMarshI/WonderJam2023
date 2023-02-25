// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"

// Sets default values
AWJCultCharacter::AWJCultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWJCultCharacter::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	CultController->RandomPatrol();
}

void AWJCultCharacter::Convert()
{
}

// Called when the game starts or when spawned
void AWJCultCharacter::BeginPlay()
{
	Super::BeginPlay();
	CultController = Cast<AWJCultController>(GetController());
	CultController->GetPathFollowingComponent()->OnRequestFinished.AddUObject
	(this, &AWJCultCharacter::OnAIMoveCompleted);
}


