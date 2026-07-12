#include "LesFightCinematicEffectManager.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "Framework/VFX/World/LesFightVFXWorldManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

void ULesFightCinematicEffectManager::Initialize(ULesFightVFXWorldManager* InManager)
{
    OwnerManager = InManager;

    CinematicEffectPaths.Empty();

    CinematicEffectPaths.Add(ECinematicVFXEvent::RoundStart, { TEXT("CameraSwoop"), TEXT("FlashEffect") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::RoundEnd, { TEXT("SlowMotionEffect"), TEXT("DramaticLighting") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::UltimateStart, { TEXT("AuraBurst"), TEXT("CameraZoom") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::UltimateHit, { TEXT("Shockwave"), TEXT("ScreenShake") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::FinisherStart, { TEXT("DramaticPause"), TEXT("FocusLight") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::FinisherHit, { TEXT("ImpactBurst"), TEXT("Debris") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::Victory, { TEXT("GoldenGlow"), TEXT("VictoryParticles") });
    CinematicEffectPaths.Add(ECinematicVFXEvent::Defeat, { TEXT("Desaturated"), TEXT("FadeOut") });
}

void ULesFightCinematicEffectManager::PlayCinematicEvent(ECinematicVFXEvent Event, FVector Location, AActor* Character)
{
    if (!bCinematicMode)
    {
        return;
    }

    if (CinematicEffectPaths.Contains(Event))
    {
        TArray<FString> EffectPaths = CinematicEffectPaths[Event];
        for (const FString& Path : EffectPaths)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                nullptr,
                Location,
                FRotator::ZeroRotator,
                FVector::OneVector,
                true
            );
        }
    }

    OnCinematicVFXEvent.Broadcast(Event);
}

void ULesFightCinematicEffectManager::PlayRoundStart(FVector Location)
{
    bCinematicMode = true;
    PlayCinematicEvent(ECinematicVFXEvent::RoundStart, Location, nullptr);
}

void ULesFightCinematicEffectManager::PlayRoundEnd(FVector Location, AActor* Winner)
{
    PlayCinematicEvent(ECinematicVFXEvent::RoundEnd, Location, Winner);
}

void ULesFightCinematicEffectManager::PlayUltimateSequence(AActor* Attacker, AActor* Target)
{
    if (!Attacker || !Target)
    {
        return;
    }

    bCinematicMode = true;

    PlayCinematicEvent(ECinematicVFXEvent::UltimateStart, Attacker->GetActorLocation(), Attacker);

    PlayCinematicEvent(ECinematicVFXEvent::UltimateHit, Target->GetActorLocation(), Target);

    bCinematicMode = false;
}

void ULesFightCinematicEffectManager::PlayFinisherSequence(AActor* Attacker, AActor* Target)
{
    if (!Attacker || !Target)
    {
        return;
    }

    bCinematicMode = true;

    PlayCinematicEvent(ECinematicVFXEvent::FinisherStart, Attacker->GetActorLocation(), Attacker);

    PlayCinematicEvent(ECinematicVFXEvent::FinisherHit, Target->GetActorLocation(), Target);

    bCinematicMode = false;
}

void ULesFightCinematicEffectManager::PlayVictoryEffect(AActor* Winner)
{
    if (!Winner)
    {
        return;
    }

    PlayCinematicEvent(ECinematicVFXEvent::Victory, Winner->GetActorLocation(), Winner);
}

void ULesFightCinematicEffectManager::SetCinematicMode(bool bEnabled)
{
    bCinematicMode = bEnabled;
}

bool ULesFightCinematicEffectManager::IsCinematicMode() const
{
    return bCinematicMode;
}

UWorld* ULesFightCinematicEffectManager::GetWorld() const
{
    if (OwnerManager.IsValid())
    {
        return OwnerManager->GetWorld();
    }
    return nullptr;
}
