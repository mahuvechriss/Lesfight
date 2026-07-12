#include "Framework/VFX/Combat/LesFightImpactEffectSystem.h"
#include "Framework/VFX/Core/LesFightVFXWorldManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ULesFightImpactEffectSystem::ULesFightImpactEffectSystem()
{
}

void ULesFightImpactEffectSystem::Initialize()
{
    ImpactDefinitions.Empty();
    ImpactCooldowns.Empty();

    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::LightPunch;
        Def.Scale = FVector(0.5f);
        Def.Lifetime = 0.5f;
        Def.bUseDecal = true;
        Def.DecalSize = 16.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::LightPunch, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::HeavyPunch;
        Def.Scale = FVector(1.0f);
        Def.Lifetime = 0.8f;
        Def.bUseDecal = true;
        Def.DecalSize = 32.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::HeavyPunch, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::LightKick;
        Def.Scale = FVector(0.6f);
        Def.Lifetime = 0.5f;
        Def.bUseDecal = true;
        Def.DecalSize = 20.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::LightKick, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::HeavyKick;
        Def.Scale = FVector(1.1f);
        Def.Lifetime = 0.8f;
        Def.bUseDecal = true;
        Def.DecalSize = 36.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::HeavyKick, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::SpecialAttack;
        Def.Scale = FVector(1.5f);
        Def.Lifetime = 1.2f;
        Def.bUseDecal = true;
        Def.DecalSize = 48.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::SpecialAttack, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::UltimateAttack;
        Def.Scale = FVector(2.0f);
        Def.Lifetime = 2.0f;
        Def.bUseDecal = true;
        Def.DecalSize = 64.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::UltimateAttack, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::BodyImpact;
        Def.Scale = FVector(0.8f);
        Def.Lifetime = 0.6f;
        Def.bUseDecal = false;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::BodyImpact, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::BlockImpact;
        Def.Scale = FVector(0.4f);
        Def.Lifetime = 0.4f;
        Def.bUseDecal = false;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::BlockImpact, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::GroundImpact;
        Def.Scale = FVector(1.0f);
        Def.Lifetime = 0.8f;
        Def.bUseDecal = true;
        Def.DecalSize = 40.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::GroundImpact, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::WallImpact;
        Def.Scale = FVector(1.0f);
        Def.Lifetime = 0.8f;
        Def.bUseDecal = true;
        Def.DecalSize = 40.0f;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::WallImpact, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::CounterImpact;
        Def.Scale = FVector(1.2f);
        Def.Lifetime = 1.0f;
        Def.bUseDecal = false;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::CounterImpact, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::Knockdown;
        Def.Scale = FVector(1.0f);
        Def.Lifetime = 1.0f;
        Def.bUseDecal = false;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::Knockdown, Def);
    }
    {
        FImpactVFXDef Def;
        Def.Type = EImpactVFXType::GetUp;
        Def.Scale = FVector(0.8f);
        Def.Lifetime = 0.6f;
        Def.bUseDecal = false;
        Def.bAttachedToCharacter = false;
        ImpactDefinitions.Add(EImpactVFXType::GetUp, Def);
    }
}

void ULesFightImpactEffectSystem::PlayImpactEffect(EImpactVFXType Type, FVector Location, FVector Normal, float Scale)
{
    const FImpactVFXDef* Def = ImpactDefinitions.Find(Type);
    if (!Def)
    {
        return;
    }

    float* Cooldown = ImpactCooldowns.Find(Type);
    if (Cooldown && *Cooldown > 0.0f)
    {
        return;
    }

    float FinalScale = Scale * GlobalImpactScale;
    FRotator Rotation = Normal.Rotation();

    UNiagaraSystem* NiagaraAsset = Def->NiagaraSystem.LoadSynchronous();
    if (NiagaraAsset)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraAsset, Location, Rotation, FVector(FinalScale));
    }

    if (Def->bUseDecal)
    {
        UMaterialInterface* DecalMat = Def->DecalMaterial.LoadSynchronous();
        if (DecalMat)
        {
            UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMat, FVector(Def->DecalSize * FinalScale), Location, Rotation, Def->Lifetime);
        }
    }
}

void ULesFightImpactEffectSystem::PlayImpactAttached(EImpactVFXType Type, AActor* Target, FName BoneName)
{
    if (!Target)
    {
        return;
    }

    const FImpactVFXDef* Def = ImpactDefinitions.Find(Type);
    if (!Def)
    {
        return;
    }

    float* Cooldown = ImpactCooldowns.Find(Type);
    if (Cooldown && *Cooldown > 0.0f)
    {
        return;
    }

    UNiagaraSystem* NiagaraAsset = Def->NiagaraSystem.LoadSynchronous();
    if (NiagaraAsset)
    {
        FVector Scale = Def->Scale * GlobalImpactScale;
        UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraAsset, Target->GetRootComponent(), BoneName, Def->SpawnOffset, FRotator::ZeroRotator, FVector(Scale.x), EAttachLocation::SnapToTarget, true, ENCPoolMethod::None);
    }
}

FImpactVFXDef ULesFightImpactEffectSystem::GetImpactDefinition(EImpactVFXType Type) const
{
    const FImpactVFXDef* Def = ImpactDefinitions.Find(Type);
    if (Def)
    {
        return *Def;
    }
    return FImpactVFXDef();
}

void ULesFightImpactEffectSystem::SetImpactScale(float Scale)
{
    GlobalImpactScale = FMath::Max(0.0f, Scale);
}

float ULesFightImpactEffectSystem::GetImpactScale() const
{
    return GlobalImpactScale;
}

void ULesFightImpactEffectSystem::PreloadImpactEffects()
{
    for (TPair<EImpactVFXType, FImpactVFXDef>& Pair : ImpactDefinitions)
    {
        Pair.Value.NiagaraSystem.LoadSynchronous();
        if (Pair.Value.bUseDecal)
        {
            Pair.Value.DecalMaterial.LoadSynchronous();
        }
    }
}
