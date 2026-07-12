#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIAudioHandler.generated.h"

class ALesFightAIFighterController;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIAudioHandler : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayVoiceLine(const FAIDecisionContext& Context);

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayHitSound();

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayMissSound();

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayBlockSound();

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayTaunt();

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayVictorySound();

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayDefeatSound();

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void PlayBreathSound(EAIAnimationEvent Event);

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void SetVoicePitch(float Pitch);

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void SetVoiceVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    bool IsSpeaking() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Audio")
    void SetMuted(bool bInMuted);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Audio")
    FString CurrentVoiceLine;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Audio")
    float VoicePitch = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Audio")
    float VoiceVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Audio")
    bool bMuted = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Audio")
    bool bSpeaking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Audio")
    TArray<FString> TauntLines;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Audio")
    TMap<EAIAnimationEvent, FString> VoiceReactions;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
};
