#include "LesFightEnergyEffectSystem.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "Framework/VFX/World/LesFightVFXWorldManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

void ULesFightEnergyEffectSystem::Initialize(ULesFightVFXWorldManager* InManager)
{
    OwnerManager = InManager;

    WaveNiagaraPaths.Empty();
    WaveNiagaraPaths.Add(EWaveType::Shockwave, TEXT("Shockwave"));
    WaveNiagaraPaths.Add(EWaveType::DustRing, TEXT("Dust_Cloud"));
    WaveNiagaraPaths.Add(EWaveType::EnergyWave, TEXT("Energy_Wave"));
    WaveNiagaraPaths.Add(EWaveType::PressureWave, TEXT("Shockwave"));
}

void ULesFightEnergyEffectSystem::SpawnEnergyWave(FVector Origin, FVector Direction, float Distance, EFightingStyle Style)
{
    if (ActiveEnergyEffects.Num() >= MaxEnergyEffects)
    {
        return;
    }

    FVector EndLocation = Origin + Direction.GetSafeNormal() * Distance;

    UNiagaraComponent* WaveComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        nullptr,
        Origin,
        FRotator::ZeroRotator,
        FVector::OneVector,
        true
    );

    if (WaveComp)
    {
        WaveComp->SetWorldLocation(Origin);
        WaveComp->SetVariableVec3(TEXT("EndLocation"), EndLocation);
        WaveComp->SetVariableFloat(TEXT("Distance"), Distance);
        WaveComp->SetVariableFloat(TEXT("EnergyIntensity"), EnergyIntensity);

        ActiveEnergyEffects.Add(WaveComp->GetFName());
    }
}

void ULesFightEnergyEffectSystem::SpawnShockwave(FVector Location, float Radius, float Force, EWaveType Type)
{
    if (ActiveEnergyEffects.Num() >= MaxEnergyEffects)
    {
        return;
    }

    UNiagaraComponent* ShockwaveComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        nullptr,
        Location,
        FRotator::ZeroRotator,
        FVector(Radius / 100.0f),
        true
    );

    if (ShockwaveComp)
    {
        ShockwaveComp->SetVariableFloat(TEXT("Radius"), Radius);
        ShockwaveComp->SetVariableFloat(TEXT("Force"), Force);
        ShockwaveComp->SetVariableFloat(TEXT("EnergyIntensity"), EnergyIntensity);

        ActiveEnergyEffects.Add(ShockwaveComp->GetFName());
    }
}

void ULesFightEnergyEffectSystem::SpawnAuraBurst(AActor* Character, float Radius)
{
    if (!Character || ActiveEnergyEffects.Num() >= MaxEnergyEffects)
    {
        return;
    }

    UNiagaraComponent* BurstComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
        nullptr,
        Character->GetRootComponent(),
        NAME_None,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::SnapToTarget,
        true
    );

    if (BurstComp)
    {
        BurstComp->SetVariableFloat(TEXT("Radius"), Radius);
        BurstComp->SetVariableFloat(TEXT("EnergyIntensity"), EnergyIntensity);

        ActiveEnergyEffects.Add(BurstComp->GetFName());
    }
}

void ULesFightEnergyEffectSystem::SpawnEnergyProjectile(FVector Start, FVector End, FLinearColor Color)
{
    if (ActiveEnergyEffects.Num() >= MaxEnergyEffects)
    {
        return;
    }

    FVector Direction = (End - Start).GetSafeNormal();
    float Distance = FVector::Dist(Start, End);

    UNiagaraComponent* ProjectileComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        nullptr,
        Start,
        Direction.Rotation(),
        FVector::OneVector,
        true
    );

    if (ProjectileComp)
    {
        ProjectileComp->SetVariableVec3(TEXT("EndLocation"), End);
        ProjectileComp->SetVariableFloat(TEXT("Distance"), Distance);
        ProjectileComp->SetVariableLinearColor(TEXT("ProjectileColor"), Color);
        ProjectileComp->SetVariableFloat(TEXT("EnergyIntensity"), EnergyIntensity);

        ActiveEnergyEffects.Add(ProjectileComp->GetFName());
    }
}

void ULesFightEnergyEffectSystem::SpawnImpactRing(FVector Location, float Radius, FLinearColor Color)
{
    if (ActiveEnergyEffects.Num() >= MaxEnergyEffects)
    {
        return;
    }

    UNiagaraComponent* RingComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        nullptr,
        Location,
        FRotator(-90.0f, 0.0f, 0.0f),
        FVector(Radius / 100.0f),
        true
    );

    if (RingComp)
    {
        RingComp->SetVariableFloat(TEXT("Radius"), Radius);
        RingComp->SetVariableLinearColor(TEXT("RingColor"), Color);
        RingComp->SetVariableFloat(TEXT("EnergyIntensity"), EnergyIntensity);

        ActiveEnergyEffects.Add(RingComp->GetFName());
    }
}

void ULesFightEnergyEffectSystem::ClearEnergyEffects()
{
    ActiveEnergyEffects.Empty();
}

void ULesFightEnergyEffectSystem::SetEnergyIntensity(float Intensity)
{
    EnergyIntensity = FMath::Clamp(Intensity, 0.0f, 2.0f);
}

UWorld* ULesFightEnergyEffectSystem::GetWorld() const
{
    if (OwnerManager.IsValid())
    {
        return OwnerManager->GetWorld();
    }
    return nullptr;
}
