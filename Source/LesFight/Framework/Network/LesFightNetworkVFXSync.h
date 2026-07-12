#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkVFXSync.generated.h"

USTRUCT(BlueprintType)
struct FNetworkVFXEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName EffectID;

    UPROPERTY(BlueprintReadOnly)
    FVector Location;

    UPROPERTY(BlueprintReadOnly)
    FRotator Rotation;

    UPROPERTY(BlueprintReadOnly)
    FVector Scale;

    UPROPERTY(BlueprintReadOnly)
    int32 PlayerIndex;

    UPROPERTY(BlueprintReadOnly)
    float Timestamp;

    UPROPERTY(BlueprintReadOnly)
    float Duration;

    UPROPERTY(BlueprintReadOnly)
    bool bAttachedToPlayer;

    FNetworkVFXEvent()
        : EffectID(NAME_None)
        , Location(FVector::ZeroVector)
        , Rotation(FRotator::ZeroRotator)
        , Scale(FVector::OneVector)
        , PlayerIndex(-1)
        , Timestamp(0.0f)
        , Duration(1.0f)
        , bAttachedToPlayer(false)
    {}
};

UCLASS(Blueprintable)
class ULesFightNetworkVFXSync : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkVFXSync();

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    void PlaySyncedEffect(FName EffectID, FVector Location, FRotator Rotation = FRotator::ZeroRotator,
        float Duration = 1.0f, bool bAttachedToPlayer = false);

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    void PlaySyncedEffectForPlayer(int32 PlayerIndex, FName EffectID,
        FVector Location, FRotator Rotation = FRotator::ZeroRotator);

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    void StopSyncedEffect(FName EffectID);

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    void ClearAllEffects();

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    void SetEnabled(bool bInEnabled) { bEnabled = bInEnabled; }

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    int32 GetActiveEffectCount() const { return ActiveEffects.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Network|VFX")
    int32 GetPendingEffectCount() const { return PendingVFXEvents.Num(); }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FNetworkVFXEvent> PendingVFXEvents;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FNetworkVFXEvent> ActiveEffects;

private:
    void BroadcastVFXEvent(const FNetworkVFXEvent& Event);
};
