// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WJClickableParticlesSpawn.h"
#include "GameFramework/Actor.h"
#include "WJClickable.generated.h"



class UWJClickableParticlesSpawn;
UCLASS()
class WONDERJAM2023_API AWJClickable : public AActor
{
	GENERATED_BODY()

public:
	AWJClickable();

	int SpawnParticles();

	UPROPERTY(EditAnywhere, Category="Delay")
	int ExplosionDelay;

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

	UPROPERTY(EditAnywhere, Category="Particles")
	FVector ParticleSize;
	UPROPERTY(EditAnywhere, Category="Particles")
	int ParticleExplosionSizeModifier;

	TArray<UParticleSystemComponent*> SparkParticles; 

	int ParticleCount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="SpawnLocation", meta = (AllowPrivateAccess = "true"))
	TArray<UWJClickableParticlesSpawn*> AntennaParticlesSpawns;

	
	
};
