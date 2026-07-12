#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightFaceCustomization.generated.h"

UCLASS(Blueprintable)
class ULesFightFaceCustomization : public UObject
{
    GENERATED_BODY()

public:
    ULesFightFaceCustomization();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    void SetMorphValue(EFaceMorphType MorphType, float Value);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    float GetMorphValue(EFaceMorphType MorphType) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    void SetAllMorphs(const TMap<EFaceMorphType, float>& Morphs);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    TMap<EFaceMorphType, float> GetAllMorphs() const { return CurrentMorphs; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    void ResetToDefault();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    float GetMorphRange(EFaceMorphType MorphType) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    void SetEyeColor(FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    FLinearColor GetEyeColor() const { return CurrentEyeColor; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Face")
    TArray<EFaceMorphType> GetAvailableMorphs() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<EFaceMorphType, float> CurrentMorphs;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FLinearColor CurrentEyeColor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TMap<EFaceMorphType, float> MorphRanges;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
