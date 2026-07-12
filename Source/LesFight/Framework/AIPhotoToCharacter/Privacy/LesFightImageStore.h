#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightImageStore.generated.h"

class ULesFightAIPipelineManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightImageStore : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    void Initialize(ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    bool StoreImage(const FString& SourcePath, FString& OutStoredPath);

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    bool RetrieveImage(const FString& StoredPath, FString& OutPath);

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    bool DeleteImage(const FString& StoredPath);

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    void DeleteAllImages();

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    int32 GetStoredImageCount() const;

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    float GetTotalStorageSizeMB() const;

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    bool IsImageExpired(const FString& StoredPath) const;

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    void CleanExpiredImages();

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    FString GetStorageDirectory() const;

    UFUNCTION(BlueprintCallable, Category = "ImageStore")
    void SetStorageDirectory(const FString& Dir);

protected:
    UPROPERTY(EditAnywhere, Category = "ImageStore")
    FString StorageDirectory;

    UPROPERTY()
    TMap<FString, FDateTime> ImageTimestamps;

    UPROPERTY(Config)
    int32 MaxStorageMB = 500;

    UPROPERTY()
    float TotalSizeMB = 0.0f;

private:
    TWeakObjectPtr<ULesFightAIPipelineManager> OwnerManager;

    TArray<FString> StoredImagePaths;
};
