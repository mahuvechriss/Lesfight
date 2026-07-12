#include "LesFightImageValidator.h"

void ULesFightImageValidator::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightImageValidator::ValidateImage(const FImageUploadResult& Upload)
{
    ValidationDetails.Empty();

    if (!Upload.bValid)
    {
        ValidationScore = 0.0f;
        bImageUsable = false;
        ValidationDetails.Add(TEXT("Image is not valid"));
        return;
    }

    float QualityMultiplier = 0.0f;
    switch (Upload.Quality)
    {
    case EImageQuality::Excellent:
        QualityMultiplier = 1.0f;
        break;
    case EImageQuality::Good:
        QualityMultiplier = 0.85f;
        break;
    case EImageQuality::Acceptable:
        QualityMultiplier = 0.65f;
        break;
    case EImageQuality::Poor:
        QualityMultiplier = 0.5f;
        break;
    default:
        QualityMultiplier = 0.6f;
        break;
    }

    float ResolutionFactor = 1.0f;
    if (Upload.Width > 0 && Upload.Height > 0)
    {
        int32 TotalPixels = Upload.Width * Upload.Height;
        if (TotalPixels >= 4096 * 4096)
        {
            ResolutionFactor = 1.0f;
        }
        else if (TotalPixels >= 1920 * 1080)
        {
            ResolutionFactor = 0.9f;
        }
        else if (TotalPixels >= 1280 * 720)
        {
            ResolutionFactor = 0.75f;
        }
        else
        {
            ResolutionFactor = 0.5f;
        }
    }

    float BaseScore = FMath::FRandRange(0.5f, 1.0f);
    ValidationScore = BaseScore * QualityMultiplier * ResolutionFactor;
    ValidationScore = FMath::Clamp(ValidationScore, 0.0f, 1.0f);

    bImageUsable = ValidationScore >= MinScore;

    if (bImageUsable)
    {
        ValidationDetails.Add(FString::Printf(TEXT("Validation passed: score=%.2f"), ValidationScore));
    }
    else
    {
        ValidationDetails.Add(FString::Printf(TEXT("Validation failed: score=%.2f (min=%.2f)"), ValidationScore, MinScore));
    }

    if (Upload.FileSizeMB > 5.0f)
    {
        ValidationDetails.Add(TEXT("Warning: Large file size may affect performance"));
    }

    if (Upload.Width < 640 || Upload.Height < 480)
    {
        ValidationDetails.Add(TEXT("Warning: Low resolution image may produce poor results"));
    }

    if (QualityMultiplier < 0.7f)
    {
        ValidationDetails.Add(TEXT("Warning: Low image quality detected"));
    }
}

void ULesFightImageValidator::ValidateAll(const TArray<FImageUploadResult>& Uploads)
{
    if (Uploads.Num() == 0)
    {
        ValidationScore = 0.0f;
        bImageUsable = false;
        ValidationDetails.Add(TEXT("No images to validate"));
        return;
    }

    float TotalScore = 0.0f;
    int32 UsableCount = 0;

    for (const FImageUploadResult& Upload : Uploads)
    {
        ValidateImage(Upload);
        TotalScore += ValidationScore;
        if (bImageUsable)
        {
            UsableCount++;
        }
    }

    ValidationScore = TotalScore / static_cast<float>(Uploads.Num());
    bImageUsable = UsableCount == Uploads.Num();

    ValidationDetails.Add(FString::Printf(TEXT("Validated %d images, %d usable"), Uploads.Num(), UsableCount));
}

float ULesFightImageValidator::GetValidationScore() const
{
    return ValidationScore;
}

bool ULesFightImageValidator::IsImageUsable() const
{
    return bImageUsable;
}

TArray<FString> ULesFightImageValidator::GetValidationDetails() const
{
    return ValidationDetails;
}

ELightingCondition ULesFightImageValidator::EstimateLighting(const FString& ImagePath)
{
    float Score = FMath::FRandRange(0.0f, 1.0f);

    if (Score >= 0.8f)
    {
        return ELightingCondition::WellLit;
    }
    else if (Score >= 0.6f)
    {
        return ELightingCondition::Mixed;
    }
    else if (Score >= 0.4f)
    {
        return ELightingCondition::LowLight;
    }
    else if (Score >= 0.2f)
    {
        return ELightingCondition::Backlit;
    }
    else
    {
        return ELightingCondition::HarshShadow;
    }
}

EFaceVisibility ULesFightImageValidator::EstimateFaceVisibility(const FString& ImagePath)
{
    float Score = FMath::FRandRange(0.0f, 1.0f);

    if (Score >= 0.7f)
    {
        return EFaceVisibility::FullFrontal;
    }
    else if (Score >= 0.4f)
    {
        return EFaceVisibility::Profile;
    }
    else if (Score >= 0.15f)
    {
        return EFaceVisibility::Partial;
    }
    else
    {
        return EFaceVisibility::NotVisible;
    }
}
