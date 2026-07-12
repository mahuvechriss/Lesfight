#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightSkinSystem.generated.h"

UCLASS(Blueprintable)
class ULesFightSkinSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightSkinSystem();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void SetSkinTone(FLinearColor Tone);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    FLinearColor GetSkinTone() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void SetSkinDetail(ESkinDetail Detail);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    ESkinDetail GetSkinDetail() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void SetGlossiness(float Gloss);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    float GetGlossiness() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void AddTattoo(const FTattooEntry& Tattoo);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    bool RemoveTattoo(const FName& TattooID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    TArray<FTattooEntry> GetAllTattoos() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void ClearTattoos();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void SetScarification(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    float GetScarification() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void SetCustomizationData(const FSkinCustomizationData& Data);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    FSkinCustomizationData GetCustomizationData() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Skin")
    void ResetToDefault();

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Skin")
    TArray<FLinearColor> GetPresetSkinTones() const { return PresetSkinTones; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FSkinCustomizationData CurrentSkinData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FLinearColor> PresetSkinTones;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxTattoos;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    TArray<FTattooEntry> Tattoos;
};
