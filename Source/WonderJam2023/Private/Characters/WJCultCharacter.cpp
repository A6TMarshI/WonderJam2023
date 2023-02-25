// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WJCultCharacter.h"


// Sets default values
AWJCultCharacter::AWJCultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWJCultCharacter::Convert()
{
}

// Called when the game starts or when spawned
void AWJCultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AWJCultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

