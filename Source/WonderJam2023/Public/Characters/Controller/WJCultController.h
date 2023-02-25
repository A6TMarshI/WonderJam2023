// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/WJCultCharacter.h"
#include "WJCultController.generated.h"

/**
 * 
 */
UCLASS()
class WONDERJAM2023_API AWJCultController : public AAIController
{
	GENERATED_BODY()

public:
	AWJCultController(const FObjectInitializer& ObjectInitializer);

	/** Calls the convert function of controlled pawn */
	UFUNCTION(BlueprintCallable, Category = "Convert")
	void StartConvert();

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
