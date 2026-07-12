#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightJoinGameUI.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameJoined, FName /*SessionID*/)
DECLARE_MULTICAST_DELEGATE(FOnJoinCancelled)
DECLARE_MULTICAST_DELEGATE(FOnSearchStarted)
DECLARE_MULTICAST_DELEGATE(FOnSearchComplete)

USTRUCT(BlueprintType)
struct FGameSessionEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    FName SessionID;

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    FText SessionName;

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    int32 PlayerCount = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    int32 MaxPlayers = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Session")
    float Ping = 0.0f;
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightJoinGameUI : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void AddGameSession(FName SessionID, FText SessionName, int32 PlayerCount, int32 MaxPlayers, float Ping);

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void RemoveGameSession(FName SessionID);

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void ClearGameSessions();

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void SelectSession(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    FName GetSelectedSession() const;

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void SearchForGames();

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void RefreshList();

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void StopSearch();

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void SetSearchStatus(FText Status, bool bSearching);

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void JoinSelectedGame();

    UFUNCTION(BlueprintCallable, Category = "JoinGame")
    void CancelJoin();

    FOnGameJoined OnGameJoined;
    FOnJoinCancelled OnJoinCancelled;
    FOnSearchStarted OnSearchStarted;
    FOnSearchComplete OnSearchComplete;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "JoinGame")
    TArray<FGameSessionEntry> AvailableSessions;

    UPROPERTY(BlueprintReadOnly, Category = "JoinGame")
    int32 SelectedIndex = -1;

    UPROPERTY(BlueprintReadOnly, Category = "JoinGame")
    FName SelectedSessionID;

    UPROPERTY(BlueprintReadOnly, Category = "JoinGame")
    bool bSearching = false;
};
