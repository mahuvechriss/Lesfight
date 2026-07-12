#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "Framework/CharacterCreation/Data/LesFightCharacterCreationData.h"
#include "LesFightBodyEstimator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBodyEstimator : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void EstimateBodyProportions(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    FBodyProportionData GetBodyProportions() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    float GetEstimatedHeight() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    float GetConfidence() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void SetReferenceHeight(float HeightCM);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    TMap<EBodyMorphType, float> GenerateBodyMorphTargets() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void CorrectProportionsManually(const FBodyProportionData& Corrections);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Estimation")
    FBodyProportionData EstimatedProportions;

    UPROPERTY(EditDefaultsOnly, Category = "Estimation")
    float ReferenceHeight = 175.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Estimation")
    float EstimationConfidence;

    UPROPERTY(VisibleInstanceOnly, Category = "Estimation")
    TMap<EBodyMorphType, float> BodyMorphs;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};
