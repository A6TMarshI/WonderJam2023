// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Clickable/WJClickable.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AWJClickable::AWJClickable()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(RootComponent);

	for (int8 i=0; i<3;i++)
	{
		UWJClickableParticlesSpawn* Spawn = CreateDefaultSubobject<UWJClickableParticlesSpawn>(FName("Spawn"+FString::FromInt(i)));
		Spawn->SetupAttachment(StaticMeshComponent);
		AntennaParticlesSpawns.Add(Spawn);
	}
	ParticleCount=0;
}

void AWJClickable::SpawnParticles()
{
	
	if (Particle != nullptr && FMath::RandRange(0,10)==0 && ParticleCount<3)
	{
		FTransform ParticleT;
		const FVector ParticlePosition = AntennaParticlesSpawns[ParticleCount]->GetComponentLocation();
		ParticleT.SetLocation(ParticlePosition);
		ParticleT.SetScale3D(ParticleSize);
		
		auto* SparkParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ParticleT, true);
		SparkParticles.Add(SparkParticle);
		if(SparkSound)
		{
			UGameplayStatics::PlaySound2D( GetWorld(), SparkSound);
		}
		++ParticleCount;
	}
	if(ParticleCount==3)
	{
		FTransform ParticleT;
		ParticleT.SetLocation(GetActorLocation());
		ParticleT.SetScale3D(ParticleSize*ParticleExplosionSizeModifier);
		
		auto* SparkParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ParticleT, true);
		SparkParticles.Add(SparkParticle);
		if(ExplosionSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
		}

		ClickTimerHandle.Invalidate();
		GetWorld()->GetTimerManager().SetTimer(ClickTimerHandle, [this]()
		{
			OnClickableDestroyedDelegate.Broadcast();
			this->Destroy();
		},  ExplosionDelay, false);
		ParticleCount++;
	}
}

void AWJClickable::StartClickTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ClickTimerHandle, this, &ThisClass::HandleClickTimer, 1,true);
}

void AWJClickable::HandleClickTimer()
{
	OnClickedDelegate.Broadcast();
}

void AWJClickable::StopClickTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ClickTimerHandle);
}


void AWJClickable::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWJClickable::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	for (auto Spark : SparkParticles)
	{
		Spark->DestroyComponent();
	}
	
}

