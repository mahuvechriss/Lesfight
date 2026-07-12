#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/CharacterCreation/Data/LesFightCharacterCreationData.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightAIResultEditor.generated.h"

class ULesFightAIManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIResultEditor : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditFaceMorph(EFaceMorphType MorphType, float NewValue);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditBodyMorph(EBodyMorphType MorphType, float NewValue);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditHair(EHairStyle Style, FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditSkinTone(FLinearColor Tone);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditClothing(const TMap<EClothingSlot, FClothingItemData>& Clothing);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditVoice(EVoicePack Pack, float Pitch, float Tone);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void EditBiography(const FCharacterBiographyData& Bio);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    FCharacterCustomizationPreset GetCurrentPreset() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void ApplyEditsToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void ResetToAIGenerated();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    void UndoLastEdit();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    TArray<FString> GetEditHistory() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Editing")
    bool HasUnsavedChanges() const;

    void Initialize(ULesFightAIManager* InOwnerManager);
    void SetInitialPreset(const FCharacterCustomizationPreset& Preset);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Photo|Editing")
    FCharacterCustomizationPreset CurrentPreset;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI Photo|Editing")
    FCharacterCustomizationPreset OriginalAIPreset;

    UPROPERTY()
    TArray<FString> EditHistory;

    UPROPERTY(EditDefaultsOnly, Category = "AI Photo|Editing")
    int32 MaxEditHistory;

    UPROPERTY()
    bool bHasUnsavedChanges;

private:
    TWeakObjectPtr<ULesFightAIManager> OwnerManager;
};
