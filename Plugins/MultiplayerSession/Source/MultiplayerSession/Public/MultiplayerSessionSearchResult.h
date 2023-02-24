// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionSearchResult.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MULTIPLAYERSESSION_API FMultiplayerSessionSearchResult
{
	GENERATED_BODY()
	
	FOnlineSession Session;
	int32 PingInMs;
	FOnlineSessionSearchResult Native;
};
