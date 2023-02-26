// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/WJCopsCharacter.h"
#include "Characters/Controller/WJCopsController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/WJCultCharacter.h"
#include "Components/SphereComponent.h"


AWJCopsCharacter::AWJCopsCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ChaseSphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Chase Sphere Collider"));
	ChaseSphereCollider->SetupAttachment(RootComponent);
	ChaseSphereCollider->SetSphereRadius(600.f);
	ChaseSphereCollider->SetGenerateOverlapEvents(true);
	ChaseSphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ChaseSphereCollider->bHiddenInGame = true;
}

void AWJCopsCharacter::OnArrest_Implementation(float time)
{
}

void AWJCopsCharacter::OnIdle_Implementation(float time)
{
}

void AWJCopsCharacter::OnCultDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto Target = Cast<AWJCultCharacter>(OtherActor))
	{
		if (Target->GetIsConverted())
		{
			if (auto AIController = Cast<AWJCopsController>(GetController()))
			{
				if(!AIController->TargetToArrest|| AIController->TargetToArrest == nullptr)
				{
					Target->bIsTargeted = true;
					AIController->TargetToArrest = Target;
					AIController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsObject(FName("TargetToArrest"), Target);
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("New Target To Arrest"));
				}
			}
		}
	}
}

void AWJCopsCharacter::BeginPlay()
{
	Super::BeginPlay();
	ChaseSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCultDetected);
}

