#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightVoiceManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVoiceLineStarted, FName, CharacterID, EVoiceContext, Context);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoiceLineComplete, FName, CharacterID);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightVoiceManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Voice")
    void PlayVoiceLine(EVoiceContext Context, FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Voice")
    void StopVoice();

    UFUNCTION(BlueprintCallable, Category = "Voice")
    bool IsSpeaking() const;

    UFUNCTION(BlueprintCallable, Category = "Voice")
    void SetVoicePitch(FName CharacterID, float Pitch);

    UFUNCTION(BlueprintCallable, Category = "Voice")
    void SetVoiceVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Voice")
    int32 GetActiveVoiceCount() const;

    UFUNCTION(BlueprintCallable, Category = "Voice")
    void PreloadVoicePack(FName PackName);

    UFUNCTION(BlueprintCallable, Category = "Voice")
    void ClearVoiceCache();

    UFUNCTION(BlueprintCallable, Category = "Voice")
    TArray<FName> GetAvailableVoicePacks() const;

    UPROPERTY(BlueprintAssignable, Category = "Voice")
    FOnVoiceLineStarted OnVoiceLineStarted;

    UPROPERTY(BlueprintAssignable, Category = "Voice")
    FOnVoiceLineComplete OnVoiceLineComplete;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Voice")
    TMap<FName, FCharacterVoicePack> VoicePacks;

    UPROPERTY(BlueprintReadWrite, Category = "Voice")
    TArray<FName> ActiveVoices;

    UPROPERTY(BlueprintReadWrite, Category = "Voice")
    int32 MaxConcurrentVoices = 4;

    UPROPERTY(BlueprintReadWrite, Category = "Voice")
    float GlobalVoiceVolume = 1.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Voice")
    TMap<FName, float> VoicePitches;

private:
    TWeakObjectPtr<class ULesFightAudioWorldManager> OwnerManager;
};
