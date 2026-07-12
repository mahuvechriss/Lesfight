#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/MartialArts/Data/LesFightMartialArtsData.h"
#include "Framework/CharacterCreation/Data/LesFightCharacterCreationData.h"
#include "LesFightStyleRecommender.generated.h"

class ULesFightAIManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightStyleRecommender : public UObject
{
    GENERATED_BODY()

public:
    ULesFightStyleRecommender();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    void AnalyzePhotosForStyle(const TArray<FString>& PhotoPaths);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    EFightingStyle RecommendFightingStyle() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    TArray<EClothingSlot> RecommendClothingStyle() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    EHairStyle RecommendHairStyle() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    TArray<FLinearColor> RecommendColorPalette() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    float GetStyleConfidence() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    FString GenerateStyleProfile() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    void SetAggressiveness(float InAggressiveness);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Style")
    void SetStylePreferences(const TArray<EFightingStyle>& Preferred);

    void Initialize(ULesFightAIManager* InOwnerManager);

protected:
    UPROPERTY()
    TArray<EFightingStyle> RecommendedStyles;

    UPROPERTY()
    TArray<float> StyleScores;

    UPROPERTY()
    EFightingStyle TopStyle;

    UPROPERTY()
    TArray<EFightingStyle> UserPreferences;

    UPROPERTY(EditDefaultsOnly, Category = "AI Photo|Style")
    float Aggressiveness;

    UPROPERTY()
    float StyleConfidence;

private:
    TWeakObjectPtr<ULesFightAIManager> OwnerManager;
    TMap<EFightingStyle, float> StyleMatchScores;
};
