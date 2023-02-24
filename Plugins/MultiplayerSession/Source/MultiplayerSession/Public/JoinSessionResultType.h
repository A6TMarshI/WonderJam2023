// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JoinSessionResultType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EJoinSessionResultType
{
	/** The join worked as expected */
	Success  UMETA(DisplayName = "Success", ToolTip = "Successfully joined session"),
	/** There are no open slots to join */
	SessionIsFull UMETA(DisplayName = "Full", ToolTip = "Session is full"),
	/** The session couldn't be found on the service */
	SessionDoesNotExist UMETA(DisplayName = "DoesNotExist", ToolTip = "Session does not exist"),
	/** There was an error getting the session server's address */
	CouldNotRetrieveAddress UMETA(DisplayName = "CouldNotRetrieveAddress", ToolTip = "Unable to get session IP address"),
	/** The user attempting to join is already a member of the session */
	AlreadyInSession UMETA(DisplayName = "AlreadyIn", ToolTip = "Already in session"),
	/** An error not covered above occurred */
	UnknownError UMETA(DisplayName = "UnknownError")
};

