// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WJCultCharacter.generated.h"

UCLASS()
class WONDERJAM2023_API AWJCultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWJCultCharacter();

	class AWJCultController* CultController;

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

	void Convert();
	void TryToConvert(AWJCultCharacter* Target);

	void SeekTarget();

	//Is the character converted to the cult
	UPROPERTY(EditAnywhere)
	bool bIsConverted = false;

	AWJCultCharacter* TargetToConvert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Collider")
	class USphereComponent* SphereCollider;
	
	UFUNCTION()
	void OnCharacterDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float StoppingDistance = 100.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
