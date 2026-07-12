#pragma once

#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightAIGenerationUI.generated.h"

UENUM(BlueprintType)
enum class EPhotoProcessingStage : uint8
{
    WaitingForPhoto,
    PhotoUploaded,
    Processing,
    GeneratingMesh,
    AdjustingResults,
    Complete,
    Failed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhotoSelected, UTexture2D*, Photo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProcessingComplete, FName, CharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGenerationConfirmed, FName, CharacterID);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIGenerationUI : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void OpenPhotoUpload();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void SelectPhotoFromDevice();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void TakePhoto();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void SetImagePreview(UTexture2D* Image);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void ClearImagePreview();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void StartProcessing();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void CancelProcessing();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void SetProcessingProgress(float Progress);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void SetProcessingStatus(FText Status);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void SetProcessingStage(EPhotoProcessingStage Stage);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void ShowGeneratedPreview(class USkeletalMesh* GeneratedMesh, UTexture2D* Texture);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void AdjustResult(float ParameterIndex, float Value);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void ConfirmCharacter(FName CharacterName);

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void RegenerateCharacter();

    UFUNCTION(BlueprintCallable, Category = "AIGeneration")
    void ResetToDefaults();

    UPROPERTY(BlueprintAssignable, Category = "AIGeneration")
    FOnPhotoSelected OnPhotoSelected;

    UPROPERTY(BlueprintAssignable, Category = "AIGeneration")
    FOnProcessingComplete OnProcessingComplete;

    UPROPERTY(BlueprintAssignable, Category = "AIGeneration")
    FOnGenerationConfirmed OnGenerationConfirmed;

protected:
    UPROPERTY()
    UTexture2D* SelectedPhoto = nullptr;

    UPROPERTY()
    UTexture2D* GeneratedTexture = nullptr;

    UPROPERTY()
    TSoftObjectPtr<USkeletalMesh> GeneratedMesh;

    UPROPERTY()
    float ProcessingProgress = 0.0f;

    UPROPERTY()
    EPhotoProcessingStage CurrentStage = EPhotoProcessingStage::WaitingForPhoto;

    UPROPERTY()
    TArray<float> AdjustmentParameters;
};
