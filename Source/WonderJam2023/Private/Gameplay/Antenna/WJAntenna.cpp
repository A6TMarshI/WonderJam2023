// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Antenna/WJAntenna.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AWJAntenna::AWJAntenna()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(RootComponent);

	for (int8 i=0; i<3;i++)
	{
		UWJAntennaParticlesSpawn* Spawn = CreateDefaultSubobject<UWJAntennaParticlesSpawn>(FName("Spawn"+FString::FromInt(i)));
		Spawn->SetupAttachment(StaticMeshComponent);
		AntennaParticlesSpawns.Add(Spawn);
	}
	ParticleCount=0;
}

int AWJAntenna::SpawnParticles()
{
	if (Particle != nullptr && FMath::RandRange(0,10)==0 && ParticleCount<3)
	{
		FTransform ParticleT;
		const FVector ParticlePosition = AntennaParticlesSpawns[ParticleCount]->GetComponentLocation();
		ParticleT.SetLocation(ParticlePosition);
		ParticleT.SetScale3D(FVector(10, 10, 10));
		
		auto* SparkParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ParticleT, true);
		SparkParticles.Add(SparkParticle);
		if(SparkSound)
		{
			UGameplayStatics::PlaySound2D( GetWorld(), SparkSound);
		}
		return ParticleCount++;
	}
	else if(ParticleCount==3)
	{
		FTransform ParticleT;
		ParticleT.SetLocation(GetActorLocation());
		ParticleT.SetScale3D(FVector(100, 100, 100));
		
		auto* SparkParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ParticleT, true);
		SparkParticles.Add(SparkParticle);
		if(ExplosionSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
		}
		ParticleCount++;
	}
	return ParticleCount;
}

void AWJAntenna::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWJAntenna::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	for (auto Spark : SparkParticles)
	{
		Spark->DestroyComponent();
	}
	
}

