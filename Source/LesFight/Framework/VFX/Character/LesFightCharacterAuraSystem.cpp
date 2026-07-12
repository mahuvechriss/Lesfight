#include "LesFightCharacterAuraSystem.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "Framework/VFX/World/LesFightVFXWorldManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ULesFightCharacterAuraSystem::Initialize(ULesFightVFXWorldManager* InManager)
{
    OwnerManager = InManager;

    AuraDefinitions.Empty();

    FCharacterAuraDef PowerDef;
    PowerDef.NiagaraSystemPath = TEXT("Aura_Power");
    PowerDef.Color = FLinearColor(0.0f, 1.0f, 1.0f);
    PowerDef.Intensity = 0.5f;
    PowerDef.Radius = 100.0f;
    PowerDef.bPulsating = true;
    PowerDef.PulseSpeed = 1.0f;
    AuraDefinitions.Add(ECharacterAuraType::PowerAura, PowerDef);

    FCharacterAuraDef UltimateDef;
    UltimateDef.Color = FLinearColor(1.0f, 0.84f, 0.0f);
    UltimateDef.Intensity = 0.8f;
    UltimateDef.Radius = 150.0f;
    UltimateDef.bPulsating = true;
    UltimateDef.PulseSpeed = 2.0f;
    AuraDefinitions.Add(ECharacterAuraType::UltimateCharge, UltimateDef);

    FCharacterAuraDef LowHealthDef;
    LowHealthDef.Color = FLinearColor(1.0f, 0.0f, 0.0f);
    LowHealthDef.Intensity = 0.3f;
    LowHealthDef.Radius = 80.0f;
    LowHealthDef.bPulsating = true;
    LowHealthDef.PulseSpeed = 0.5f;
    AuraDefinitions.Add(ECharacterAuraType::LowHealth, LowHealthDef);

    FCharacterAuraDef VictoryDef;
    VictoryDef.Color = FLinearColor(1.0f, 0.84f, 0.0f);
    VictoryDef.Intensity = 1.0f;
    VictoryDef.Radius = 200.0f;
    VictoryDef.bPulsating = false;
    VictoryDef.PulseSpeed = 0.0f;
    AuraDefinitions.Add(ECharacterAuraType::Victory, VictoryDef);

    FCharacterAuraDef EntranceDef;
    EntranceDef.Color = FLinearColor(1.0f, 1.0f, 1.0f);
    EntranceDef.Intensity = 0.8f;
    EntranceDef.Radius = 120.0f;
    EntranceDef.bPulsating = false;
    EntranceDef.PulseSpeed = 0.0f;
    AuraDefinitions.Add(ECharacterAuraType::Entrance, EntranceDef);

    TMap<EFightingStyle, FLinearColor> StylePowerColors;
    StylePowerColors.Add(EFightingStyle::Karate, FLinearColor(0.2f, 0.6f, 1.0f));
    StylePowerColors.Add(EFightingStyle::MuayThai, FLinearColor(1.0f, 0.2f, 0.1f));
    StylePowerColors.Add(EFightingStyle::Boxing, FLinearColor(1.0f, 0.6f, 0.0f));
    StylePowerColors.Add(EFightingStyle::Wushu, FLinearColor(0.1f, 1.0f, 0.3f));
}

void ULesFightCharacterAuraSystem::ActivateAura(ECharacterAuraType Type, AActor* Character)
{
    if (!Character || !AuraDefinitions.Contains(Type))
    {
        return;
    }

    ActiveAuras.Add(Type, true);
    AuraTimers.Add(Type, 0.0f);

    const FCharacterAuraDef& Def = AuraDefinitions[Type];

    UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
        nullptr,
        Character->GetRootComponent(),
        NAME_None,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::SnapToTarget,
        true
    );

    if (NiagaraComp)
    {
        NiagaraComp->SetVariableLinearColor(TEXT("AuraColor"), Def.Color);
        NiagaraComp->SetVariableFloat(TEXT("AuraIntensity"), Def.Intensity * GlobalAuraIntensity);
        NiagaraComp->SetVariableFloat(TEXT("AuraRadius"), Def.Radius);
        NiagaraComp->SetVariableBool(TEXT("bPulsating"), Def.bPulsating);
        NiagaraComp->SetVariableFloat(TEXT("PulseSpeed"), Def.PulseSpeed);
    }

    OnAuraActivated.Broadcast(Type);
}

void ULesFightCharacterAuraSystem::DeactivateAura(ECharacterAuraType Type)
{
    if (!ActiveAuras.Contains(Type) || !ActiveAuras[Type])
    {
        return;
    }

    ActiveAuras[Type] = false;
    ActiveAuras.Remove(Type);
    AuraTimers.Remove(Type);

    OnAuraDeactivated.Broadcast(Type);
}

void ULesFightCharacterAuraSystem::DeactivateAllAuras()
{
    TArray<ECharacterAuraType> ActiveTypes;
    ActiveAuras.GenerateKeyArray(ActiveTypes);

    for (ECharacterAuraType Type : ActiveTypes)
    {
        DeactivateAura(Type);
    }
}

void ULesFightCharacterAuraSystem::UpdateAuras(float DeltaTime)
{
    for (TPair<ECharacterAuraType, bool>& Pair : ActiveAuras)
    {
        if (!Pair.Value)
        {
            continue;
        }

        ECharacterAuraType Type = Pair.Key;
        float& Timer = AuraTimers.FindOrAdd(Type);
        Timer += DeltaTime;

        if (AuraDefinitions.Contains(Type))
        {
            const FCharacterAuraDef& Def = AuraDefinitions[Type];
            if (Def.bPulsating)
            {
                float PulseAlpha = FMath::Sin(Timer * Def.PulseSpeed * PI * 2.0f) * 0.5f + 0.5f;
                float FinalIntensity = Def.Intensity * GlobalAuraIntensity * (0.7f + 0.3f * PulseAlpha);
            }
        }
    }
}

TArray<ECharacterAuraType> ULesFightCharacterAuraSystem::GetActiveAuraTypes() const
{
    TArray<ECharacterAuraType> Result;
    for (const TPair<ECharacterAuraType, bool>& Pair : ActiveAuras)
    {
        if (Pair.Value)
        {
            Result.Add(Pair.Key);
        }
    }
    return Result;
}

bool ULesFightCharacterAuraSystem::IsAuraActive(ECharacterAuraType Type) const
{
    const bool* bActive = ActiveAuras.Find(Type);
    return bActive && *bActive;
}

void ULesFightCharacterAuraSystem::SetAuraColor(FLinearColor Color)
{
    for (TPair<ECharacterAuraType, FCharacterAuraDef>& Pair : AuraDefinitions)
    {
        Pair.Value.Color = Color;
    }
}

void ULesFightCharacterAuraSystem::SetAuraIntensity(float Intensity)
{
    GlobalAuraIntensity = FMath::Clamp(Intensity, 0.0f, 2.0f);
}

void ULesFightCharacterAuraSystem::SetAuraPulse(bool bPulsating, float Speed)
{
    for (TPair<ECharacterAuraType, FCharacterAuraDef>& Pair : AuraDefinitions)
    {
        Pair.Value.bPulsating = bPulsating;
        Pair.Value.PulseSpeed = Speed;
    }
}
