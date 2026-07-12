#include "Framework/VFX/Combat/LesFightMotionEffectSystem.h"
#include "Framework/VFX/Core/LesFightVFXWorldManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"

ULesFightMotionEffectSystem::ULesFightMotionEffectSystem()
{
}

void ULesFightMotionEffectSystem::Initialize()
{
    MotionDefinitions.Empty();
    ActiveTrails.Empty();

    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::PunchTrail;
        Def.TrailType = ETrailType::GhostTrail;
        Def.TrailLength = 150.0f;
        Def.TrailWidth = 20.0f;
        Def.TrailColor = FLinearColor::White;
        Def.MaxTrailCount = 10;
        Def.SpawnInterval = 0.05f;
        MotionDefinitions.Add(EMotionVFXType::PunchTrail, Def);
    }
    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::KickTrail;
        Def.TrailType = ETrailType::RibbonTrail;
        Def.TrailLength = 200.0f;
        Def.TrailWidth = 30.0f;
        Def.TrailColor = FLinearColor::White;
        Def.MaxTrailCount = 8;
        Def.SpawnInterval = 0.04f;
        MotionDefinitions.Add(EMotionVFXType::KickTrail, Def);
    }
    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::DodgeTrail;
        Def.TrailType = ETrailType::GhostTrail;
        Def.TrailLength = 100.0f;
        Def.TrailWidth = 15.0f;
        Def.TrailColor = FLinearColor(0.5f, 0.5f, 1.0f, 0.6f);
        Def.MaxTrailCount = 5;
        Def.SpawnInterval = 0.08f;
        MotionDefinitions.Add(EMotionVFXType::DodgeTrail, Def);
    }
    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::DashTrail;
        Def.TrailType = ETrailType::ParticleTrail;
        Def.TrailLength = 120.0f;
        Def.TrailWidth = 25.0f;
        Def.TrailColor = FLinearColor(0.8f, 0.8f, 1.0f, 0.5f);
        Def.MaxTrailCount = 6;
        Def.SpawnInterval = 0.06f;
        MotionDefinitions.Add(EMotionVFXType::DashTrail, Def);
    }
    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::SpeedLines;
        Def.TrailType = ETrailType::ParticleTrail;
        Def.TrailLength = 300.0f;
        Def.TrailWidth = 5.0f;
        Def.TrailColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.3f);
        Def.MaxTrailCount = 20;
        Def.SpawnInterval = 0.02f;
        MotionDefinitions.Add(EMotionVFXType::SpeedLines, Def);
    }
    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::Afterimage;
        Def.TrailType = ETrailType::GhostTrail;
        Def.TrailLength = 50.0f;
        Def.TrailWidth = 0.0f;
        Def.TrailColor = FLinearColor(0.5f, 0.5f, 1.0f, 0.3f);
        Def.MaxTrailCount = 3;
        Def.SpawnInterval = 0.15f;
        MotionDefinitions.Add(EMotionVFXType::Afterimage, Def);
    }
    {
        FMotionTrailDef Def;
        Def.Type = EMotionVFXType::AirDistortion;
        Def.TrailType = ETrailType::MotionBlur;
        Def.TrailLength = 80.0f;
        Def.TrailWidth = 40.0f;
        Def.TrailColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.2f);
        Def.MaxTrailCount = 4;
        Def.SpawnInterval = 0.1f;
        MotionDefinitions.Add(EMotionVFXType::AirDistortion, Def);
    }
}

void ULesFightMotionEffectSystem::PlayMotionTrail(EMotionVFXType Type, FTransform Transform)
{
    if (ActiveTrails.Num() >= MaxActiveTrails)
    {
        return;
    }

    FName TrailName = FName(*FString::Printf(TEXT("%s_Trail"), *UEnum::GetValueAsString(Type)));
    ActiveTrails.Add(TrailName);
}

void ULesFightMotionEffectSystem::PlayPunchTrail(FVector Start, FVector End)
{
    if (ActiveTrails.Num() >= MaxActiveTrails)
    {
        return;
    }

    FVector Direction = (End - Start).GetSafeNormal();
    float Distance = FVector::Dist(Start, End);

    FTransform TrailTransform;
    TrailTransform.SetLocation(Start);
    TrailTransform.SetRotation(Direction.Rotation().Quaternion());

    ActiveTrails.Add(TEXT("PunchTrail"));
}

void ULesFightMotionEffectSystem::PlayKickTrail(FVector Start, FVector End)
{
    if (ActiveTrails.Num() >= MaxActiveTrails)
    {
        return;
    }

    FVector Direction = (End - Start).GetSafeNormal();

    FTransform TrailTransform;
    TrailTransform.SetLocation(Start);
    TrailTransform.SetRotation(Direction.Rotation().Quaternion());

    ActiveTrails.Add(TEXT("KickTrail"));
}

void ULesFightMotionEffectSystem::PlayDodgeTrail(AActor* Character)
{
    if (!Character || ActiveTrails.Num() >= MaxActiveTrails)
    {
        return;
    }

    USkeletalMeshComponent* SkeletalMesh = Character->FindComponentByClass<USkeletalMeshComponent>();
    if (SkeletalMesh)
    {
        FTransform CharacterTransform = SkeletalMesh->GetComponentTransform();
    }

    ActiveTrails.Add(TEXT("DodgeTrail"));
}

void ULesFightMotionEffectSystem::SpawnAfterimage(AActor* Character, float Duration)
{
    if (!Character)
    {
        return;
    }

    USkeletalMeshComponent* SkeletalMesh = Character->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMesh)
    {
        return;
    }

    FTransform PoseTransform = SkeletalMesh->GetComponentTransform();
    TArray<FName> ActiveAfterimages;

    if (ActiveAfterimages.Num() >= MaxAfterimages)
    {
        ActiveAfterimages.RemoveAt(0);
    }

    ActiveAfterimages.Add(FName(*FString::Printf(TEXT("Afterimage_%lld"), (int64)Character)));
    ActiveTrails.Add(TEXT("Afterimage"));
}

void ULesFightMotionEffectSystem::PlaySpeedLines(FVector Direction, float Speed)
{
    if (ActiveTrails.Num() >= MaxActiveTrails)
    {
        return;
    }

    ActiveTrails.Add(TEXT("SpeedLines"));
}

void ULesFightMotionEffectSystem::PlayAirDistortion(FVector Location)
{
    if (ActiveTrails.Num() >= MaxActiveTrails)
    {
        return;
    }

    ActiveTrails.Add(TEXT("AirDistortion"));
}

void ULesFightMotionEffectSystem::ClearAllTrails()
{
    ActiveTrails.Empty();
}

void ULesFightMotionEffectSystem::SetTrailIntensity(float Intensity)
{
    TrailIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);
}
