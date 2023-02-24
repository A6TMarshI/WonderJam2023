// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerSessionSearchResult.h"
#include "JoinSessionResultType.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerSessionsSubsystem.generated.h"


/*---Declare my own custom delegates for the menu class to bind callbacks ---*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FMultiplayerSessionSearchResult>&, SessionResults, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMultiplayerOnJoinSessionComplete, bool, bWasSuccessful, EJoinSessionResultType, Type, const FString&, Address);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/*---To handle session functionnality. The menu class will use these---*/
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void CreateSession(int32 NumPublicConnections, FString MatchType, const FString& SessionName, const bool bIsPrivate, const FString& SessionPassword);
	
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void FindSessions(int32 MaxSearchResults, const FString& MatchType);
	
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void JoinSession(const FMultiplayerSessionSearchResult& SessionResult);
	
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void DestroySession();
	
	UFUNCTION(BlueprintCallable, Category="OnlineOptions")
	void StartSession();

	/*---My own custom delegate for the menu class to bind callbacks to---*/
	UPROPERTY(BlueprintAssignable)
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	
	UPROPERTY(BlueprintAssignable)
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	
	UPROPERTY(BlueprintAssignable)
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	
	UPROPERTY(BlueprintAssignable)
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	
	UPROPERTY(BlueprintAssignable)
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;
	
protected:
	/*---Internal callback for delegates added to the online session interface delegate list---*/
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);


	/*Get Online Session Info. Used to display many lobbies within UI*/
	UFUNCTION(BlueprintCallable)
	void GetSessionInformations(const FMultiplayerSessionSearchResult& Session, int32& SessionPing, int32& NumberOfConnectedPlayers, int32& MaxConnectedPlayer, FString& SessionName, FString& SessionPassword, bool& bIsSessionPrivate);
	
private:
	IOnlineSessionPtr PTRSessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	/*--To add to the online session interface delegate list---*/
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	bool bCreateSessionOnDestroy{false};
	int32 LastNumPublicConnections;
	FString LastMatchType;
	FString LastSessionName;
	FString LastSessionPassword;
	bool bIsLastSessionPrivate;
	
	
};
