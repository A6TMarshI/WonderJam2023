// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineMenu.h"

#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"


void UOnlineMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	if(const UWorld* World = GetWorld())
	{
		if(APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
	
	if(const UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();

		checkf(MultiplayerSessionsSubsystem != nullptr, TEXT("Multiplayer Session Subsystem cannot be found"));
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddDynamic(this, &ThisClass::OnFindSessions);
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddDynamic(this, &ThisClass::OnJoinSession);
	}
}

void UOnlineMenu::HostSession(const TSoftObjectPtr<UWorld> Lobby, int32 NumPublicConnection, const FString& MatchType, const FString& ServerName, const bool bIsPrivate, const FString& ServerPassword)
{
	if(!ensureMsgf(MultiplayerSessionsSubsystem != nullptr,TEXT("Multiplayer Session Subsystem is null. Must call MenuSetup"))) return;

	Lobby.ToSoftObjectPath().ToString().Split(FString("."),&PathToLobby,nullptr);
	MultiplayerSessionsSubsystem->CreateSession(NumPublicConnection, MatchType,ServerName,bIsPrivate,ServerPassword);
}

void UOnlineMenu::FindSessions(int32 MaxSessionNumber, const FString& MatchType)
{
	if(!ensureMsgf(MultiplayerSessionsSubsystem != nullptr,TEXT("Multiplayer Session Subsystem is null. Must call MenuSetup"))) return;
	MultiplayerSessionsSubsystem->FindSessions(MaxSessionNumber, MatchType);
}

void UOnlineMenu::JoinSession(const FMultiplayerSessionSearchResult& Session)
{
	if(!ensureMsgf(MultiplayerSessionsSubsystem != nullptr,TEXT("Multiplayer Session Subsystem is null. Must call MenuSetup"))) return;
	MultiplayerSessionsSubsystem->JoinSession(Session);
}

void UOnlineMenu::NativeDestruct()
{
	Super::NativeDestruct();
	MenuTearDown();
}

void UOnlineMenu::OnCreateSession(bool bWasSuccessful)
{
	OnSessionCreateComplete.Broadcast(bWasSuccessful);
	if(!bWasSuccessful)return;
	
		if(UWorld* World = GetWorld())
		{
			World->ServerTravel(PathToLobby.Append("?listen"));
		}
}

void UOnlineMenu::OnFindSessions(const TArray<FMultiplayerSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	OnSessionSearchComplete.Broadcast(bWasSuccessful, SessionResults);
}

void UOnlineMenu::OnJoinSession(bool bWasSuccessful, EJoinSessionResultType Type, const FString& Address)
{
	OnSessionJoinComplete.Broadcast(bWasSuccessful,Type);
	
	if(const auto* World = GetWorld())
	{
		if(APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeGameOnly InputModeData;
			PlayerController->ClientTravel(Address, TRAVEL_Absolute);
		}
	}
}

void UOnlineMenu::MenuTearDown()
{
	RemoveFromParent();
	
	if(const UWorld* World = GetWorld())
	{
		if(APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			const FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
	MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.RemoveDynamic(this, &ThisClass::OnCreateSession);
	MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.RemoveDynamic(this, &ThisClass::OnFindSessions);
	MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.RemoveDynamic(this, &ThisClass::OnJoinSession);
}
