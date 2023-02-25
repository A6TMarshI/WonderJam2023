// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Antenna/WJAntennaParticlesSpawn.h"


UWJAntennaParticlesSpawn::UWJAntennaParticlesSpawn()
{
	PrimaryComponentTick.bCanEverTick = false;

	Mobility = EComponentMobility::Movable;
}


void UWJAntennaParticlesSpawn::BeginPlay()
{
	Super::BeginPlay();

	
}

