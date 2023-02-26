// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WJCultController.generated.h"


class AWJCultCharacter;
/**
 * 
 */
UCLASS()
class WONDERJAM2023_API AWJCultController : public AAIController
{
	GENERATED_BODY()

public:
	AWJCultController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;

	TObjectPtr<AWJCultCharacter> TargetToConvert;

	UPROPERTY(EditAnywhere)
	bool bNeedToEat = false;
	UPROPERTY(EditAnywhere)
	bool bNeedToPray = false;
	UPROPERTY(EditAnywhere)
	bool bIsFleeing = false;
	UPROPERTY(EditAnywhere)
	bool bIsHurt = false;
	UPROPERTY(EditAnywhere)
	bool bCanChangeState = true;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
