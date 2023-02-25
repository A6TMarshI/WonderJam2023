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

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;
	
	void Convert();

	UPROPERTY(EditAnywhere)
	bool bIsConvertedToCult = false;

	//set up sphere collider to seek for non converted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Collider")
	class USphereComponent* SphereCollider;

	UFUNCTION()
	void OnNonConvertedDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
