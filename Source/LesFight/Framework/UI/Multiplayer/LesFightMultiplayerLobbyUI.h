#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"
#include "LesFightMultiplayerLobbyUI.generated.h"

DECLARE_DELEGATE_OneParam(FOnStartMatch, FName /*SessionName*/)
DECLARE_MULTICAST_DELEGATE(FOnLeaveLobby)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnArenaChanged, FText /*ArenaName*/)

USTRUCT(BlueprintType)
struct FLobbyPlayerEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    int32 PlayerIndex = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    FText PlayerName;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    UTexture2D* Avatar = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    TSoftObjectPtr<USkeletalMesh> FighterMesh;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    bool bReady = false;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    float Ping = 0.0f;
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMultiplayerLobbyUI : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void SetLocalPlayerInfo(FText PlayerName, UTexture2D* Avatar, class USkeletalMesh* FighterMesh);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void AddRemotePlayer(int32 PlayerIndex, FText PlayerName, UTexture2D* Avatar, bool bReady, float Ping);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void RemoveRemotePlayer(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void UpdatePlayerReady(int32 PlayerIndex, bool bReady);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void UpdatePlayerPing(int32 PlayerIndex, float PingMs);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void SetArenaSelection(FText ArenaName, UTexture2D* ArenaPreview);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void SetMatchRules(int32 RoundCount, float RoundDuration, bool bStageHazards);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void SetLobbyStatus(FText Status);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lobby")
    void StartMatchCountdown(int32 Seconds);
    virtual void StartMatchCountdown_Implementation(int32 Seconds);

    FOnStartMatch OnStartMatch;
    FOnLeaveLobby OnLeaveLobby;
    FOnArenaChanged OnArenaChanged;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    TArray<FLobbyPlayerEntry> Players;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    FText LocalPlayerName;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    float LocalPing = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    FText CurrentArenaName;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    int32 RoundLimit = 3;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    int32 RoundTimeLimit = 99;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    bool bStageHazardsEnabled = false;

    UPROPERTY(BlueprintReadOnly, Category = "Lobby")
    UTexture2D* ArenaPreview = nullptr;
};
