#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightLagCompensation.generated.h"

USTRUCT()
struct FPositionSnapshot
{
    GENERATED_BODY()

    FVector Position;
    FRotator Rotation;
    float Timestamp;
    int32 SequenceNumber;

    FPositionSnapshot()
        : Position(FVector::ZeroVector)
        , Rotation(FRotator::ZeroRotator)
        , Timestamp(0.0f)
        , SequenceNumber(0)
    {}
};

USTRUCT()
struct FFrameHistoryEntry
{
    GENERATED_BODY()

    int32 FrameNumber;
    float Timestamp;
    TArray<FPositionSnapshot> Snapshots;

    FFrameHistoryEntry()
        : FrameNumber(0)
        , Timestamp(0.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightLagCompensation : public UObject
{
    GENERATED_BODY()

public:
    ULesFightLagCompensation();

    void Initialize(ULesFightMultiplayerManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    void RecordSnapshot(int32 PlayerIndex, FVector Position, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    bool RewindToTimestamp(float TargetTimestamp, int32 TargetPlayerIndex,
        FVector& OutPosition, FRotator& OutRotation);

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    bool ValidateHitAtTime(int32 AttackerIndex, int32 DefenderIndex,
        float HitTimestamp, float HitboxRadius);

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    void ClearHistory();

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    void SetHistoryDuration(float Seconds);

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    void SetEnabled(bool bInEnabled);

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    bool IsEnabled() const { return bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    int32 GetHistorySize() const { return FrameHistory.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Network|LagCompensation")
    void SetMaxHistoryFrames(int32 MaxFrames);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float HistoryDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxHistoryFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float RewindTolerance;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FFrameHistoryEntry> FrameHistory;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    TMap<int32, TArray<FPositionSnapshot>> PlayerSnapshots;
    int32 CurrentSequenceNumber;

    void PruneOldHistory();
};
