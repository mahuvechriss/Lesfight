#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightVFXEventSystem.generated.h"

class ULesFightVFXWorldManager;

USTRUCT(BlueprintType)
struct FVFXEventEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY()
    TWeakObjectPtr<AActor> Instigator;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Timestamp;
};

UCLASS(Blueprintable)
class ULesFightVFXEventSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightVFXEventSystem();

    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void FireVFXEvent(FName EventName, FVector Location, AActor* Instigator);

    UFUNCTION(BlueprintCallable)
    void RegisterVFXEventListener(FName EventName, FName ListenerID);

    UFUNCTION(BlueprintCallable)
    void UnregisterVFXEventListener(FName ListenerID);

    UFUNCTION(BlueprintCallable)
    TArray<FVFXEventEntry> GetRecentVFXEvents(int32 Count) const;

    UFUNCTION(BlueprintCallable)
    void ClearEventHistory();

    UFUNCTION(BlueprintCallable)
    void SetEventCooldown(FName EventName, float Cooldown);

protected:
    UPROPERTY()
    TArray<FVFXEventEntry> EventHistory;

    UPROPERTY()
    TMap<FName, TArray<FName>> EventListeners;

    UPROPERTY()
    TMap<FName, float> EventCooldowns;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 MaxEventHistory = 200;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;
};
