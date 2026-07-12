#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterPreview.generated.h"

UCLASS(Blueprintable)
class ULesFightCharacterPreview : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterPreview();

    void Initialize(class ULesFightCharCreationManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void ShowPreview(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void HidePreview();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void RotateCharacter(float YawInput);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void ZoomCharacter(float ZoomInput);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void ResetCamera();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void SetBackground(EPreviewBackground Background);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void SetLighting(float Intensity, float Angle, FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void SetAutoRotate(bool bAutoRotate);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void CaptureScreenshot(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void UpdatePreviewMesh(const FCharacterCustomizationPreset& Preset);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void SetAnimationPreview(bool bPlaying, FName MontageName = NAME_None);

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Preview")
    bool IsPreviewActive() const { return bPreviewActive; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Preview")
    float GetRotation() const { return CurrentRotation; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|Preview")
    float GetZoom() const { return CurrentZoom; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Preview")
    void Reset();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bPreviewActive;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bAutoRotate;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float CurrentRotation;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float CurrentZoom;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPreviewBackground CurrentBackground;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName PreviewCharacterID;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float RotationSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float ZoomSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MinZoom;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxZoom;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float DefaultZoom;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
