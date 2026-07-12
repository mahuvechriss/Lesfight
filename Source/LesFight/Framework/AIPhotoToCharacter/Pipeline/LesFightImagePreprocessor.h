#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightImagePreprocessor.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightImagePreprocessor : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    bool PreprocessImage(const FString& SourcePath, FString& OutProcessedPath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    bool RemoveBackground(const FString& ImagePath, FString& OutPath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    bool AdjustColorBalance(const FString& ImagePath, float Brightness, float Contrast, float Saturation);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    bool ResizeImage(const FString& ImagePath, int32 MaxDimension);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    bool DetectEdges(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    bool NormalizeLighting(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Preprocessing")
    TArray<FString> GetPreprocessingLog() const;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Preprocessing")
    TArray<FString> PreprocessingLog;

    UPROPERTY(EditDefaultsOnly, Category = "Preprocessing")
    int32 MaxPreprocessDimension = 1024;

    UPROPERTY(EditDefaultsOnly, Category = "Preprocessing")
    int32 MaxLogEntries = 50;

private:
    void AddLogEntry(const FString& Entry);

    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};
