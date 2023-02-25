// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "Components/SphereComponent.h"

// Sets default values
AWJCultCharacter::AWJCultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Attacking Cullusion"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSphereRadius(700.f);
	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollider->bHiddenInGame = false;

}

void AWJCultCharacter::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	CultController->RandomPatrol();
}

void AWJCultCharacter::Convert()
{
}

void AWJCultCharacter::OnCharacterDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("We got a collision."));
}

// Called when the game starts or when spawned
void AWJCultCharacter::BeginPlay()
{
	Super::BeginPlay();
	CultController = Cast<AWJCultController>(GetController());
	CultController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AWJCultCharacter::OnAIMoveCompleted);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AWJCultCharacter::OnCharacterDetected);
}


