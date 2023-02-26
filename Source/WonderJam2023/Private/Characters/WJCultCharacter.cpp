// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WJCultCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Gameplay/WJPointOfInterestAssistant.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWJCultCharacter::AWJCultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	ChaseSphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Chase Sphere Collider"));
	ChaseSphereCollider->SetupAttachment(RootComponent);
	ChaseSphereCollider->SetSphereRadius(600.f);
	ChaseSphereCollider->SetGenerateOverlapEvents(true);
	ChaseSphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ChaseSphereCollider->bHiddenInGame = true;
}

void AWJCultCharacter::OnNonConvertedDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsConvertedToCult)
	{
		if(auto Target = Cast<AWJCultCharacter>(OtherActor))
		{
			if (!Target->GetIsConverted() && !Target->bIsTargeted)
			{
				// AIController = Cast<AWJCultController>(GetController());
				if (AIController)
				{
					if(!AIController->TargetToConvert)
					{
						Target->bIsTargeted = true;
						AIController->TargetToConvert = Target;
						AIController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsObject(FName("TargetToConvert"), Target);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("New Target to Convert"));
					}
				}
			}
		}
	}
}

void AWJCultCharacter::Arrest()
{
	bIsConvertedToCult = false;
	GetWorld()->GetTimerManager().SetTimer(ArrestDebuffTimerHandle, this, &AWJCultCharacter::ResetArrestedStatus, 10, false);
}

void AWJCultCharacter::HasEaten()
{
	FoodRateModifier = 0;
	GetWorld()->GetTimerManager().SetTimer(EatenBuffTimerHandle, this, &AWJCultCharacter::ResetFoodModifier, 10, false);
}

void AWJCultCharacter::ResetFoodModifier()
{
	FoodRateModifier = -5;
}

void AWJCultCharacter::ResetPrayingModifier()
{
	FaithRateModifier = -5;
}

void AWJCultCharacter::HasPrayed()
{
	FaithRateModifier = 5;
	GetWorld()->GetTimerManager().SetTimer(PrayedBuffTimerHandle, this, &AWJCultCharacter::ResetPrayingModifier, 10, false );
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
	//auto
	AIController = Cast<AWJCultController>(GetController());
	AIController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsConvertedToCult"), bIsConvertedToCult);
	AIController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsReadyToTalk"), false);
	
	world = GetWorld();
	UGameplayStatics::GetAllActorsWithTag(world, "PoIAssistant", FoundPointOfInterest);
	if(FoundPointOfInterest.IsEmpty())
	{
		PointOfInterestAssistant = Cast<AWJPointOfInterestAssistant>(FoundPointOfInterest[0]);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("PoIAssistant cant be found"));
	}
	
	GetWorld()->GetTimerManager().SetTimer(NeedTimerHandle, this, &AWJCultCharacter::UpdateNeed, DecreaseNeedTime, true );
	
}

void AWJCultCharacter::UpdateNeed()
{
	Food += FoodRateModifier;
	Faith += FaithRateModifier;
	UpdateBehaviourToNeed();
}

void AWJCultCharacter::ResetArrestedStatus()
{
	AIController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsBool(FName("IsArrested"), false);
}

bool AWJCultCharacter::CharacterNeedToEat() const
{
	return Food <= 50;
}

void AWJCultCharacter::GoToRestaurant()
{
	AIController->GetBlackboardComponent()->SetValueAsBool(FName("bNeedToEat"), true);
	AIController->GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), PointOfInterestAssistant->GetPointOfInterest(Restaurant));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Munching time"));
}

bool AWJCultCharacter::CharacterNeedToPray() const
{
	return Faith <= 40;
}

void AWJCultCharacter::GoToBaseToPray()
{
	AIController->GetBlackboardComponent()->SetValueAsBool(FName("bNeedToPray"), true);
	AIController->GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), PointOfInterestAssistant->GetPointOfInterest(CultBase));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("OH! My God time"));
}

bool AWJCultCharacter::CharacterIsHurt() const
{
	return Health < 3;
}

void AWJCultCharacter::GoToHospitalToHeal()
{
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsHurt"), true);
		AIController->GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), PointOfInterestAssistant->GetPointOfInterest(Hospital));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Wahhbulance"));
}

void AWJCultCharacter::UpdateBehaviourToNeed()
{
	if (AIController)
	{
		if(CharacterIsHurt())
			GoToHospitalToHeal();
		if(CharacterNeedToPray())
			GoToBaseToPray();
		if(CharacterNeedToEat())
			GoToRestaurant();
	}
}

void AWJCultCharacter::Heal()
{
	Health = 3;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Whats up doc!"));
}

void AWJCultCharacter::Hurt()
{
	Health--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OUCHHH! POLICEEE!"));
	if(Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("R.I.P - Im dead."));

	//Character die.
	}
}




