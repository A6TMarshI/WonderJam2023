// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WJPointOfInterestAssistant.h"


// Sets default values
AWJPointOfInterestAssistant::AWJPointOfInterestAssistant()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FVector3d AWJPointOfInterestAssistant::GetPointOfInterest(PointOfInterestType typeOfPoI)
{
	
	switch (typeOfPoI)
	{
	case Hospital:
		return GetHospitalLocationVector();
	case Restaurant:
		return GetRestaurantLocationVector();
	case CultBase:
		return GetCultBaseLocationVector();
	default:
		return FVector3d().Zero();
	}
}

// Called when the game starts or when spawned
void AWJPointOfInterestAssistant::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector3d AWJPointOfInterestAssistant::GetHospitalLocationVector()
{
	int chance = FMath::RandRange(0, Hospitals.Num()-1);
	return Hospitals[chance]->GetTransform().GetLocation();
}

FVector3d AWJPointOfInterestAssistant::GetRestaurantLocationVector()
{
	int chance = FMath::RandRange(0, Restaurants.Num()-1);
	return Restaurants[chance]->GetTransform().GetLocation();
}

FVector3d AWJPointOfInterestAssistant::GetCultBaseLocationVector()
{
	int chance = FMath::RandRange(0, CultBases.Num()-1);
	return CultBases[chance]->GetTransform().GetLocation();
}
