#include "LesFightMotionMatchingSystem.h"
#include "LesFightMartialArtsManager.h"

ULesFightMotionMatchingSystem::ULesFightMotionMatchingSystem()
    : bEnabled(false)
    , Mode(EMotionMatchingMode::Disabled)
    , bMotionWarpActive(false)
    , CurrentAnimation(NAME_None)
    , BlendProgress(0.0f)
    , MotionWarpTimer(0.0f)
{
}

void ULesFightMotionMatchingSystem::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    Settings = FMotionMatchingSettings();
}

void ULesFightMotionMatchingSystem::Tick(float DeltaTime)
{
    if (!bEnabled) return;

    ProcessMotionMatching(DeltaTime);
    if (bMotionWarpActive)
    {
        ProcessMotionWarp(DeltaTime);
    }
}

FPoseMatchResult ULesFightMotionMatchingSystem::FindBestPose(
    FVector TargetVelocity, FRotator TargetRotation,
    bool bIsGrounded, float CurrentSpeed)
{
    FPoseMatchResult BestResult;
    BestResult.BlendTime = Settings.BlendSpeed > 0.0f ? 1.0f / Settings.BlendSpeed : 0.2f;

    if (MotionDatabase.Num() == 0) return BestResult;

    float BestScore = -1.0f;
    int32 BestAnimIndex = -1;

    for (int32 i = 0; i < MotionDatabase.Num(); i++)
    {
        float Score = CalculatePoseScore(TargetVelocity, TargetRotation,
            bIsGrounded, CurrentSpeed, i);
        if (Score > BestScore)
        {
            BestScore = Score;
            BestAnimIndex = i;
        }
    }

    if (BestAnimIndex >= 0)
    {
        BestResult.AnimationName = MotionDatabase[BestAnimIndex];
        BestResult.MatchScore = BestScore;
        BestResult.BlendTime = FMath::Max(0.05f, 1.0f / Settings.BlendSpeed);
    }

    return BestResult;
}

void ULesFightMotionMatchingSystem::SetMotionMatchingSettings(
    const FMotionMatchingSettings& InSettings)
{
    Settings = InSettings;
    bEnabled = Settings.Mode != EMotionMatchingMode::Disabled;
    Mode = Settings.Mode;
}

void ULesFightMotionMatchingSystem::SetMotionDatabase(
    const TArray<FName>& AnimationList)
{
    MotionDatabase = AnimationList;
}

void ULesFightMotionMatchingSystem::ApplyMotionWarp(
    FName WarpTarget, FVector TargetLocation, float Duration)
{
    if (!bEnabled) return;

    bMotionWarpActive = true;
    WarpTargetLocation = TargetLocation;
    MotionWarpTimer = Duration;

    if (OwnerManager.IsValid())
    {
        AActor* Owner = Cast<AActor>(OwnerManager->GetOuter());
        if (Owner)
        {
            WarpStartLocation = Owner->GetActorLocation();
        }
    }
}

void ULesFightMotionMatchingSystem::CancelMotionWarp()
{
    bMotionWarpActive = false;
    MotionWarpTimer = 0.0f;
}

void ULesFightMotionMatchingSystem::Reset()
{
    bEnabled = false;
    bMotionWarpActive = false;
    CurrentAnimation = NAME_None;
    BlendProgress = 0.0f;
    MotionWarpTimer = 0.0f;
}

void ULesFightMotionMatchingSystem::ProcessMotionMatching(float DeltaTime)
{
    if (BlendProgress < 1.0f)
    {
        BlendProgress = FMath::Min(BlendProgress + Settings.BlendSpeed * DeltaTime, 1.0f);
    }
}

void ULesFightMotionMatchingSystem::ProcessMotionWarp(float DeltaTime)
{
    if (!bMotionWarpActive) return;

    MotionWarpTimer -= DeltaTime;
    if (MotionWarpTimer <= 0.0f)
    {
        bMotionWarpActive = false;

        if (OwnerManager.IsValid())
        {
            AActor* Owner = Cast<AActor>(OwnerManager->GetOuter());
            if (Owner)
            {
                Owner->SetActorLocation(WarpTargetLocation);
            }
        }
    }
}

void ULesFightMotionMatchingSystem::BlendToAnimation(const FPoseMatchResult& Result)
{
    if (Result.AnimationName != NAME_None)
    {
        CurrentAnimation = Result.AnimationName;
        BlendProgress = 0.0f;
    }
}

float ULesFightMotionMatchingSystem::CalculatePoseScore(
    FVector Velocity, FRotator Rotation, bool bGrounded,
    float Speed, int32 AnimIndex)
{
    float Score = 1.0f;
    if (Speed > 0.0f)
    {
        float SpeedDiff = FMath::Abs(Speed - 200.0f);
        Score -= SpeedDiff / 1000.0f;
    }
    return FMath::Clamp(Score, 0.0f, 1.0f);
}

void ULesFightMotionMatchingSystem::EnableTerrainAdaptation()
{
}

void ULesFightMotionMatchingSystem::DirectionalBlend(FVector InputDirection)
{
}
