#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightImageValidator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightImageValidator : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    void ValidateImage(const FImageUploadResult& Upload);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    void ValidateAll(const TArray<FImageUploadResult>& Uploads);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    float GetValidationScore() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    bool IsImageUsable() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    TArray<FString> GetValidationDetails() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    ELightingCondition EstimateLighting(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Validation")
    EFaceVisibility EstimateFaceVisibility(const FString& ImagePath);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Validation")
    float ValidationScore = 0.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Validation")
    bool bImageUsable = false;

    UPROPERTY(VisibleInstanceOnly, Category = "Validation")
    TArray<FString> ValidationDetails;

    UPROPERTY(EditDefaultsOnly, Category = "Validation")
    float MinScore = 0.6f;

    UPROPERTY(EditDefaultsOnly, Category = "Validation")
    float MinLightingScore = 0.3f;

    UPROPERTY(EditDefaultsOnly, Category = "Validation")
    float MinFaceVisibility = 0.5f;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};
