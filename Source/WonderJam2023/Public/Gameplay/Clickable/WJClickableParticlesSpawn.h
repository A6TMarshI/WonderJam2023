// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WJClickableParticlesSpawn.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WONDERJAM2023_API UWJClickableParticlesSpawn : public UMeshComponent
{
	GENERATED_BODY()

public:
	UWJClickableParticlesSpawn();

protected:
	virtual void BeginPlay() override;
};
