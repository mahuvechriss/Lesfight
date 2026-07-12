#include "LesFightSessionManager.h"
#include "LesFight.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Engine/World.h"

ULesFightSessionManager::ULesFightSessionManager()
    : SessionState(ENetworkSessionState::None)
    , bIsHosting(false)
    , SearchTimeout(5.0f)
    , MaxSearchResults(32)
{
}

void ULesFightSessionManager::Initialize()
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        SessionInterface = OnlineSub->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
                FOnCreateSessionCompleteDelegate::CreateUObject(this, &ULesFightSessionManager::OnCreateSessionComplete));
            OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
                FOnFindSessionsCompleteDelegate::CreateUObject(this, &ULesFightSessionManager::OnFindSessionsComplete));
            OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
                FOnJoinSessionCompleteDelegate::CreateUObject(this, &ULesFightSessionManager::OnJoinSessionComplete));
            OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(
                FOnDestroySessionCompleteDelegate::CreateUObject(this, &ULesFightSessionManager::OnDestroySessionComplete));
        }
    }
    UE_LOG(LogLesFightNetwork, Log, TEXT("SessionManager initialized"));
}

bool ULesFightSessionManager::HostSession(const FString& SessionName, int32 MaxPlayers, bool bIsLAN)
{
    if (!SessionInterface.IsValid()) return false;

    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (!OnlineSub) return false;

    FOnlineSessionSettings SessionSettings;
    SessionSettings.bIsLANMatch = bIsLAN;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.bUsesPresence = true;
    SessionSettings.bAllowJoinInProgress = false;
    SessionSettings.bAllowJoinViaPresence = true;
    SessionSettings.bUseLobbiesIfAvailable = true;
    SessionSettings.NumPublicConnections = MaxPlayers;
    SessionSettings.bAllowInvites = false;

    SessionSettings.Set(FName(TEXT("SESSION_NAME")), SessionName,
        EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    CurrentSessionName = SessionName;
    bIsHosting = true;
    SessionState = ENetworkSessionState::Hosting;

    bool bResult = SessionInterface->CreateSession(0, FName(*SessionName), SessionSettings);
    return bResult;
}

bool ULesFightSessionManager::SearchForSessions(bool bIsLAN)
{
    if (!SessionInterface.IsValid()) return false;

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->bIsLanQuery = bIsLAN;
    SessionSearch->MaxSearchResults = MaxSearchResults;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

    SessionState = ENetworkSessionState::Searching;
    return SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

bool ULesFightSessionManager::JoinSession(int32 SessionIndex)
{
    if (!SessionInterface.IsValid() || !SessionSearch.IsValid()) return false;

    if (SessionIndex < 0 || SessionIndex >= FoundSessions.Num()) return false;

    SessionState = ENetworkSessionState::Joining;
    return SessionInterface->JoinSession(0, FName(*CurrentSessionName), SessionSearch->SearchResults[SessionIndex]);
}

bool ULesFightSessionManager::JoinSessionById(uint64 SessionId)
{
    for (int32 i = 0; i < FoundSessions.Num(); i++)
    {
        if (FoundSessions[i].SessionId == SessionId)
        {
            return JoinSession(i);
        }
    }
    return false;
}

bool ULesFightSessionManager::LeaveSession()
{
    if (!SessionInterface.IsValid()) return false;

    SessionState = ENetworkSessionState::None;
    return true;
}

bool ULesFightSessionManager::DestroySession()
{
    if (!SessionInterface.IsValid()) return false;

    SessionState = ENetworkSessionState::None;
    bIsHosting = false;
    return SessionInterface->DestroySession(FName(*CurrentSessionName));
}

bool ULesFightSessionManager::IsSessionValid() const
{
    if (!SessionInterface.IsValid()) return false;
    return SessionInterface->GetNamedSession(FName(*CurrentSessionName)) != nullptr;
}

void ULesFightSessionManager::SetSessionSettings(const FString& ServerName, const FString& MapName)
{
}

void ULesFightSessionManager::CleanupStaleSessions()
{
    if (!SessionInterface.IsValid()) return;

    TArray<FName> SessionNames;
    SessionInterface->GetSessionNames(SessionNames);
    for (const FName& Name : SessionNames)
    {
        SessionInterface->DestroySession(Name);
    }
}

void ULesFightSessionManager::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        SessionState = ENetworkSessionState::Connected;
        UE_LOG(LogLesFightNetwork, Log, TEXT("Session created: %s"), *SessionName.ToString());
    }
    else
    {
        SessionState = ENetworkSessionState::None;
        UE_LOG(LogLesFightNetwork, Warning, TEXT("Failed to create session"));
    }
    OnSessionCreated.Broadcast(bWasSuccessful);
}

void ULesFightSessionManager::OnFindSessionsComplete(bool bWasSuccessful)
{
    FoundSessions.Empty();

    if (bWasSuccessful && SessionSearch.IsValid())
    {
        for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
        {
            FLANSessionInfo Info;
            Info.SessionName = Result.Session.OwningUserName;
            Info.HostName = Result.Session.OwningUserName;
            Info.CurrentPlayers = Result.Session.SessionSettings.NumPublicConnections -
                Result.Session.NumOpenPublicConnections;
            Info.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
            Info.PingMs = Result.PingInMs;
            Info.SessionId = 0;

            FString FoundMapName;
            Result.Session.Settings.Get(FName(TEXT("MAP_NAME")), FoundMapName);
            Info.MapName = FoundMapName;

            FoundSessions.Add(Info);
        }
        UE_LOG(LogLesFightNetwork, Log, TEXT("Found %d sessions"), FoundSessions.Num());
    }

    SessionState = ENetworkSessionState::None;
    OnSessionsFound.Broadcast(FoundSessions);
}

void ULesFightSessionManager::OnJoinSessionComplete(FName SessionName,
    EOnJoinSessionCompleteResult::Type Result)
{
    if (Result == EOnJoinSessionCompleteResult::Success)
    {
        SessionState = ENetworkSessionState::Connected;
        UE_LOG(LogLesFightNetwork, Log, TEXT("Joined session: %s"), *SessionName.ToString());

        FString ConnectString;
        if (SessionInterface.IsValid() &&
            SessionInterface->GetResolvedConnectString(SessionName, ConnectString))
        {
            if (GetWorld())
            {
                GetWorld()->GetFirstPlayerController()->ClientTravel(ConnectString, TRAVEL_Absolute);
            }
        }
    }
    else
    {
        SessionState = ENetworkSessionState::None;
        UE_LOG(LogLesFightNetwork, Warning, TEXT("Failed to join session"));
    }
    OnSessionJoined.Broadcast(Result == EOnJoinSessionCompleteResult::Success);
}

void ULesFightSessionManager::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        SessionState = ENetworkSessionState::None;
        bIsHosting = false;
        UE_LOG(LogLesFightNetwork, Log, TEXT("Session destroyed: %s"), *SessionName.ToString());
    }
    OnSessionDestroyed.Broadcast();
}
