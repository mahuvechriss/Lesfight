#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightBodyCustomization.generated.h"

UCLASS(Blueprintable)
class ULesFightBodyCustomization : public UObject
{
    GENERATED_BODY()

public:
    ULesFightBodyCustomization();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    void SetBodyMorph(EBodyMorphType MorphType, float Value);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    float GetBodyMorph(EBodyMorphType MorphType) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    void SetAllBodyMorphs(const TMap<EBodyMorphType, float>& Morphs);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    TMap<EBodyMorphType, float> GetAllBodyMorphs() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    void SetHeight(float Height);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    float GetHeight() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    void SetBuild(ECharacterBuild Build);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    ECharacterBuild GetBuild() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    TArray<EBodyMorphType> GetAvailableMorphs() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Body")
    void ResetToDefault();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<EBodyMorphType, float> CurrentBodyMorphs;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float CurrentHeight;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECharacterBuild CurrentBuild;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MinHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float DefaultHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TMap<EBodyMorphType, float> MorphRanges;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
