// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/WJInputConfig.h"


const UInputAction* UWJInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const auto& TaggedInputAction : TaggedInputActions)
	{
		if(TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return  TaggedInputAction.InputAction;
		}
	}
	return nullptr;
}