#include "LesFightAnimationDebugger.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFight.h"

ULesFightAnimationDebugger::ULesFightAnimationDebugger()
    : bDebugEnabled(false)
    , bShowStates(true)
    , bShowBlendSpaces(false)
    , bShowRootMotion(false)
    , bShowNotifies(false)
    , bShowPerformance(false)
    , FrameTimeIndex(0)
{
    FMemory::Memset(FrameTimeHistory, 0, sizeof(FrameTimeHistory));
}

void ULesFightAnimationDebugger::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("AnimationDebugger initialized"));
}

void ULesFightAnimationDebugger::RegisterAnimComponent(
    ULesFightCharacterAnimationComponent* AnimComp)
{
    if (AnimComp)
    {
        RegisteredComponents.AddUnique(AnimComp);
    }
}

void ULesFightAnimationDebugger::Update(float DeltaTime)
{
    if (!bDebugEnabled) return;

    FrameTimeHistory[FrameTimeIndex] = DeltaTime * 1000.0f;
    FrameTimeIndex = (FrameTimeIndex + 1) % 120;

    CollectDebugData();

    UWorld* World = nullptr;
    if (RegisteredComponents.Num() > 0 && RegisteredComponents[0])
    {
        World = RegisteredComponents[0]->GetWorld();
    }

    if (World)
    {
        DrawDebugOverlay(World);
    }
}

void ULesFightAnimationDebugger::ToggleDebugDisplay()
{
    bDebugEnabled = !bDebugEnabled;
    UE_LOG(LogLesFight, Log, TEXT("Animation Debugger: %s"),
        bDebugEnabled ? TEXT("ENABLED") : TEXT("DISABLED"));
}

void ULesFightAnimationDebugger::SetSlowMotionMode(bool bEnabled, float TimeDilation)
{
    for (ULesFightCharacterAnimationComponent* Comp : RegisteredComponents)
    {
        if (Comp)
        {
            Comp->SetGlobalPlayRate(bEnabled ? TimeDilation : 1.0f);
        }
    }
}

void ULesFightAnimationDebugger::SetAnimationPaused(bool bPaused)
{
    for (ULesFightCharacterAnimationComponent* Comp : RegisteredComponents)
    {
        if (Comp)
        {
            if (bPaused) Comp->PauseAnimation();
            else Comp->ResumeAnimation();
        }
    }
}

void ULesFightAnimationDebugger::CollectDebugData()
{
    DebugInfo.Empty();

    for (ULesFightCharacterAnimationComponent* Comp : RegisteredComponents)
    {
        if (!Comp) continue;

        FAnimationDebugInfo Info;
        AActor* Owner = Comp->GetOwner();
        Info.FighterName = Owner ? Owner->GetName() : TEXT("Unknown");
        Info.CurrentState = UEnum::GetValueAsString(Comp->GetCurrentLocomotionState());
        Info.CurrentCombatAnim = UEnum::GetValueAsString(Comp->GetCurrentCombatAnimType());
        Info.CurrentHitReaction = UEnum::GetValueAsString(Comp->GetCurrentHitReactionAnim());
        Info.bIsPlayingMontage = Comp->IsPlayingMontage();
        Info.MontagePlayTime = Comp->GetCurrentMontagePlayTime();
        Info.PlayRate = Comp->GetGlobalPlayRate();

        DebugInfo.Add(Info);
    }
}

void ULesFightAnimationDebugger::DrawDebugOverlay(UWorld* World)
{
    if (!World) return;

    FString DebugString = TEXT("=== ANIMATION DEBUG ===\n");

    for (const FAnimationDebugInfo& Info : DebugInfo)
    {
        DebugString += FString::Printf(TEXT(
            "[%s]\n"
            "  State: %s | Combat: %s | Reaction: %s\n"
            "  Montage: %s (%.2fs)\n"
            "  PlayRate: %.2f\n"),
            *Info.FighterName,
            *Info.CurrentState, *Info.CurrentCombatAnim, *Info.CurrentHitReaction,
            Info.bIsPlayingMontage ? TEXT("Playing") : TEXT("None"),
            Info.MontagePlayTime, Info.PlayRate);
    }

    if (bShowPerformance)
    {
        float AvgFrameTime = 0.0f;
        int32 Count = 0;
        for (int32 i = 0; i < 120; i++)
        {
            if (FrameTimeHistory[i] > 0.0f)
            {
                AvgFrameTime += FrameTimeHistory[i];
                Count++;
            }
        }
        if (Count > 0) AvgFrameTime /= Count;

        DebugString += FString::Printf(TEXT(
            "\nPerformance:\n  Avg Frame: %.2fms (%.0f FPS)\n"),
            AvgFrameTime, Count > 0 ? 1000.0f / AvgFrameTime : 0.0f);
    }

    GEngine->AddOnScreenDebugMessage(998, 0.0f, FColor::Green, DebugString, true,
        FVector2D(1.0f, 1.0f));
}
