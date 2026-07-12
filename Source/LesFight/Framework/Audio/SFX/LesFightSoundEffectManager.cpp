#include "LesFightSoundEffectManager.h"
#include "Framework/Audio/Data/LesFightAudioData.h"

ULesFightSoundEffectManager::ULesFightSoundEffectManager()
{
    CombatSounds.Emplace(ECombatSoundType::LightPunch, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/LightPunch_01", "/Game/Audio/SFX/LightPunch_02", "/Game/Audio/SFX/LightPunch_03"},
        0.8f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::HeavyPunch, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/HeavyPunch_01", "/Game/Audio/SFX/HeavyPunch_02", "/Game/Audio/SFX/HeavyPunch_03"},
        1.0f, 0.05f
    });
    CombatSounds.Emplace(ECombatSoundType::LightKick, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/LightKick_01", "/Game/Audio/SFX/LightKick_02"},
        0.8f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::HeavyKick, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/HeavyKick_01", "/Game/Audio/SFX/HeavyKick_02"},
        1.0f, 0.05f
    });
    CombatSounds.Emplace(ECombatSoundType::SpecialAttack, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/SpecialAttack_01", "/Game/Audio/SFX/SpecialAttack_02"},
        1.2f, 0.05f
    });
    CombatSounds.Emplace(ECombatSoundType::UltimateAttack, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/UltimateAttack_01"},
        1.5f, 0.05f
    });
    CombatSounds.Emplace(ECombatSoundType::BodyImpact, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/BodyImpact_01", "/Game/Audio/SFX/BodyImpact_02"},
        1.0f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::BlockImpact, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/BlockImpact_01", "/Game/Audio/SFX/BlockImpact_02"},
        0.6f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::GroundImpact, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/GroundImpact_01", "/Game/Audio/SFX/GroundImpact_02"},
        1.0f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::WallImpact, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/WallImpact_01", "/Game/Audio/SFX/WallImpact_02"},
        1.0f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::CounterImpact, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/CounterImpact_01", "/Game/Audio/SFX/CounterImpact_02"},
        1.1f, 0.08f
    });
    CombatSounds.Emplace(ECombatSoundType::Knockdown, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Knockdown_01", "/Game/Audio/SFX/Knockdown_02"},
        1.0f, 0.1f
    });
    CombatSounds.Emplace(ECombatSoundType::GetUp, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/GetUp_01", "/Game/Audio/SFX/GetUp_02"},
        0.9f, 0.1f
    });

    MovementSounds.Emplace(EMovementSoundType::Footstep, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Footstep_01", "/Game/Audio/SFX/Footstep_02", "/Game/Audio/SFX/Footstep_03"},
        0.7f, 0.15f
    });
    MovementSounds.Emplace(EMovementSoundType::Slide, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Slide_01", "/Game/Audio/SFX/Slide_02"},
        0.8f, 0.1f
    });
    MovementSounds.Emplace(EMovementSoundType::Dodge, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Dodge_01", "/Game/Audio/SFX/Dodge_02"},
        0.9f, 0.1f
    });
    MovementSounds.Emplace(EMovementSoundType::Landing, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Landing_01", "/Game/Audio/SFX/Landing_02"},
        1.0f, 0.1f
    });
    MovementSounds.Emplace(EMovementSoundType::Jump, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Jump_01"},
        0.7f, 0.1f
    });
    MovementSounds.Emplace(EMovementSoundType::Run, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Run_01", "/Game/Audio/SFX/Run_02"},
        0.8f, 0.15f
    });
    MovementSounds.Emplace(EMovementSoundType::Dash, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Dash_01", "/Game/Audio/SFX/Dash_02"},
        0.9f, 0.1f
    });
    MovementSounds.Emplace(EMovementSoundType::Backstep, FCombatSoundDef{
        TArray<FString>{"/Game/Audio/SFX/Backstep_01"},
        0.8f, 0.1f
    });
}

void ULesFightSoundEffectManager::PlayCombatSound(ECombatSoundType Type, FVector Location, float VolumeMod)
{
    if (ActiveSounds.Num() >= SFXPoolSize)
    {
        return;
    }

    FCombatSoundDef* Def = CombatSounds.Find(Type);
    if (Def == nullptr || Def->MetaSoundVariations.Num() == 0)
    {
        return;
    }

    int32 Index = FMath::RandRange(0, Def->MetaSoundVariations.Num() - 1);
    FName SoundName = FName(*Def->MetaSoundVariations[Index]);

    ActiveSounds.Add(SoundName);
    int32& Count = SoundUsageCount.FindOrAdd(SoundName);
    Count++;

    if (OwnerManager.IsValid())
    {
        OwnerManager->PlaySoundAtLocation(SoundName, Location, Def->BaseVolume * VolumeMod, Def->PitchVariation);
    }
}

void ULesFightSoundEffectManager::PlayMovementSound(EMovementSoundType Type, FVector Location, float VolumeMod)
{
    if (ActiveSounds.Num() >= SFXPoolSize)
    {
        return;
    }

    FCombatSoundDef* Def = MovementSounds.Find(Type);
    if (Def == nullptr || Def->MetaSoundVariations.Num() == 0)
    {
        return;
    }

    int32 Index = FMath::RandRange(0, Def->MetaSoundVariations.Num() - 1);
    FName SoundName = FName(*Def->MetaSoundVariations[Index]);

    ActiveSounds.Add(SoundName);
    int32& Count = SoundUsageCount.FindOrAdd(SoundName);
    Count++;

    if (OwnerManager.IsValid())
    {
        OwnerManager->PlaySoundAtLocation(SoundName, Location, Def->BaseVolume * VolumeMod, Def->PitchVariation);
    }
}

void ULesFightSoundEffectManager::PreloadSoundBank(FName BankName)
{
    if (OwnerManager.IsValid())
    {
        OwnerManager->PreloadBank(BankName);
    }
}

int32 ULesFightSoundEffectManager::GetActiveSFXCount() const
{
    return ActiveSounds.Num();
}

void ULesFightSoundEffectManager::SetSFXPoolSize(int32 Size)
{
    SFXPoolSize = Size;
}

void ULesFightSoundEffectManager::StopAllSFX()
{
    if (OwnerManager.IsValid())
    {
        OwnerManager->StopAllSFX();
    }
    ActiveSounds.Empty();
    SoundUsageCount.Empty();
}

bool ULesFightSoundEffectManager::IsSoundPlaying(FName SoundName) const
{
    return ActiveSounds.Contains(SoundName);
}
