#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharCreationManager.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ULesFightCharCreationManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharCreationManager();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    void SetActiveCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    FName GetActiveCharacter() const { return ActiveCharacterID; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    FCharacterCustomizationPreset GetActiveCharacterData() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    bool SaveActiveCharacter();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    bool LoadCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    TArray<FName> GetAllCharacterIDs() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    void OpenUI();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    void CloseUI();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Manager")
    bool IsUIOpen() const;

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterCreator* GetCreator() const { return Creator; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterPreset* GetPresetSystem() const { return PresetSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterRandomizer* GetRandomizer() const { return Randomizer; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterPreview* GetPreview() const { return Preview; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightFaceCustomization* GetFaceSystem() const { return FaceSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightHairSystem* GetHairSystem() const { return HairSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightBodyCustomization* GetBodySystem() const { return BodySystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightSkinSystem* GetSkinSystem() const { return SkinSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightClothingSystem* GetClothingSystem() const { return ClothingSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightMaterialCustomization* GetMaterialSystem() const { return MaterialSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightAccessorySystem* GetAccessorySystem() const { return AccessorySystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightVoiceSelection* GetVoiceSystem() const { return VoiceSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterBiography* GetBiographySystem() const { return BiographySystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterSaveSystem* GetSaveSystem() const { return SaveSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCustomizationUI* GetUI() const { return UISystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharacterReplication* GetReplication() const { return ReplicationSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharCreationPerformance* GetPerformance() const { return PerformanceSystem; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Manager")
    ULesFightCharCreationDevTools* GetDevTools() const { return DevTools; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterCreator* Creator;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterPreset* PresetSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterRandomizer* Randomizer;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterPreview* Preview;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightFaceCustomization* FaceSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightHairSystem* HairSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightBodyCustomization* BodySystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightSkinSystem* SkinSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightClothingSystem* ClothingSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightMaterialCustomization* MaterialSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightAccessorySystem* AccessorySystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightVoiceSelection* VoiceSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterBiography* BiographySystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterSaveSystem* SaveSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCustomizationUI* UISystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharacterReplication* ReplicationSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharCreationPerformance* PerformanceSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    ULesFightCharCreationDevTools* DevTools;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName ActiveCharacterID;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bInitialized;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterCreator> CreatorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterPreset> PresetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterRandomizer> RandomizerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterPreview> PreviewClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightFaceCustomization> FaceClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightHairSystem> HairClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightBodyCustomization> BodyClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightSkinSystem> SkinClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightClothingSystem> ClothingClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightMaterialCustomization> MaterialClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightAccessorySystem> AccessoryClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightVoiceSelection> VoiceClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterBiography> BioClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterSaveSystem> SaveClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCustomizationUI> UIClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharacterReplication> ReplicationClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharCreationPerformance> PerformanceClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<ULesFightCharCreationDevTools> DevToolsClass;

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Class, T*& OutPtr);
};
