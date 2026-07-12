#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "LesFightNetworkData.generated.h"

UENUM(BlueprintType)
enum class ENetworkSessionState : uint8
{
    None,
    Hosting,
    Searching,
    Joining,
    Connected,
    InLobby,
    InMatch,
    Disconnected,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ENetworkMatchState : uint8
{
    None,
    WaitingForPlayers,
    CharacterSelect,
    Countdown,
    RoundInProgress,
    RoundEnd,
    MatchEnd,
    ReturningToLobby,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ENetworkPlayerRole : uint8
{
    None,
    Host,
    Client,
    Spectator,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ENetworkReadyState : uint8
{
    NotReady,
    Ready,
    Loading,
    Loaded,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConnectionQuality : uint8
{
    Excellent,
    Good,
    Fair,
    Poor,
    Lost,
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FLANSessionInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString SessionName;

    UPROPERTY(BlueprintReadOnly)
    FString HostName;

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentPlayers;

    UPROPERTY(BlueprintReadOnly)
    int32 MaxPlayers;

    UPROPERTY(BlueprintReadOnly)
    int32 PingMs;

    UPROPERTY(BlueprintReadOnly)
    FString MapName;

    UPROPERTY(BlueprintReadOnly)
    uint64 SessionId;

    UPROPERTY(BlueprintReadOnly)
    bool bHasPassword;

    FLANSessionInfo()
        : SessionName(TEXT("")), HostName(TEXT(""))
        , CurrentPlayers(0), MaxPlayers(2)
        , PingMs(0), MapName(TEXT(""))
        , SessionId(0), bHasPassword(false)
    {}
};

USTRUCT(BlueprintType)
struct FNetworkPlayerInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString PlayerName;

    UPROPERTY(BlueprintReadOnly)
    int32 PlayerIndex;

    UPROPERTY(BlueprintReadOnly)
    ENetworkPlayerRole Role;

    UPROPERTY(BlueprintReadOnly)
    ENetworkReadyState ReadyState;

    UPROPERTY(BlueprintReadOnly)
    int32 PingMs;

    UPROPERTY(BlueprintReadOnly)
    bool bIsConnected;

    UPROPERTY(BlueprintReadOnly)
    FName CharacterID;

    FNetworkPlayerInfo()
        : PlayerName(TEXT("")), PlayerIndex(-1)
        , Role(ENetworkPlayerRole::None)
        , ReadyState(ENetworkReadyState::NotReady)
        , PingMs(0), bIsConnected(false)
        , CharacterID(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FNetworkMatchData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString MatchID;

    UPROPERTY(BlueprintReadOnly)
    int32 RoundNumber;

    UPROPERTY(BlueprintReadOnly)
    int32 MaxRounds;

    UPROPERTY(BlueprintReadOnly)
    float RoundTimeLimit;

    UPROPERTY(BlueprintReadOnly)
    float RoundTimeRemaining;

    UPROPERTY(BlueprintReadOnly)
    ENetworkMatchState MatchState;

    UPROPERTY(BlueprintReadOnly)
    TArray<FNetworkPlayerInfo> Players;

    FNetworkMatchData()
        : MatchID(TEXT("")), RoundNumber(1), MaxRounds(3)
        , RoundTimeLimit(99.0f), RoundTimeRemaining(99.0f)
        , MatchState(ENetworkMatchState::None)
    {}
};

USTRUCT(BlueprintType)
struct FNetworkCombatAction
{
    GENERATED_BODY()

    UPROPERTY()
    FName ActionID;

    UPROPERTY()
    int32 ActionIndex;

    UPROPERTY()
    float Timestamp;

    UPROPERTY()
    uint32 SequenceNumber;

    UPROPERTY()
    bool bIsPredicting;

    FNetworkCombatAction()
        : ActionID(NAME_None), ActionIndex(0)
        , Timestamp(0.0f), SequenceNumber(0)
        , bIsPredicting(false)
    {}
};

USTRUCT(BlueprintType)
struct FNetworkAnimSyncData
{
    GENERATED_BODY()

    UPROPERTY()
    FName CurrentState;

    UPROPERTY()
    float StatePlayTime;

    UPROPERTY()
    float BlendWeight;

    UPROPERTY()
    bool bIsPlayingMontage;

    UPROPERTY()
    FName MontageName;

    UPROPERTY()
    float MontagePosition;

    FNetworkAnimSyncData()
        : CurrentState(NAME_None), StatePlayTime(0.0f)
        , BlendWeight(1.0f), bIsPlayingMontage(false)
        , MontageName(NAME_None), MontagePosition(0.0f)
    {}
};

UCLASS(BlueprintType)
class ULesFightNetworkDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    int32 MaxPlayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    int32 MaxRounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    float RoundTimeLimit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    float ConnectionTimeout;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    float ReplicationRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    int32 MaxBandwidthKbps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    bool bEnableClientPrediction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    bool bEnableLagCompensation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
    float SyncInterval;

    ULesFightNetworkDataAsset()
        : MaxPlayers(2), MaxRounds(3), RoundTimeLimit(99.0f)
        , ConnectionTimeout(10.0f), ReplicationRate(60.0f)
        , MaxBandwidthKbps(256), bEnableClientPrediction(true)
        , bEnableLagCompensation(true), SyncInterval(0.033f)
    {}
};
