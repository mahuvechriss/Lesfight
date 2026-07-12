#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightEventCoordinationSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSequenceEvent, ECoordinationEvent, Event, UObject*, Context);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventTriggered, ECoordinationEvent, Event, UObject*, Context);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightEventCoordinationSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void PlaySequence(FName SequenceName);

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void RegisterSequence(FName SequenceName, const FCoordinationSequence& Sequence);

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void UnregisterSequence(FName SequenceName);

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void RegisterSequenceCallback(FName SequenceName, ECoordinationEvent Event, FOnSequenceEvent Callback);

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void StartCoordinationEvent(ECoordinationEvent Event, UObject* Context);

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    FName GetActiveSequence() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    bool IsSequencePlaying() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    TArray<FName> GetAvailableSequences() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void PauseSequence();

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void ResumeSequence();

    UFUNCTION(BlueprintCallable, Category = "Integration|EventCoordination")
    void StopSequence();

    UPROPERTY(BlueprintAssignable, Category = "Integration|EventCoordination")
    FOnEventTriggered OnEventTriggered;

protected:
    UPROPERTY()
    TMap<FName, FCoordinationSequence> SequenceRegistry;

    UPROPERTY()
    TMap<FName, TMap<ECoordinationEvent, FOnSequenceEvent>> SequenceCallbacks;

    UPROPERTY()
    FName ActiveSequence;

    UPROPERTY()
    TArray<ECoordinationEvent> PendingEvents;

    UPROPERTY()
    int32 CurrentEventIndex;

    UPROPERTY()
    bool bSequencePlaying;

    UPROPERTY()
    bool bPaused;

    UPROPERTY()
    float SequenceTimer;
};
