#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "Framework/CharacterCreation/Data/LesFightCharacterCreationData.h"
#include "LesFightHairGenerator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightHairGenerator : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    void GenerateHair(const FHairDetectionData& DetectedHair);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    FString GetGeneratedHairPath() const { return GeneratedHairPath; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    void SetHairQuality(int32 Quality);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    TArray<EHairStyle> GetAvailableHairStyles() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    void OverrideHairStyle(EHairStyle Style);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    void SetHairColor(FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    void SetHairPhysicsEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Hair Generation")
    void ApplyHairToCharacter(AActor* CharacterActor);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Hair Generator")
    FString GeneratedHairPath;

    UPROPERTY(VisibleInstanceOnly, Category = "Hair Generator")
    FHairDetectionData HairData;

    UPROPERTY(VisibleInstanceOnly, Category = "Hair Generator")
    EHairStyle AppliedStyle;

    UPROPERTY(VisibleInstanceOnly, Category = "Hair Generator")
    FLinearColor AppliedColor;

    UPROPERTY(EditDefaultsOnly, Category = "Hair Generator")
    int32 HairQuality = 3;

    UPROPERTY(VisibleInstanceOnly, Category = "Hair Generator")
    bool bHairGenerated = false;

    UPROPERTY(VisibleInstanceOnly, Category = "Hair Generator")
    bool bHairPhysicsEnabled = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;

    EHairStyle MapDetectionToStyle(EHairDetectionType Detected) const;
};
