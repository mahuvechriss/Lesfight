#include "Framework/Audio/Effects/LesFightAudioEffectsProcessor.h"

void ULesFightAudioEffectsProcessor::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bLowPassActive = false;
    bHighPassActive = false;
    ActiveEffects.Empty();
    EffectParameters.Empty();
    CurrentReverb = FReverbZoneData();
}

void ULesFightAudioEffectsProcessor::ApplyReverb(FReverbZoneData ReverbData)
{
    CurrentReverb = ReverbData;
    CurrentReverb.bEnabled = true;
    ActiveEffects.Add(TEXT("Reverb"), true);
}

void ULesFightAudioEffectsProcessor::RemoveReverb()
{
    CurrentReverb.bEnabled = false;
    ActiveEffects.Add(TEXT("Reverb"), false);
}

void ULesFightAudioEffectsProcessor::ApplyLowPassFilter(float CutoffFrequency)
{
    bLowPassActive = true;
    EffectParameters.Add(TEXT("LowPassCutoff"), CutoffFrequency);
    ActiveEffects.Add(TEXT("LowPassFilter"), true);
}

void ULesFightAudioEffectsProcessor::RemoveLowPassFilter()
{
    bLowPassActive = false;
    ActiveEffects.Add(TEXT("LowPassFilter"), false);
}

void ULesFightAudioEffectsProcessor::ApplyHighPassFilter(float CutoffFrequency)
{
    bHighPassActive = true;
    EffectParameters.Add(TEXT("HighPassCutoff"), CutoffFrequency);
    ActiveEffects.Add(TEXT("HighPassFilter"), true);
}

void ULesFightAudioEffectsProcessor::RemoveHighPassFilter()
{
    bHighPassActive = false;
    ActiveEffects.Add(TEXT("HighPassFilter"), false);
}

void ULesFightAudioEffectsProcessor::ApplyEQ(float LowGain, float MidGain, float HighGain)
{
    EffectParameters.Add(TEXT("EQLowGain"), LowGain);
    EffectParameters.Add(TEXT("EQMidGain"), MidGain);
    EffectParameters.Add(TEXT("EQHighGain"), HighGain);
    ActiveEffects.Add(TEXT("EQ"), true);
}

void ULesFightAudioEffectsProcessor::ApplyCompression(float Threshold, float Ratio, float Attack, float Release)
{
    EffectParameters.Add(TEXT("CompressionThreshold"), Threshold);
    EffectParameters.Add(TEXT("CompressionRatio"), Ratio);
    EffectParameters.Add(TEXT("CompressionAttack"), Attack);
    EffectParameters.Add(TEXT("CompressionRelease"), Release);
    ActiveEffects.Add(TEXT("Compression"), true);
}

void ULesFightAudioEffectsProcessor::SetEnvironmentalFilter(EArenaType ArenaType)
{
    switch (ArenaType)
    {
    case EArenaType::BambooForest:
    case EArenaType::FloatingIslands:
    case EArenaType::MysticForest:
    case EArenaType::DragonValley:
        ApplyEQ(0.0f, 2.0f, 3.0f);
        break;
    case EArenaType::UndergroundArena:
    case EArenaType::IndustrialFactory:
    case EArenaType::AbandonedBuilding:
        ApplyEQ(3.0f, 0.0f, -2.0f);
        ApplyReverb(FReverbZoneData());
        break;
    case EArenaType::TempleCourtyard:
    case EArenaType::MountainDojo:
    case EArenaType::AncientRuins:
        ApplyEQ(1.0f, 1.0f, 1.0f);
        break;
    default:
        ApplyEQ(0.0f, 0.0f, 0.0f);
        break;
    }
}

void ULesFightAudioEffectsProcessor::ClearAllEffects()
{
    ActiveEffects.Empty();
    EffectParameters.Empty();
    bLowPassActive = false;
    bHighPassActive = false;
    CurrentReverb.bEnabled = false;
}

bool ULesFightAudioEffectsProcessor::IsEffectActive(FName EffectName) const
{
    const bool* bActive = ActiveEffects.Find(EffectName);
    return bActive && *bActive;
}
