// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WJAntennaParticlesSpawn.h"
#include "GameFramework/Actor.h"
#include "WJAntenna.generated.h"

UCLASS()
class WONDERJAM2023_API AWJAntenna : public AActor
{
	GENERATED_BODY()

public:
	AWJAntenna();

	int SpawnParticles();

protected:
	virtual void BeginPlay() override;
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* SparkSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, Category="Particles")
	class UParticleSystem* Particle;

	TArray<UParticleSystemComponent*> SparkParticles; 

	int ParticleCount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="SpawnLocation", meta = (AllowPrivateAccess = "true"))
	TArray<UWJAntennaParticlesSpawn*> AntennaParticlesSpawns;

	
	
};
