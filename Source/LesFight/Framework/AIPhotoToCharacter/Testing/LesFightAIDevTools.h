#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightAIDevTools.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDevTestComplete, bool, bSuccess, const FString&, Report);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void SetDevModeEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    bool IsDevModeEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void TestImageInput(const FString& TestImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void CompareGeneratedFace(const FAICharacterGenerationResult& Result, const FString& OriginalImage);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    float GetFaceAccuracyScore() const;

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void PreviewGeneratedMesh(const FAICharacterGenerationResult& Result);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void AdjustAIParameter(const FString& ParamName, float Value);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    bool ValidateSkeletonCompatibility(const FAICharacterGenerationResult& Result);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    bool TestAnimationPerformance(const FAICharacterGenerationResult& Result, FName AnimationName);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    bool RunFullPipelineTest(const FString& TestImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    bool GenerateAccuracyReport(const FString& OutputPath);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void VisualizeLandmarks(const FString& ImagePath, const FFacialLandmarkData& Landmarks, const FString& OutputPath);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void OverlayGeneratedOnOriginal(const FAICharacterGenerationResult& Result, const FString& OriginalImage, const FString& OutputPath);

    UPROPERTY(BlueprintAssignable, Category = "AI|DevTools")
    FOnDevTestComplete OnDevTestComplete;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|DevTools|Config")
    bool bDevMode;

    UPROPERTY(BlueprintReadOnly, Category = "AI|DevTools|Accuracy")
    float FaceAccuracyScore;

    UPROPERTY(BlueprintReadOnly, Category = "AI|DevTools|Report")
    TArray<FAIDevReportEntry> DevReport;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|DevTools|Config")
    int32 MaxReportEntries;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|DevTools|Config")
    TMap<FString, float> AIParameters;

private:
    TWeakObjectPtr<class ULesFightAIManager> OwnerManager;

public:
    void Initialize(ULesFightAIManager* InManager);
};
