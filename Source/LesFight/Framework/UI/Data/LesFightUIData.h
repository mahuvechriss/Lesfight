#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "LesFightUIData.generated.h"

USTRUCT(BlueprintType)
struct LESFIGHT_API FUIAccessibilitySettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHighContrast = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLargeText = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bColorBlindMode = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSubtitlesEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bReducedMotion = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float UIScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TextScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Language = TEXT("en");
};

USTRUCT(BlueprintType)
struct LESFIGHT_API FUIAnimationDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLoop = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float OffsetX = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float OffsetY = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Scale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Opacity = 1.0f;
};

USTRUCT(BlueprintType)
struct LESFIGHT_API FActiveAnimation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AnimationName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FUIAnimationDef Def;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ElapsedTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPaused = false;
};

USTRUCT(BlueprintType)
struct LESFIGHT_API FWidgetTestResult
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPassed = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText WidgetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FText> Errors;
};

USTRUCT(BlueprintType)
struct LESFIGHT_API FLocalizationIssue
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Language;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Issue;
};

USTRUCT(BlueprintType)
struct LESFIGHT_API FPerformanceSample
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Timestamp = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FrameTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WidgetCount = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MemoryUsage = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsApplied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsSaved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGraphicsApplied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGraphicsReverted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlsApplied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlsReverted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabChanged, int32, TabIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAccessibilityChanged, FUIAccessibilitySettings, NewSettings);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostAnimationEvent, FName, AnimationName);
