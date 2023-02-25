// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WJAntennaParticlesSpawn.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WONDERJAM2023_API UWJAntennaParticlesSpawn : public UMeshComponent
{
	GENERATED_BODY()

public:
	UWJAntennaParticlesSpawn();

protected:
	virtual void BeginPlay() override;
};
