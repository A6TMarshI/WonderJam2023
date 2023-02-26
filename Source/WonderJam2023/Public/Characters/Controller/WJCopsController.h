// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/WJCultCharacter.h"
#include "Characters/WJCopsCharacter.h"
#include "WJCopsController.generated.h"


UCLASS()
class WONDERJAM2023_API AWJCopsController : public AAIController
{
	GENERATED_BODY()

public:
	AWJCopsController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;

	TObjectPtr<AWJCultCharacter> TargetToArrest;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
};
