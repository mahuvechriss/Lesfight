#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterSaveSystem.generated.h"

UCLASS(Blueprintable)
class ULesFightCharacterSaveSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterSaveSystem();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool SaveCharacter(FName CharacterID, const FCharacterCustomizationPreset& Data);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool LoadCharacter(FName CharacterID, FCharacterCustomizationPreset& OutData);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool DeleteCharacterSave(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool SaveAllCharacters(const TMap<FName, FCharacterCustomizationPreset>& Characters);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    TMap<FName, FCharacterCustomizationPreset> LoadAllCharacters();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    TArray<FName> GetSavedCharacterIDs();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool CharacterSaveExists(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool SaveToSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool LoadFromSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    void SetAutoSave(bool bAutoSave);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    bool IsAutoSaveEnabled() const { return bAutoSave; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Save")
    void AutoSave();

    UPROPERTY(BlueprintReadWrite, Category = "CharacterCreator|Save")
    FString SaveSlotName;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxSaveSlots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    FString SaveDirectory;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bAutoSave;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float AutoSaveInterval;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    TMap<FName, FCharacterCustomizationPreset> InMemoryCharacters;
    float TimeSinceLastAutoSave;

    FString GetCharacterSavePath(FName CharacterID) const;
    FString GetSlotSavePath(int32 SlotIndex) const;
    FString GetSaveExtension() const { return TEXT(".lfchar"); }
};
