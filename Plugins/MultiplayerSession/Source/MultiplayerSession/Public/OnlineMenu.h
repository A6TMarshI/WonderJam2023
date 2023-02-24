// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JoinSessionResultType.h"
#include "Blueprint/UserWidget.h"
#include "OnlineMenu.generated.h"

/**
 * 
 */
struct FMultiplayerSessionSearchResult;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessionMenuCreationComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSessionMenuSearchComplete, bool, bWasSuccessful, const TArray<FMultiplayerSessionSearchResult>&, SearchResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSessionMenuJoinComplete, bool, bWasSuccessful, EJoinSessionResultType, Type);
UCLASS()
class MULTIPLAYERSESSION_API UOnlineMenu : public UUserWidget
{
	
private:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void MenuSetup();

protected:
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void HostSession(const TSoftObjectPtr<UWorld> Lobby, int32 NumPublicConnection = 4, const FString& MatchType = "FreeForAll", const FString& ServerName="", const bool IsPrivate=false, const FString& ServerPassword="");

	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void FindSessions(int32 MaxSessionNumber = 10, const FString& MatchType = "FreeForAll");
	
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void JoinSession(const FMultiplayerSessionSearchResult& Session);

	virtual void NativeDestruct() override;
	/*---Callbacks for the custom delegates one the MultiplayerSessionSubsystem---*/
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
	UFUNCTION()
	void OnFindSessions(const TArray<FMultiplayerSessionSearchResult>& SessionResults, bool bWasSuccessful);
	
	UFUNCTION()
	void OnJoinSession(bool bWasSuccessful, EJoinSessionResultType Type, const FString& Address);

	/*Delegate for blueprints usage*/
	UPROPERTY(BlueprintAssignable)
	FSessionMenuCreationComplete OnSessionCreateComplete;
	
	UPROPERTY(BlueprintAssignable)
	FSessionMenuSearchComplete OnSessionSearchComplete;
	
	UPROPERTY(BlueprintAssignable)
	FSessionMenuJoinComplete OnSessionJoinComplete;
	
private:
	void MenuTearDown();
	
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	FString PathToLobby;
    
};
