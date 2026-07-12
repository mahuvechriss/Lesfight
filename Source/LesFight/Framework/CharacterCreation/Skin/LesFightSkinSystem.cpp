#include "LesFightSkinSystem.h"
#include "LesFightCharCreationManager.h"

ULesFightSkinSystem::ULesFightSkinSystem()
    : MaxTattoos(10)
{
    CurrentSkinData.SkinTone = FLinearColor(0.9f, 0.7f, 0.5f);
    CurrentSkinData.SkinDetail = ESkinDetail::Smooth;
    CurrentSkinData.Glossiness = 0.3f;

    PresetSkinTones = {
        FLinearColor(0.9f, 0.7f, 0.5f),
        FLinearColor(0.5f, 0.3f, 0.2f),
        FLinearColor(1.0f, 0.9f, 0.8f),
        FLinearColor(0.8f, 0.6f, 0.4f),
        FLinearColor(0.6f, 0.4f, 0.3f),
    };
}

void ULesFightSkinSystem::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightSkinSystem::SetSkinTone(FLinearColor Tone)
{
    CurrentSkinData.SkinTone = Tone;
}

FLinearColor ULesFightSkinSystem::GetSkinTone() const
{
    return CurrentSkinData.SkinTone;
}

void ULesFightSkinSystem::SetSkinDetail(ESkinDetail Detail)
{
    CurrentSkinData.SkinDetail = Detail;
}

ESkinDetail ULesFightSkinSystem::GetSkinDetail() const
{
    return CurrentSkinData.SkinDetail;
}

void ULesFightSkinSystem::SetGlossiness(float Gloss)
{
    CurrentSkinData.Glossiness = FMath::Clamp(Gloss, 0.0f, 1.0f);
}

float ULesFightSkinSystem::GetGlossiness() const
{
    return CurrentSkinData.Glossiness;
}

void ULesFightSkinSystem::AddTattoo(const FTattooEntry& Tattoo)
{
    if (Tattoos.Num() < MaxTattoos)
    {
        Tattoos.Add(Tattoo);
    }
}

bool ULesFightSkinSystem::RemoveTattoo(const FName& TattooID)
{
    int32 Removed = Tattoos.RemoveAll(
        [&](const FTattooEntry& T) { return T.TattooID == TattooID; });
    return Removed > 0;
}

TArray<FTattooEntry> ULesFightSkinSystem::GetAllTattoos() const
{
    return Tattoos;
}

void ULesFightSkinSystem::ClearTattoos()
{
    Tattoos.Empty();
}

void ULesFightSkinSystem::SetScarification(float Intensity)
{
    CurrentSkinData.ScarIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);
}

float ULesFightSkinSystem::GetScarification() const
{
    return CurrentSkinData.ScarIntensity;
}

void ULesFightSkinSystem::SetCustomizationData(const FSkinCustomizationData& Data)
{
    CurrentSkinData = Data;
}

FSkinCustomizationData ULesFightSkinSystem::GetCustomizationData() const
{
    FSkinCustomizationData Data = CurrentSkinData;
    Data.Tattoos = Tattoos;
    return Data;
}

void ULesFightSkinSystem::ApplyToCharacter(AActor* CharacterActor)
{
}

void ULesFightSkinSystem::ResetToDefault()
{
    CurrentSkinData.SkinTone = FLinearColor(0.9f, 0.7f, 0.5f);
    CurrentSkinData.SkinDetail = ESkinDetail::Smooth;
    CurrentSkinData.Glossiness = 0.3f;
    CurrentSkinData.ScarIntensity = 0.0f;
    Tattoos.Empty();
}
