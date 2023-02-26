// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "WJCopsCharacter.generated.h"

class UBehaviorTree;
UCLASS()
class WONDERJAM2023_API AWJCopsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWJCopsCharacter();
	
	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
