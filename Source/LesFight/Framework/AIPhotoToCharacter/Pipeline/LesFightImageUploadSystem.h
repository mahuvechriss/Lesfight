#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightImageUploadSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightImageUploadSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightImageUploadSystem();

    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    FImageUploadResult UploadImage(const FString& FilePath, EImageType Type);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    TArray<FImageUploadResult> UploadMultipleImages(const TArray<FString>& FilePaths);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    void CancelUpload();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    FImageUploadResult GetLastUploadResult() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    TArray<FImageUploadResult> GetUploadHistory() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    void ClearUploadHistory();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    void SetMaxFileSize(float MB);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    float GetMaxFileSize() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Upload")
    bool IsUploadInProgress() const;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Upload")
    TArray<FImageUploadResult> UploadHistory;

    UPROPERTY(EditDefaultsOnly, Category = "Upload")
    int32 MaxUploadHistory = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Upload")
    float MaxFileSizeMB = 10.0f;

    UPROPERTY(Transient)
    bool bUploadInProgress = false;

    UPROPERTY(EditDefaultsOnly, Category = "Upload")
    TArray<FString> AcceptedExtensions;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};
