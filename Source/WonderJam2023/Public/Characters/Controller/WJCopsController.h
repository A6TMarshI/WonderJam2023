// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/WJCopsCharacter.h"
#include "WJCopsController.generated.h"


UCLASS()
class WONDERJAM2023_API AWJCopsController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWJCopsController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
};
