#include "LesFightReverbZoneSystem.h"

ULesFightReverbZoneSystem::ULesFightReverbZoneSystem()
{
    FReverbZoneData SmallRoom;
    SmallRoom.ZoneName = TEXT("SmallRoom");
    SmallRoom.Preset = EReverbPreset::SmallRoom;
    SmallRoom.WetLevel = 0.3f;
    SmallRoom.DecayTime = 0.5f;
    SmallRoom.PreDelay = 10.0f;
    SmallRoom.bEnabled = true;

    FReverbZoneData MediumRoom;
    MediumRoom.ZoneName = TEXT("MediumRoom");
    MediumRoom.Preset = EReverbPreset::MediumRoom;
    MediumRoom.WetLevel = 0.5f;
    MediumRoom.DecayTime = 1.0f;
    MediumRoom.PreDelay = 15.0f;
    MediumRoom.bEnabled = true;

    FReverbZoneData LargeRoom;
    LargeRoom.ZoneName = TEXT("LargeRoom");
    LargeRoom.Preset = EReverbPreset::LargeRoom;
    LargeRoom.WetLevel = 0.6f;
    LargeRoom.DecayTime = 1.8f;
    LargeRoom.PreDelay = 20.0f;
    LargeRoom.bEnabled = true;

    FReverbZoneData Cathedral;
    Cathedral.ZoneName = TEXT("Cathedral");
    Cathedral.Preset = EReverbPreset::Cathedral;
    Cathedral.WetLevel = 0.8f;
    Cathedral.DecayTime = 4.0f;
    Cathedral.PreDelay = 30.0f;
    Cathedral.bEnabled = true;

    FReverbZoneData Arena;
    Arena.ZoneName = TEXT("Arena");
    Arena.Preset = EReverbPreset::Arena;
    Arena.WetLevel = 0.6f;
    Arena.DecayTime = 2.5f;
    Arena.PreDelay = 25.0f;
    Arena.bEnabled = true;

    FReverbZoneData Outdoor;
    Outdoor.ZoneName = TEXT("Outdoor");
    Outdoor.Preset = EReverbPreset::Outdoor;
    Outdoor.WetLevel = 0.2f;
    Outdoor.DecayTime = 0.8f;
    Outdoor.PreDelay = 5.0f;
    Outdoor.bEnabled = true;

    FReverbZoneData Underground;
    Underground.ZoneName = TEXT("Underground");
    Underground.Preset = EReverbPreset::Underground;
    Underground.WetLevel = 0.7f;
    Underground.DecayTime = 3.0f;
    Underground.PreDelay = 20.0f;
    Underground.bEnabled = true;

    FReverbZoneData NonePreset;
    NonePreset.ZoneName = TEXT("None");
    NonePreset.Preset = EReverbPreset::None;
    NonePreset.WetLevel = 0.0f;
    NonePreset.DecayTime = 0.0f;
    NonePreset.PreDelay = 0.0f;
    NonePreset.bEnabled = false;

    CurrentReverb = NonePreset;
}

void ULesFightReverbZoneSystem::RegisterReverbZone(const FReverbZoneData& Zone)
{
    ReverbZones.Add(Zone);
}

void ULesFightReverbZoneSystem::RemoveReverbZone(FName ZoneName)
{
    for (int32 i = 0; i < ReverbZones.Num(); ++i)
    {
        if (ReverbZones[i].ZoneName == ZoneName)
        {
            ReverbZones.RemoveAt(i);
            return;
        }
    }
}

void ULesFightReverbZoneSystem::UpdateListenerReverb(FVector ListenerPosition)
{
    FName PreviousZoneName = CurrentZoneName;

    for (const FReverbZoneData& Zone : ReverbZones)
    {
        if (!Zone.bEnabled)
        {
            continue;
        }

        float Distance = FVector::Dist(ListenerPosition, Zone.ZoneCenter);
        if (Distance <= Zone.ZoneRadius)
        {
            if (CurrentZoneName != Zone.ZoneName)
            {
                if (bInZone)
                {
                    OnReverbZoneExited.Broadcast(CurrentZoneName);
                }
                CurrentZoneName = Zone.ZoneName;
                CurrentReverb = Zone;
                bInZone = true;
                OnReverbZoneEntered.Broadcast(CurrentZoneName);
            }
            return;
        }
    }

    if (bInZone)
    {
        OnReverbZoneExited.Broadcast(CurrentZoneName);
        CurrentZoneName = NAME_None;
        bInZone = false;
    }
}

FReverbZoneData ULesFightReverbZoneSystem::GetCurrentReverbData() const
{
    return CurrentReverb;
}

EReverbPreset ULesFightReverbZoneSystem::GetCurrentReverbPreset() const
{
    if (bInZone)
    {
        return CurrentReverb.Preset;
    }
    return GlobalReverb;
}

void ULesFightReverbZoneSystem::SetGlobalReverb(EReverbPreset Preset)
{
    GlobalReverb = Preset;
}

void ULesFightReverbZoneSystem::ClearAllZones()
{
    ReverbZones.Empty();
    CurrentZoneName = NAME_None;
    CurrentReverb = FReverbZoneData();
    bInZone = false;
}

FReverbZoneData ULesFightReverbZoneSystem::GetReverbZoneAtLocation(FVector Location) const
{
    for (const FReverbZoneData& Zone : ReverbZones)
    {
        if (!Zone.bEnabled)
        {
            continue;
        }
        float Distance = FVector::Dist(Location, Zone.ZoneCenter);
        if (Distance <= Zone.ZoneRadius)
        {
            return Zone;
        }
    }
    return FReverbZoneData();
}
