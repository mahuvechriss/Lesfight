#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAIVoiceSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIVoiceSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void InitializeForAI(EAIPersonalityType Personality);

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void PlayAITaunt();

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void PlayAIReaction(EAIAnimationEvent Event);

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void PlayAICombatCall();

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void PlayAIVictory();

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void PlayAIDefeat();

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    void SetAIAggression(float Aggression);

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    FName GetAIVoicePack() const;

    UFUNCTION(BlueprintCallable, Category = "AIVoice")
    bool WouldAISpeak() const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "AIVoice")
    EAIPersonalityType AIPersonality;

    UPROPERTY(BlueprintReadWrite, Category = "AIVoice")
    FName AIVoicePackName;

    UPROPERTY(BlueprintReadWrite, Category = "AIVoice")
    float Aggression;

    UPROPERTY(BlueprintReadWrite, Category = "AIVoice")
    float TauntFrequency = 0.3f;

    UPROPERTY(BlueprintReadWrite, Category = "AIVoice")
    TMap<EAIPersonalityType, FName> PersonalityVoicePacks;

    UPROPERTY(BlueprintReadWrite, Category = "AIVoice")
    TMap<EAIPersonalityType, TArray<FString>> PersonalityTaunts;

private:
    TWeakObjectPtr<class ULesFightAudioWorldManager> OwnerManager;
};
