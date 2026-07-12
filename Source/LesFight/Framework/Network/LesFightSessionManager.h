#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightSessionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionsFound, const TArray<FLANSessionInfo>&, Sessions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionCreated, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionJoined, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionDestroyed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionError, FString, ErrorMessage);

UCLASS(Blueprintable)
class ULesFightSessionManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightSessionManager();

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool HostSession(const FString& SessionName, int32 MaxPlayers = 2, bool bIsLAN = true);

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool SearchForSessions(bool bIsLAN = true);

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool JoinSession(int32 SessionIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool JoinSessionById(uint64 SessionId);

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool LeaveSession();

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool DestroySession();

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    bool IsSessionValid() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    FString GetCurrentSessionName() const { return CurrentSessionName; }

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    ENetworkSessionState GetSessionState() const { return SessionState; }

    UFUNCTION(BlueprintPure, Category = "Network|Sessions")
    TArray<FLANSessionInfo> GetFoundSessions() const { return FoundSessions; }

    UFUNCTION(BlueprintPure, Category = "Network|Sessions")
    bool IsHosting() const { return bIsHosting; }

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    void SetSessionSettings(const FString& ServerName, const FString& MapName);

    UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
    void CleanupStaleSessions();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSessionsFound OnSessionsFound;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSessionCreated OnSessionCreated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSessionJoined OnSessionJoined;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSessionDestroyed OnSessionDestroyed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSessionError OnSessionError;

    UPROPERTY(BlueprintReadOnly, Category = "Network|Sessions")
    TArray<FLANSessionInfo> FoundSessions;

    UPROPERTY(BlueprintReadOnly, Category = "Network|Sessions")
    ENetworkSessionState SessionState;

    UPROPERTY(BlueprintReadOnly, Category = "Network|Sessions")
    FString CurrentSessionName;

    UPROPERTY(BlueprintReadOnly, Category = "Network|Sessions")
    bool bIsHosting;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network|Sessions")
    float SearchTimeout;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network|Sessions")
    int32 MaxSearchResults;

private:
    TWeakObjectPtr<class ULesFightMultiplayerManager> MultiplayerManager;
    TSharedPtr<class IOnlineSession> SessionInterface;
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;
    FDelegateHandle OnJoinSessionCompleteDelegateHandle;
    FDelegateHandle OnDestroySessionCompleteDelegateHandle;
    TSharedPtr<class FOnlineSessionSearch> SessionSearch;

    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
    void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
