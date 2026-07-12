#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioReplication.generated.h"

class ULesFightAudioWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioEventReplicated, FAudioEventData, EventData);

UCLASS(Blueprintable)
class ULesFightAudioReplication : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void ReplicateMusicState(EMusicState State);

    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void ReplicateCombatSound(ECombatSoundType Type, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void ReplicateVoiceLine(EVoiceContext Context, FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void ReplicateCinematicEvent(FString EventName);

    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void SetReplicationEnabled(bool bEnabled);

    UFUNCTION(BlueprintPure, Category = "Audio|Replication")
    bool IsReplicationEnabled() const;

    UFUNCTION(BlueprintPure, Category = "Audio|Replication")
    bool IsAudioDuplicate(FName EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Replication")
    void ProcessReplicatedEvents();

    UPROPERTY(BlueprintAssignable, Category = "Audio|Replication|Events")
    FOnAudioEventReplicated OnAudioEventReplicated;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Replication")
    bool bReplicationEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Replication")
    TArray<FAudioEventData> PendingAudioEvents;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Replication")
    TMap<FName, float> ReplicatedEventTimestamps;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Replication")
    float DuplicateWindow;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
