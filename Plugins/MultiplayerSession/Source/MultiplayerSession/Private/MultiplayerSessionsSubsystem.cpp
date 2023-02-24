// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem():
CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this,&UMultiplayerSessionsSubsystem::OnCreateSessionComplete)),
FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this,&UMultiplayerSessionsSubsystem::OnFindSessionsComplete)),
JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this,&UMultiplayerSessionsSubsystem::OnJoinSessionComplete)),
DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this,&UMultiplayerSessionsSubsystem::OnDestroySessionComplete)),
StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this,&UMultiplayerSessionsSubsystem::OnStartSessionComplete))
{
	const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
		PTRSessionInterface = Subsystem->GetSessionInterface();
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	checkf(Subsystem != nullptr, TEXT("Unable to get the SubSytem"));

	PTRSessionInterface = Subsystem->GetSessionInterface();
	if(!ensureMsgf(PTRSessionInterface.IsValid(), TEXT("Unable to get the Session Interface"))) return;
}

void UMultiplayerSessionsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UMultiplayerSessionsSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType, const FString& SessionName, const bool bIsPrivate, const FString& SessionPassword)
{
	if(!ensureMsgf(PTRSessionInterface.IsValid(), TEXT("Unable to get the Session Interface")))return;
	
	const auto ExistingSession = PTRSessionInterface->GetNamedSession(NAME_GameSession);
	if(ExistingSession!=nullptr)
	{
		bCreateSessionOnDestroy=true;
		LastNumPublicConnections = NumPublicConnections;
		LastMatchType = MatchType;
		LastSessionName = SessionName;
		LastSessionPassword = SessionPassword;
		bIsLastSessionPrivate = bIsPrivate;
		
		DestroySession();
		return;
	}
		

	CreateSessionCompleteDelegateHandle = PTRSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName()=="NULL" ? true : false;
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	
#if !UE_BUILD_SHIPPING
	//Enforce a specific Build ID in not shipping so we can
	//easily test session creation
	LastSessionSettings->BuildUniqueId = 1;
#endif
	
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->Set(FName("MatchType"),MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	LastSessionSettings->Set(FName("SessionName"),SessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	LastSessionSettings->Set(FName("SessionPassword"),SessionPassword, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	LastSessionSettings->Set(FName("IsPrivate"),bIsPrivate, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if(!PTRSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		PTRSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		//Broadcast my own custom delegate
		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}
}

void UMultiplayerSessionsSubsystem::FindSessions(int32 MaxSearchResults, const FString& MatchType)
{
	if(!ensureMsgf(PTRSessionInterface.IsValid(), TEXT("Unable to get the Session Interface")))return;

	FindSessionsCompleteDelegateHandle = PTRSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);

	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName()=="NULL" ? true : false;
	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	LastSessionSearch->QuerySettings.Set(FName("MatchType"), MatchType, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if(!PTRSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		PTRSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

		MultiplayerOnFindSessionsComplete.Broadcast(TArray<FMultiplayerSessionSearchResult>(), false);
	}
}

void UMultiplayerSessionsSubsystem::JoinSession(const FMultiplayerSessionSearchResult& SessionResult)
{
	if(!ensureMsgf(PTRSessionInterface.IsValid(), TEXT("Unable to get the Session Interface")))return;
	
	JoinSessionCompleteDelegateHandle = PTRSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if(!PTRSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult.Native))
	{
		PTRSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

		MultiplayerOnJoinSessionComplete.Broadcast(false, UnknownError,"");
	}
}

void UMultiplayerSessionsSubsystem::DestroySession()
{
	if(!ensureMsgf(PTRSessionInterface.IsValid(), TEXT("Unable to get the Session Interface")))return;

	DestroySessionCompleteDelegateHandle = PTRSessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);

	if(PTRSessionInterface->GetNamedSession(NAME_GameSession)!=nullptr)
	{
		PTRSessionInterface->DestroySession(NAME_GameSession);
	}
	else
	{
		PTRSessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
		MultiplayerOnDestroySessionComplete.Broadcast(false);
	}
}

void UMultiplayerSessionsSubsystem::StartSession()
{
	if(!ensureMsgf(PTRSessionInterface.IsValid(), TEXT("Unable to get the Session Interface")))return;

	StartSessionCompleteDelegateHandle = PTRSessionInterface->AddOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegate);

	if(!PTRSessionInterface->StartSession(NAME_GameSession))
	{
		PTRSessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);
		MultiplayerOnStartSessionComplete.Broadcast(false);
	}
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if(PTRSessionInterface)
		PTRSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	MultiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	if(PTRSessionInterface)
		PTRSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

	if(!LastSessionSearch.IsValid() || LastSessionSearch->SearchResults.Num()<=0)
	{
		MultiplayerOnFindSessionsComplete.Broadcast(TArray<FMultiplayerSessionSearchResult>(), false);
		return;
	}

	TArray<FMultiplayerSessionSearchResult> Results;
	Results.Reserve(LastSessionSearch->SearchResults.Num());
	for (const auto& result : LastSessionSearch->SearchResults)
	{
		FMultiplayerSessionSearchResult r{};
		r.Native = result;
		r.Session = result.Session;
		r.PingInMs = result.PingInMs;
		Results.Add(r);
	}
	MultiplayerOnFindSessionsComplete.Broadcast(Results, bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if(PTRSessionInterface)
		PTRSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	else
		MultiplayerOnJoinSessionComplete.Broadcast(Result==EOnJoinSessionCompleteResult::Type::Success,UnknownError,"");

	EJoinSessionResultType ResultBP = UnknownError;
	switch (Result)
	{
	case EOnJoinSessionCompleteResult::Success:
		ResultBP = Success;
		break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		ResultBP = SessionIsFull;
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		ResultBP = SessionDoesNotExist;
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		ResultBP = CouldNotRetrieveAddress;
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		ResultBP = AlreadyInSession;
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		ResultBP = UnknownError;
		break;
	}
	FString Address;
	PTRSessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

	
	MultiplayerOnJoinSessionComplete.Broadcast(Result == EOnJoinSessionCompleteResult::Type::Success,ResultBP,Address);
	
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if(PTRSessionInterface)
		PTRSessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
	MultiplayerOnDestroySessionComplete.Broadcast(bWasSuccessful);
	
	if(!bWasSuccessful || !bCreateSessionOnDestroy)return;
	
	CreateSession(LastNumPublicConnections,LastMatchType,LastSessionName,bIsLastSessionPrivate,LastSessionPassword);
		
}

void UMultiplayerSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if(PTRSessionInterface)
		PTRSessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);

	MultiplayerOnStartSessionComplete.Broadcast(bWasSuccessful);
}

void UMultiplayerSessionsSubsystem::GetSessionInformations(const FMultiplayerSessionSearchResult& Session,
	int32& SessionPing, int32& NumberOfConnectedPlayers, int32& MaxConnectedPlayer, FString& SessionName,
	FString& SessionPassword, bool& bIsSessionPrivate)
{
	SessionPing = Session.PingInMs;
	MaxConnectedPlayer = Session.Session.SessionSettings.NumPublicConnections;
	Session.Session.SessionSettings.Get(FName("SessionName"), SessionName);
	NumberOfConnectedPlayers = MaxConnectedPlayer - Session.Session.NumOpenPublicConnections;
	Session.Session.SessionSettings.Get(FName("SessionPassword"),SessionPassword);
	Session.Session.SessionSettings.Get(FName("IsPrivate"),bIsSessionPrivate);
}