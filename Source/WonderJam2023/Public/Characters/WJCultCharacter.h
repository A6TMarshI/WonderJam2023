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

	UPROPERTY(EditDefaultsOnly)
	bool bIsConvertedToCult = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
