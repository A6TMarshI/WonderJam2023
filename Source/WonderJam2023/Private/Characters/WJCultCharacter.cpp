// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WJCultCharacter.h"
#include "Characters/Controller/WJCultController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AWJCultCharacter::AWJCultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSphereRadius(700.f);
	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollider->bHiddenInGame = true;
}


void AWJCultCharacter::Convert()
{
}

void AWJCultCharacter::OnNonConvertedDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsConvertedToCult)
	{
		auto Target = Cast<AWJCultCharacter>(OtherActor);
		if (!Target->bIsConvertedToCult)
		{
			auto AIController = Cast<AWJCultController>(GetController());
			if (AIController)
			{
				AIController->TargetToConvert = Target;
				AIController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsObject(FName("TargetToConvert"), Target);
			}
		}
	}
}

// Called when the game starts or when spawned
void AWJCultCharacter::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AWJCultCharacter::OnNonConvertedDetected);
}


