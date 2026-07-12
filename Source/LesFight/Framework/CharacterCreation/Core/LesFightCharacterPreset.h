#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterPreset.generated.h"

UCLASS(Blueprintable)
class ULesFightCharacterPreset : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterPreset();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    bool ExportPreset(const FCharacterCustomizationPreset& Preset, const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    FCharacterCustomizationPreset ImportPreset(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    bool SavePresetToSlot(const FCharacterCustomizationPreset& Preset, int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    FCharacterCustomizationPreset LoadPresetFromSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    TArray<int32> GetOccupiedPresetSlots() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    int32 GetMaxPresetSlots() const { return MaxPresetSlots; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    bool DeletePresetFromSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Presets")
    FString GetPresetFilePath(int32 SlotIndex) const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxPresetSlots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    FString PresetDirectory;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    TMap<int32, FCharacterCustomizationPreset> CachedPresets;

    FString GetPresetSlotPath(int32 SlotIndex) const;
    FString GetPresetExtension() const { return TEXT(".lfpreset"); }
};
