#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMotionMatchingSystem.generated.h"

USTRUCT(BlueprintType)
struct FPoseMatchResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName AnimationName;

    UPROPERTY(BlueprintReadOnly)
    float BlendTime;

    UPROPERTY(BlueprintReadOnly)
    float MatchScore;

    UPROPERTY(BlueprintReadOnly)
    float StartTimePosition;

    FPoseMatchResult()
        : AnimationName(NAME_None), BlendTime(0.2f)
        , MatchScore(0.0f), StartTimePosition(0.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightMotionMatchingSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMotionMatchingSystem();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    FPoseMatchResult FindBestPose(FVector TargetVelocity, FRotator TargetRotation,
        bool bIsGrounded, float CurrentSpeed);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void SetMotionMatchingSettings(const FMotionMatchingSettings& InSettings);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void SetMotionDatabase(const TArray<FName>& AnimationList);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void ApplyMotionWarp(FName WarpTarget, FVector TargetLocation, float Duration = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void CancelMotionWarp();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void Enable(bool bInEnabled) { bEnabled = bInEnabled; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void SetMode(EMotionMatchingMode InMode) { Mode = InMode; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|MotionMatching")
    bool IsEnabled() const { return bEnabled; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|MotionMatching")
    EMotionMatchingMode GetMode() const { return Mode; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|MotionMatching")
    bool IsMotionWarpActive() const { return bMotionWarpActive; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|MotionMatching")
    FName GetCurrentAnimation() const { return CurrentAnimation; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|MotionMatching")
    float GetBlendProgress() const { return BlendProgress; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|MotionMatching")
    void Reset();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EMotionMatchingMode Mode;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bMotionWarpActive;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName CurrentAnimation;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float BlendProgress;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FMotionMatchingSettings Settings;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TArray<FName> MotionDatabase;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    float MotionWarpTimer;
    FVector WarpTargetLocation;
    FVector WarpStartLocation;

    void ProcessMotionMatching(float DeltaTime);
    void ProcessMotionWarp(float DeltaTime);
    void BlendToAnimation(const FPoseMatchResult& Result);
    float CalculatePoseScore(FVector Velocity, FRotator Rotation, bool bGrounded,
        float Speed, int32 AnimIndex);
    void EnableTerrainAdaptation();
    void DirectionalBlend(FVector InputDirection);
};
