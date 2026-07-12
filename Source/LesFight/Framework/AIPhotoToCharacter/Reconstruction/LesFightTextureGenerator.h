#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightTextureGenerator.generated.h"

struct FTattooEntry;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightTextureGenerator : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateTextures(const FFaceFeatureData& Features, const FString& SourceImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    FGeneratedTextureData GetGeneratedTextures() const { return GeneratedTextures; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void SetTextureResolution(int32 Resolution);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    int32 GetTextureResolution() const { return TextureResolution; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateNormalMap(const FString& DiffusePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateRoughnessMap(const FString& DiffusePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateSubsurfaceMap(const FString& DiffusePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void ApplySkinDetail(ESkinDetailLevel Detail);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateTattooTexture(const FTattooEntry& Tattoo);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateScarTexture(const FVector2D& Position, float Intensity);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    FGeneratedTextureData GeneratedTextures;

    UPROPERTY(EditDefaultsOnly, Category = "Reconstruction")
    int32 TextureResolution = 2048;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    FString OutputDirectory;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    bool bTexturesGenerated = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};
