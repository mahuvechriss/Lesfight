#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightReverbZoneSystem.generated.h"

class ULesFightAudioWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReverbZoneEntered, FName, ZoneName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReverbZoneExited, FName, ZoneName);

UCLASS(Blueprintable)
class ULesFightReverbZoneSystem : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Reverb")
    FOnReverbZoneEntered OnReverbZoneEntered;

    UPROPERTY(BlueprintAssignable, Category = "Reverb")
    FOnReverbZoneExited OnReverbZoneExited;

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    void RegisterReverbZone(const FReverbZoneData& Zone);

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    void RemoveReverbZone(FName ZoneName);

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    void UpdateListenerReverb(FVector ListenerPosition);

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    FReverbZoneData GetCurrentReverbData() const;

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    EReverbPreset GetCurrentReverbPreset() const;

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    void SetGlobalReverb(EReverbPreset Preset);

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    void ClearAllZones();

    UFUNCTION(BlueprintCallable, Category = "Reverb")
    FReverbZoneData GetReverbZoneAtLocation(FVector Location) const;

protected:
    UPROPERTY()
    TArray<FReverbZoneData> ReverbZones;

    UPROPERTY()
    FReverbZoneData CurrentReverb;

    UPROPERTY()
    FName CurrentZoneName;

    UPROPERTY()
    bool bInZone = false;

    UPROPERTY()
    EReverbPreset GlobalReverb = EReverbPreset::None;

private:
    friend class ULesFightAudioWorldManager;

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
