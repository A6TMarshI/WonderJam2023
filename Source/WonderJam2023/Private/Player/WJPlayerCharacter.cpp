// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WJPlayerCharacter.h"
//#include <ocidl.h>   //Commented due to bug.


#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/WJCultCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Gameplay/Clickable/WJClickable.h"
#include "GameplayTags/WJGameplayTags.h"
#include "Inputs/WJTaggedInputComponent.h"


// Sets default values
AWJPlayerCharacter::AWJPlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create player collision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerSphere"));
	SphereCollision->SetSphereRadius(100.f);
	SphereCollision->SetupAttachment(RootComponent);
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(SphereCollision);
	FollowCamera->SetRelativeRotation(FRotator(-90.f,0.f,0.f));
	FollowCamera->SetRelativeLocation(FVector(0.f, 0.f, 90.f));

	// Add movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement Component"));
	SphereCollision->SetupAttachment(RootComponent);
	
	
}

void AWJPlayerCharacter::InputMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
	
}

void AWJPlayerCharacter::InputZoom(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		AddMovementInput(FVector(0,0,1), Value.Get<float>());
	}
}

void AWJPlayerCharacter::InputInteract(const FInputActionValue& Value)
{
	const auto bIsInteract = Value.Get<bool>();

	if(Controller==nullptr || bIsInteract==false)return;

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursorForObjects(ObjectTypes, false, HitResult);

	if(HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			if(auto* Clickable = Cast<AWJClickable>(HitActor))
			{
				Clickable->StartClickTimer();
			}
			if(auto* Cult = Cast<AWJCultCharacter>(HitActor))
			{
				if(!Cult->bIsArrested)return;
				OnClickedCultArested.Broadcast(Cult);
			}
		}
	}
}

// Called when the game starts or when spawned
void AWJPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWJPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWJPlayerCharacter::MakeSacrifice(FVector3d Location)
{
	TArray<FHitResult> OutHits;
	FCollisionShape ColSphere = FCollisionShape::MakeSphere(1000.f);
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, Location, Location, FQuat::Identity, ECC_WorldStatic, ColSphere);
	int NeededConvert = 0;
	TArray<AWJCultCharacter*> Sacrifiers;
	if(isHit)
	{
		for(auto& Hit : OutHits)
		{
			auto Character = Cast<AWJCultCharacter>(Hit.GetActor());
			if(Character)
			{
				if(Character->GetIsConverted())
				{
					if(!Sacrifiers.Contains(Character))
					{
						NeededConvert++;
						Sacrifiers.Add(Character);
					}
				}
			}
			if(NeededConvert==3)
				break;
		}
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("needconvert : %d"),NeededConvert));
		if(NeededConvert<3)
		{
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, TEXT("not enough sacrifiers"));
			return;
		}
		for(auto& Sacrifier : Sacrifiers)
		{
			auto CultController = Cast<AWJCultController>(Sacrifier->GetController());
			CultController->BehaviorTreeComponent->GetBlackboardComponent()->SetValueAsVector(FName("SacrifyLocation"), Location);
		}
	}
}

// Called to bind functionality to input
void AWJPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* TaggedInputComponent = Cast<UWJTaggedInputComponent>(PlayerInputComponent);
	check(TaggedInputComponent);

	TaggedInputComponent->BindActionsByTag(InputConfig, TAG_Input_Move, ETriggerEvent::Triggered
		, this, &AWJPlayerCharacter::InputMove);
	
	TaggedInputComponent->BindActionsByTag(InputConfig, TAG_Input_Zoom, ETriggerEvent::Triggered
		, this, &AWJPlayerCharacter::InputZoom);
	TaggedInputComponent->BindActionsByTag(InputConfig, TAG_Input_Interact, ETriggerEvent::Triggered
		,this,&ThisClass::InputInteract);
}

void AWJPlayerCharacter::BoxTrace(const FVector& MouseLocation)
{
	FVector StartLocation = MouseLocation;
	
}

