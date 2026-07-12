#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightCharacterVoiceSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharacterVoiceSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void AssignVoicePack(FName CharacterID, FName VoicePackName);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void PlayCharacterTaunt(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void PlayCharacterPain(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void PlayCharacterVictory(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void PlayCharacterDefeat(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void PlayCharacterUltimateCall(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    void PlayCharacterEntrance(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    FCharacterVoicePack GetCharacterVoicePack(FName CharacterID) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterVoice")
    float GetCharacterPitch(FName CharacterID) const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "CharacterVoice")
    TMap<FName, FName> CharacterVoiceAssignments;

    UPROPERTY(BlueprintReadWrite, Category = "CharacterVoice")
    TMap<FName, float> CharacterPitches;

    UPROPERTY(BlueprintReadWrite, Category = "CharacterVoice")
    TMap<FName, FCharacterVoicePack> CachedPacks;

private:
    TWeakObjectPtr<class ULesFightAudioWorldManager> OwnerManager;
};
