// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WJPointOfInterestAssistant.generated.h"

UENUM()
enum PointOfInterestType
{
	Hospital,
	Restaurant,
	CultBase
};

UCLASS()
class WONDERJAM2023_API AWJPointOfInterestAssistant : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWJPointOfInterestAssistant();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Point of Interest")
	TArray<AActor*> Hospitals;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Point of Interest")
	TArray<AActor*> Restaurants;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Point of Interest")
	TArray<AActor*> CultBases;

	UFUNCTION()
	FVector3d GetPointOfInterest(PointOfInterestType typeOfPoI);


protected:
	virtual void BeginPlay() override;
	FVector3d GetHospitalLocationVector();
	FVector3d GetRestaurantLocationVector();
	FVector3d GetCultBaseLocationVector();
	
};
