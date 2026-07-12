#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterRandomizer.generated.h"

UCLASS(Blueprintable)
class ULesFightCharacterRandomizer : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterRandomizer();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    FCharacterCustomizationPreset GenerateRandomCharacter();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeFace(TMap<EFaceMorphType, float>& FaceMorphs);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeHair(FHairCustomizationData& HairData);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeBody(TMap<EBodyMorphType, float>& BodyMorphs);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeSkin(FSkinCustomizationData& SkinData);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeClothing(TMap<EClothingSlot, FClothingItemData>& Clothing);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeAccessories(TMap<EAccessorySlot, FAccessoryData>& Accessories);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeVoice(FVoiceSelectionData& VoiceData);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void RandomizeBiography(FCharacterBiographyData& BioData);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    void SetRandomSeed(int32 Seed);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Randomizer")
    TArray<FCharacterCustomizationPreset> GenerateBatch(int32 Count);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FString> RandomFirstNames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FString> RandomLastNames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FString> RandomNicknames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FString> RandomCountries;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float RandomizationIntensity;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    FRandomStream RandomStream;

    float RandomMorphValue(float Min, float Max) const;
    FLinearColor RandomColorFromPalette(const TArray<FLinearColor>& Palette) const;
    FString RandomFromArray(const TArray<FString>& Array) const;
    int32 RandomIndex(int32 Max) const;
    bool RandomBool(float TrueChance = 0.5f) const;
};
