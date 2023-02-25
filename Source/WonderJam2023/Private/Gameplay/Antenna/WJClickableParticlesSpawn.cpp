// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Antenna/WJClickableParticlesSpawn.h"


UWJClickableParticlesSpawn::UWJClickableParticlesSpawn()
{
	PrimaryComponentTick.bCanEverTick = false;

	Mobility = EComponentMobility::Movable;
}


void UWJClickableParticlesSpawn::BeginPlay()
{
	Super::BeginPlay();

	
}

