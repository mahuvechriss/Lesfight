#include "LesFightPostProcessingManager.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"

void ULesFightPostProcessingManager::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    bTransitioning = false;
    CurrentPreset = EPostProcessingPreset::Default;

    PostProcessingPresets.Empty();
    PostProcessingPresets.Add(EPostProcessingPreset::Default, FPostProcessingState{ 0.0f, 0.0f, 0.5f, 0.2f, 1.0f, 1.0f, FLinearColor::White });
    PostProcessingPresets.Add(EPostProcessingPreset::Combat, FPostProcessingState{ 0.1f, 0.0f, 0.6f, 0.3f, 1.0f, 1.0f, FLinearColor::White });
    PostProcessingPresets.Add(EPostProcessingPreset::Cinematic, FPostProcessingState{ 0.3f, 0.7f, 0.8f, 0.5f, 1.1f, 1.2f, FLinearColor::White });
    PostProcessingPresets.Add(EPostProcessingPreset::SlowMotion, FPostProcessingState{ 0.5f, 0.5f, 0.7f, 0.4f, 1.0f, 1.0f, FLinearColor::White });
    PostProcessingPresets.Add(EPostProcessingPreset::Ultimate, FPostProcessingState{ 0.4f, 0.3f, 1.0f, 0.6f, 1.2f, 1.3f, FLinearColor::White });
    PostProcessingPresets.Add(EPostProcessingPreset::LowHealth, FPostProcessingState{ 0.1f, 0.2f, 0.3f, 0.7f, 0.7f, 0.8f, FLinearColor(1.0f, 0.2f, 0.2f) });
    PostProcessingPresets.Add(EPostProcessingPreset::Victory, FPostProcessingState{ 0.2f, 0.4f, 1.2f, 0.3f, 1.3f, 1.0f, FLinearColor::White });
    PostProcessingPresets.Add(EPostProcessingPreset::Defeat, FPostProcessingState{ 0.3f, 0.5f, 0.2f, 0.6f, 0.5f, 0.7f, FLinearColor::White });

    if (const FPostProcessingState* DefaultState = PostProcessingPresets.Find(CurrentPreset))
    {
        CurrentState = *DefaultState;
        TargetState = *DefaultState;
    }
}

void ULesFightPostProcessingManager::ApplyPreset(EPostProcessingPreset Preset, float TransitionTime)
{
    if (!PostProcessingPresets.Contains(Preset)) return;

    TargetState = PostProcessingPresets[Preset];
    TransitionProgress = 0.0f;
    TransitionTime = FMath::Max(TransitionTime, 0.01f);
    bTransitioning = true;

    OnPostProcessChanged.Broadcast(Preset);
}

void ULesFightPostProcessingManager::SetMotionBlur(float Amount)
{
    CurrentState.MotionBlurAmount = Amount;
}

void ULesFightPostProcessingManager::SetDepthOfField(float Strength)
{
    CurrentState.DepthOfFieldStrength = Strength;
}

void ULesFightPostProcessingManager::SetBloom(float Intensity)
{
    CurrentState.BloomIntensity = Intensity;
}

void ULesFightPostProcessingManager::SetColorGrading(FLinearColor Grade)
{
    CurrentState.ColorGrade = Grade;
}

void ULesFightPostProcessingManager::SetVignette(float Intensity)
{
    CurrentState.VignetteIntensity = Intensity;
}

void ULesFightPostProcessingManager::SetSaturation(float Saturation)
{
    CurrentState.Saturation = Saturation;
}

void ULesFightPostProcessingManager::SetContrast(float Contrast)
{
    CurrentState.Contrast = Contrast;
}

EPostProcessingPreset ULesFightPostProcessingManager::GetCurrentPreset() const
{
    return CurrentPreset;
}

void ULesFightPostProcessingManager::ResetToDefault()
{
    ApplyPreset(EPostProcessingPreset::Default, 0.5f);
}

void ULesFightPostProcessingManager::UpdatePostProcess(float DeltaTime)
{
    if (!bTransitioning) return;

    TransitionProgress += DeltaTime / TransitionTime;
    if (TransitionProgress >= 1.0f)
    {
        TransitionProgress = 1.0f;
        bTransitioning = false;
        CurrentState = TargetState;
        return;
    }

    float Alpha = FMath::InterpEaseOut(0.0f, 1.0f, TransitionProgress, 2.0f);
    CurrentState.MotionBlurAmount = FMath::Lerp(CurrentState.MotionBlurAmount, TargetState.MotionBlurAmount, Alpha);
    CurrentState.DepthOfFieldStrength = FMath::Lerp(CurrentState.DepthOfFieldStrength, TargetState.DepthOfFieldStrength, Alpha);
    CurrentState.BloomIntensity = FMath::Lerp(CurrentState.BloomIntensity, TargetState.BloomIntensity, Alpha);
    CurrentState.VignetteIntensity = FMath::Lerp(CurrentState.VignetteIntensity, TargetState.VignetteIntensity, Alpha);
    CurrentState.Saturation = FMath::Lerp(CurrentState.Saturation, TargetState.Saturation, Alpha);
    CurrentState.Contrast = FMath::Lerp(CurrentState.Contrast, TargetState.Contrast, Alpha);
    CurrentState.ColorGrade = FLinearColor(
        FMath::Lerp(CurrentState.ColorGrade.R, TargetState.ColorGrade.R, Alpha),
        FMath::Lerp(CurrentState.ColorGrade.G, TargetState.ColorGrade.G, Alpha),
        FMath::Lerp(CurrentState.ColorGrade.B, TargetState.ColorGrade.B, Alpha),
        FMath::Lerp(CurrentState.ColorGrade.A, TargetState.ColorGrade.A, Alpha)
    );
}
