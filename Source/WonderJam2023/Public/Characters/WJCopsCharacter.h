// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "WJCopsCharacter.generated.h"

UCLASS()
class WONDERJAM2023_API AWJCopsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWJCopsCharacter();
	
	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Collider")
	class USphereComponent* ChaseSphereCollider;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnArrest(float time);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnIdle(float time);
	

	UFUNCTION()
	void OnCultDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
