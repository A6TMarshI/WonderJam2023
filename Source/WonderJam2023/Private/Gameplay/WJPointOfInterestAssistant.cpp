// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WJPointOfInterestAssistant.h"

#include "Kismet/GameplayStatics.h"


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
	UWorld* world = GetWorld();
	UGameplayStatics::GetAllActorsWithTag(world, "Restaurant", Restaurants);
	UGameplayStatics::GetAllActorsWithTag(world, "CultBase", CultBases);
	UGameplayStatics::GetAllActorsWithTag(world, "Hospital", Hospitals);
}

FVector3d AWJPointOfInterestAssistant::GetHospitalLocationVector()
{
	if(!Hospitals.IsEmpty())
	{
		int chance = FMath::RandRange(0, Hospitals.Num()-1);
		return Hospitals[chance]->GetTransform().GetLocation();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Cant find hospital"));
	return FVector3d().Zero();
}

FVector3d AWJPointOfInterestAssistant::GetRestaurantLocationVector()
{
	if(!Restaurants.IsEmpty())
	{
		int chance = FMath::RandRange(0, Restaurants.Num()-1);
		return Restaurants[chance]->GetTransform().GetLocation();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Cant find restaurant"));
	return FVector3d().Zero();
}

FVector3d AWJPointOfInterestAssistant::GetCultBaseLocationVector()
{
	if(!CultBases.IsEmpty())
	{
		int chance = FMath::RandRange(0, CultBases.Num()-1);
		return CultBases[chance]->GetTransform().GetLocation();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Cant find Cult base"));
	return FVector3d().Zero();
}
