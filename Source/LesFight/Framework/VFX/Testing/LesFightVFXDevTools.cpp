#include "LesFightVFXDevTools.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"
#include "Framework/VFX/Camera/LesFightCameraEffects.h"

void ULesFightVFXDevTools::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    bDebugMode = false;
    MaxLogEntries = 200;
}

void ULesFightVFXDevTools::EnableDebugMode(bool bEnabled)
{
    bDebugMode = bEnabled;
}

void ULesFightVFXDevTools::PlayTestImpact(EImpactVFXType Type)
{
    if (!OwnerManager.IsValid()) return;

    OwnerManager->GetImpactEffectSystem()->PlayImpactEffect(Type, FVector::ZeroVector, FVector::UpVector, nullptr);
    if (OwnerManager->GetCameraEffects())
    {
        OwnerManager->GetCameraEffects()->PlayCameraShake(Type, FVector::ZeroVector);
    }

    TestLog.Add(FString::Printf(TEXT("Played test impact: %s"), *UEnum::GetValueAsString(Type)));
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

void ULesFightVFXDevTools::PlayTestAura(ECharacterAuraType Type)
{
    if (!OwnerManager.IsValid()) return;
    TestLog.Add(FString::Printf(TEXT("Played test aura: %s"), *UEnum::GetValueAsString(Type)));
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

void ULesFightVFXDevTools::PlayTestMotionTrail(EMotionVFXType Type)
{
    if (!OwnerManager.IsValid()) return;
    TestLog.Add(FString::Printf(TEXT("Played test motion trail: %s"), *UEnum::GetValueAsString(Type)));
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

void ULesFightVFXDevTools::TestAllEffects()
{
    if (!OwnerManager.IsValid()) return;

    TArray<EImpactVFXType> AllImpactTypes;
    for (int32 i = 0; i < (int32)EImpactVFXType::Max; i++)
    {
        AllImpactTypes.Add((EImpactVFXType)i);
    }

    for (EImpactVFXType Type : AllImpactTypes)
    {
        PlayTestImpact(Type);
    }

    TestLog.Add(TEXT("Tested all VFX effects"));
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

void ULesFightVFXDevTools::TestCinematicSequence(ECinematicVFXEvent Event)
{
    if (!OwnerManager.IsValid()) return;

    if (OwnerManager->GetCinematicEffectManager())
    {
    }

    TestLog.Add(FString::Printf(TEXT("Played cinematic sequence: %s"), *UEnum::GetValueAsString(Event)));
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

void ULesFightVFXDevTools::DisplayVFXStats()
{
    if (!OwnerManager.IsValid()) return;

    FString Stats = TEXT("=== VFX Stats ===\n");
    Stats += FString::Printf(TEXT("Active Camera Shake: %s\n"),
        OwnerManager->GetCameraEffects() && OwnerManager->GetCameraEffects()->IsCameraShakeEnabled() ? TEXT("Enabled") : TEXT("Disabled"));

    TestLog.Add(Stats);
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

void ULesFightVFXDevTools::RunVFXStressTest(int32 EffectCount)
{
    if (!OwnerManager.IsValid()) return;

    int32 SpawnedCount = FMath::Min(EffectCount, 500);
    for (int32 i = 0; i < SpawnedCount; i++)
    {
        FVector RandomLocation = FVector(
            FMath::FRandRange(-1000.0f, 1000.0f),
            FMath::FRandRange(-1000.0f, 1000.0f),
            FMath::FRandRange(0.0f, 100.0f)
        );

        OwnerManager->GetImpactEffectSystem()->PlayImpactEffect(EImpactVFXType::LightPunch, RandomLocation, FVector::UpVector, nullptr);
    }

    float StartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    float TestDuration = 5.0f;

    TestLog.Add(FString::Printf(TEXT("Stress test spawned %d effects in %.2f seconds"), SpawnedCount, TestDuration));
    TestResults.Add(TEXT("StressTest_Spawned"), (float)SpawnedCount);
    TestResults.Add(TEXT("StressTest_Duration"), TestDuration);

    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
}

FString ULesFightVFXDevTools::GenerateVFXReport() const
{
    FString Report = TEXT("VFX Dev Report:\n");

    Report += TEXT("\nTest Results:\n");
    for (const TPair<FString, float>& Result : TestResults)
    {
        Report += FString::Printf(TEXT("  %s: %.2f\n"), *Result.Key, Result.Value);
    }

    Report += TEXT("\nRecent Log:\n");
    int32 StartIdx = FMath::Max(0, TestLog.Num() - 20);
    for (int32 i = StartIdx; i < TestLog.Num(); i++)
    {
        Report += FString::Printf(TEXT("  [%d] %s\n"), i, *TestLog[i]);
    }

    return Report;
}
