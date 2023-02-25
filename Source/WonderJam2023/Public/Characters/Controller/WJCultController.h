// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/WJCultCharacter.h"
#include "WJCultController.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable)
class WONDERJAM2023_API AWJCultController : public AAIController
{
	GENERATED_BODY()

public:
	AWJCultController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;
	UBlackboardComponent* GetBlackboard() const { return BlackboardComponent; }

	/** Calls the convert function of controlled pawn */
	UFUNCTION(BlueprintCallable, Category = "Convert")
	void StartConvert();

protected:
	/** The cult pawn possessed by this controller */
	UPROPERTY(BlueprintReadOnly)
	AWJCultCharacter* ControlledPawn;

private:
	/** The component that starts the behavior tree */
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorTreeComponent;

	/** The component that initializes the blackboard */
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent;
};
