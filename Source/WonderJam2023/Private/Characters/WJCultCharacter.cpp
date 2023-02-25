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
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	ChaseSphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	ChaseSphereCollider->SetupAttachment(RootComponent);
	ChaseSphereCollider->SetSphereRadius(700.f);
	ChaseSphereCollider->SetGenerateOverlapEvents(true);
	ChaseSphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ChaseSphereCollider->bHiddenInGame = true;
}


void AWJCultCharacter::Convert()
{
}

void AWJCultCharacter::OnNonConvertedDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsConvertedToCult)
	{
		auto Target = Cast<AWJCultCharacter>(OtherActor);
		if (!Target->GetIsConverted())
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

bool AWJCultCharacter::GetIsConverted()
{
	return bIsConvertedToCult;
}

void AWJCultCharacter::ConvertToCult()
{
	bIsConvertedToCult = true;
	MeshComponent->SetSkeletalMesh(CultMesh);
}

// Called when the game starts or when spawned
void AWJCultCharacter::BeginPlay()
{
	Super::BeginPlay();
	ChaseSphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AWJCultCharacter::OnNonConvertedDetected);
}


