// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WJInputConfig.h"
#include "EnhancedInputComponent.h"
#include "WJTaggedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WONDERJAM2023_API UWJTaggedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename FuncType>
	void BindActionsByTag(const UWJInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
	{
		check(InputConfig)
		if(const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
		{
			BindAction(IA, TriggerEvent, Object, Func);
		}
	}
};
