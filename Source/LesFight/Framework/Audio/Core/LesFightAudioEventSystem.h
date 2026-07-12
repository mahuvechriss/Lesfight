#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioEventSystem.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightAudioEventSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Events")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Events")
    void FireEvent(FName EventName, AActor* Instigator, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Audio|Events")
    void RegisterEventListener(FName EventName, FName ListenerID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Events")
    void UnregisterEventListener(FName ListenerID);

    UFUNCTION(BlueprintPure, Category = "Audio|Events")
    TArray<FAudioEventData> GetRecentEvents(int32 Count) const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Events")
    void ClearEventHistory();

    UFUNCTION(BlueprintPure, Category = "Audio|Events")
    int32 GetEventCount() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Events")
    void SetEventCooldown(FName EventName, float Cooldown);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Events")
    TArray<FAudioEventData> EventHistory;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Events")
    TMap<FName, TArray<FName>> EventListeners;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Events")
    TMap<FName, float> EventCooldowns;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Events")
    TMap<FName, float> LastEventTimes;

private:
    static constexpr int32 MaxEventHistory = 200;

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
