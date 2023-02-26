// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WJInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FFPSTaggedInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta=(Categories = "InputTag"))
	FGameplayTag InputTag;
};

UCLASS()
class WONDERJAM2023_API UWJInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FFPSTaggedInputAction> TaggedInputActions;
};
