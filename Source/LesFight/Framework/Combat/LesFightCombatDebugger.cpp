#include "LesFightCombatDebugger.h"
#include "LesFightCombatComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightCombatDebugger::ULesFightCombatDebugger()
    : ComboWindowMultiplier(1.0f)
    , bDebugMode(false)
    , bShowHitboxes(false)
    , bShowHurtboxes(false)
    , bShowFrameData(false)
    , bShowComboDebug(false)
    , bShowDamageLog(false)
    , bShowInputHistory(false)
    , bGodMode(false)
    , bInfiniteMeter(false)
    , bInfiniteHealth(false)
{
}

void ULesFightCombatDebugger::Initialize()
{
}

void ULesFightCombatDebugger::RegisterCombatComponent(ULesFightCombatComponent* CombatComp)
{
    if (CombatComp)
    {
        RegisteredComponents.AddUnique(CombatComp);
    }
}

void ULesFightCombatDebugger::LogDamageEvent(AActor* Target, float Damage, FName AttackID)
{
    if (!bShowDamageLog || !bDebugMode) return;

    FString LogEntry = FString::Printf(TEXT("[DAMAGE] %s -> %s: %.1f (Attack: %s)"),
        Target ? *Target->GetName() : TEXT("Unknown"),
        Target ? *Target->GetName() : TEXT("Unknown"),
        Damage, *AttackID.ToString());

    DebugLog.Add(LogEntry);

    if (DebugLog.Num() > 100)
    {
        DebugLog.RemoveAt(0);
    }
}

void ULesFightCombatDebugger::LogFrameData(const FCombatDebugFrameData& FrameData)
{
    if (!bShowFrameData || !bDebugMode) return;

    OnDebugFrameUpdated.Broadcast(FrameData);
}

void ULesFightCombatDebugger::LogString(const FString& Message, FColor Color)
{
    if (!bDebugMode) return;

    DebugLog.Add(Message);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, Message);
    }
}

void ULesFightCombatDebugger::ClearLog()
{
    DebugLog.Empty();
}

void ULesFightCombatDebugger::ToggleDebugDisplay()
{
    bDebugMode = !bDebugMode;
    UE_LOG(LogLesFight, Log, TEXT("Combat debugger: %s"),
        bDebugMode ? TEXT("ENABLED") : TEXT("DISABLED"));
}

void ULesFightCombatDebugger::SpawnDebugFighter(TSubclassOf<ALesFightBaseFighter> FighterClass,
    FVector Location)
{
    if (!FighterClass) return;

    FActorSpawnParameters SpawnParams;
    ALesFightBaseFighter* NewFighter = GetWorld()->SpawnActor<ALesFightBaseFighter>(
        FighterClass, Location, FRotator::ZeroRotator, SpawnParams);

    if (NewFighter)
    {
        UE_LOG(LogLesFight, Log, TEXT("Debug fighter spawned: %s"), *NewFighter->GetName());
    }
}

void ULesFightCombatDebugger::ExecuteAttackByName(FName AttackID)
{
    for (ULesFightCombatComponent* Comp : RegisteredComponents)
    {
        if (Comp)
        {
            Comp->ExecuteAttackByID(AttackID);
            break;
        }
    }
}

void ULesFightCombatDebugger::DrawDebugOverlay(UWorld* World)
{
    if (!World) return;

    FString DebugInfo = FString::Printf(TEXT(
        "=== COMBAT DEBUG ===\n"
        "God Mode: %s | Inf Health: %s | Inf Meter: %s\n"
        "Hitboxes: %s | Hurtboxes: %s | Frame Data: %s\n"
        "Combo Debug: %s | Damage Log: %s | Input: %s\n"
        "Combo Window: %.2f\n"
        "Log Entries: %d"),
        bGodMode ? TEXT("ON") : TEXT("OFF"),
        bInfiniteHealth ? TEXT("ON") : TEXT("OFF"),
        bInfiniteMeter ? TEXT("ON") : TEXT("OFF"),
        bShowHitboxes ? TEXT("ON") : TEXT("OFF"),
        bShowHurtboxes ? TEXT("ON") : TEXT("OFF"),
        bShowFrameData ? TEXT("ON") : TEXT("OFF"),
        bShowComboDebug ? TEXT("ON") : TEXT("OFF"),
        bShowDamageLog ? TEXT("ON") : TEXT("OFF"),
        bShowInputHistory ? TEXT("ON") : TEXT("OFF"),
        ComboWindowMultiplier,
        DebugLog.Num());

    GEngine->AddOnScreenDebugMessage(999, 0.0f, FColor::Cyan, DebugInfo, true, FVector2D(1.2f, 1.2f));
}
