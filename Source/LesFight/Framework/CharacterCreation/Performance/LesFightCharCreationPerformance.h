#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharCreationPerformance.generated.h"

UCLASS(Blueprintable)
class ULesFightCharCreationPerformance : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharCreationPerformance();

    void Initialize(class ULesFightCharCreationManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void SetDetailLevel(int32 DetailLevel);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    int32 GetDetailLevel() const { return CurrentDetailLevel; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void SetPreviewQuality(int32 Quality);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    int32 GetPreviewQuality() const { return CurrentPreviewQuality; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void SetTextureResolutionScale(float Scale);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    float GetTextureResolutionScale() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void SetLODBias(int32 Bias);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    int32 GetLODBias() const { return CurrentLODBias; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void EnableDynamicResolution(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    bool IsDynamicResolutionEnabled() const { return bDynamicResolution; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void SetTargetFrameRate(int32 FPS);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    int32 GetCurrentFrameRate() const { return CurrentFrameRate; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Performance")
    float GetPerformanceScore() const { return PerformanceScore; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void OptimizeForPlatform();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void ApplyOptimizations();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Performance")
    void ResetToDefault();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentDetailLevel;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentPreviewQuality;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentLODBias;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bDynamicResolution;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float TextureScale;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float PerformanceScore;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 TargetFrameRate;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentFrameRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 DefaultDetailLevel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 DefaultPreviewQuality;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxDetailLevel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxPreviewQuality;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    float FrameTimeHistory[60];
    int32 FrameTimeIndex;
};
