#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightVoiceSelection.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoicePreviewComplete, bool, bSuccess);

UCLASS(Blueprintable)
class ULesFightVoiceSelection : public UObject
{
    GENERATED_BODY()

public:
    ULesFightVoiceSelection();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void SetVoicePack(EVoicePack Pack);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    EVoicePack GetVoicePack() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void SetPitch(float Pitch);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    float GetPitch() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void SetTone(float Tone);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    float GetTone() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void PreviewVoice();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void PreviewTaunt(int32 TauntIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void StopPreview();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void SetData(const FVoiceSelectionData& Data);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    FVoiceSelectionData GetData() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    TArray<EVoicePack> GetAvailableVoicePacks() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void SetVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    float GetVolume() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Voice")
    void ResetToDefault();

    UPROPERTY(BlueprintAssignable, Category = "CharacterCreator|Voice")
    FOnVoicePreviewComplete OnVoicePreviewComplete;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FVoiceSelectionData CurrentVoiceData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<EVoicePack> UnlockedVoicePacks;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float DefaultVolume;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MinPitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxPitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MinTone;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxTone;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
