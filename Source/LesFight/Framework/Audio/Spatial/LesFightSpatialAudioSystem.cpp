#include "LesFightSpatialAudioSystem.h"

ULesFightSpatialAudioSystem::ULesFightSpatialAudioSystem()
{
}

void ULesFightSpatialAudioSystem::SetSoundSpatialization(FName SoundName, bool bEnable3D)
{
}

void ULesFightSpatialAudioSystem::SetAttenuation(FName SoundName, float MinDist, float MaxDist)
{
    DefaultMinDist = MinDist;
    DefaultMaxDist = MaxDist;
}

void ULesFightSpatialAudioSystem::SetSpatialBlend(FName SoundName, float Blend3D)
{
}

void ULesFightSpatialAudioSystem::UpdateListenerPosition(FVector Position, FVector Forward, FVector Up)
{
    ListenerPosition = Position;
    ListenerForward = Forward;
}

float ULesFightSpatialAudioSystem::CalculateOcclusion(FVector ListenerPos, FVector SoundPos) const
{
    FVector Direction = SoundPos - ListenerPos;
    float Distance = Direction.Size();
    if (Distance <= 0.0f)
    {
        return 0.0f;
    }

    FVector DirectionNormal = Direction / Distance;
    float DotProduct = FVector::DotProduct(DirectionNormal, ListenerForward);
    float Occlusion = FMath::GetMappedRangeValueClamped(
        FVector2D(-1.0f, 1.0f),
        FVector2D(0.8f, 0.0f),
        DotProduct
    );
    Occlusion = FMath::Clamp(Occlusion + (Distance / DefaultMaxDist) * 0.2f, 0.0f, 1.0f);

    return Occlusion;
}

float ULesFightSpatialAudioSystem::GetOcclusionValue() const
{
    return OcclusionValue;
}

void ULesFightSpatialAudioSystem::EnableDoppler(bool bEnabled)
{
    bDopplerEnabled = bEnabled;
}

int32 ULesFightSpatialAudioSystem::GetSpatialQuality() const
{
    return SpatialQuality;
}
