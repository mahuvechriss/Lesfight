#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightHairSystem.generated.h"

UCLASS(Blueprintable)
class ULesFightHairSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightHairSystem();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void SetHairStyle(EHairStyle Style);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    EHairStyle GetHairStyle() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void SetHairColor(FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    FLinearColor GetHairColor() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void SetHairLength(float Length);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    float GetHairLength() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void SetHairShine(float Shine);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void SetPhysicsEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void SetCustomizationData(const FHairCustomizationData& Data);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    FHairCustomizationData GetCustomizationData() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    TArray<EHairStyle> GetAvailableStyles() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Hair")
    void ResetToDefault();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FHairCustomizationData CurrentHairData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<EHairStyle> UnlockedStyles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float DefaultLength;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MinLength;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxLength;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
