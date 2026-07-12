#include "LesFightMartialArtsDevTools.h"
#include "LesFightMartialArtsManager.h"
#include "Styles/LesFightStyleManager.h"
#include "Styles/LesFightFightingStyle.h"
#include "Stances/LesFightStanceSystem.h"

ULesFightMartialArtsDevTools::ULesFightMartialArtsDevTools()
    : bDebugMode(false)
    , bInfiniteStamina(false)
    , bOneHitKO(false)
    , bShowOverlay(false)
    , MaxLogEntries(100)
{
}

void ULesFightMartialArtsDevTools::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    DebugLog.Empty();
}

void ULesFightMartialArtsDevTools::Tick(float DeltaTime)
{
}

void ULesFightMartialArtsDevTools::SwitchFightingStyle(EFightingStyle Style)
{
    if (!OwnerManager.IsValid()) return;

    ULesFightStyleManager* StyleMgr = OwnerManager->GetStyleManager();
    if (StyleMgr && StyleMgr->EquipStyle(Style))
    {
        FString Result = FString::Printf(TEXT("Switched to style: %s"),
            *UEnum::GetValueAsString(Style));
        AddToLog(Result);
        BroadcastResult(FName(TEXT("SwitchStyle")), Result);
    }
}

void ULesFightMartialArtsDevTools::DisplayActiveStance()
{
    if (!OwnerManager.IsValid()) return;

    ULesFightStanceSystem* StanceSys = OwnerManager->GetStanceSystem();
    if (StanceSys)
    {
        FString Result = FString::Printf(TEXT("Active Stance: %s"),
            *UEnum::GetValueAsString(StanceSys->GetCurrentStance()));
        AddToLog(Result);
        BroadcastResult(FName(TEXT("StanceDisplay")), Result);
    }
}

void ULesFightMartialArtsDevTools::TestComboPath(const TArray<FName>& ComboSequence)
{
    FString ComboStr;
    for (FName Step : ComboSequence)
    {
        ComboStr += Step.ToString() + TEXT(" -> ");
    }
    AddToLog(FString::Printf(TEXT("Testing combo: %s"), *ComboStr));
    BroadcastResult(FName(TEXT("ComboTest")), ComboStr);
}

void ULesFightMartialArtsDevTools::VisualizeCounterWindows()
{
    AddToLog(TEXT("Counter windows visualization active"));
}

void ULesFightMartialArtsDevTools::InspectMotionMatching()
{
    AddToLog(TEXT("Motion matching inspection active"));
}

void ULesFightMartialArtsDevTools::MonitorAnimationTiming()
{
    AddToLog(TEXT("Animation timing monitor active"));
}

void ULesFightMartialArtsDevTools::SetDebugMode(bool bEnabled)
{
    bDebugMode = bEnabled;
    AddToLog(FString::Printf(TEXT("Debug mode: %s"), bEnabled ? TEXT("ON") : TEXT("OFF")));
}

void ULesFightMartialArtsDevTools::ToggleDebugOverlay()
{
    bShowOverlay = !bShowOverlay;
    AddToLog(FString::Printf(TEXT("Debug overlay: %s"), bShowOverlay ? TEXT("VISIBLE") : TEXT("HIDDEN")));
}

void ULesFightMartialArtsDevTools::LogAllStyles()
{
    if (!OwnerManager.IsValid()) return;

    ULesFightStyleManager* StyleMgr = OwnerManager->GetStyleManager();
    if (!StyleMgr) return;

    TArray<EFightingStyle> Styles = StyleMgr->GetAllAvailableStyles();
    for (EFightingStyle Style : Styles)
    {
        ULesFightFightingStyle* StyleObj = StyleMgr->GetStyle(Style);
        if (StyleObj)
        {
            FStyleAttributes Attr = StyleObj->GetAttributes();
            AddToLog(FString::Printf(TEXT("Style: %s (Dmg:%.2f Spd:%.2f Def:%.2f)"),
                *UEnum::GetValueAsString(Style),
                Attr.BaseDamageMultiplier,
                Attr.BaseSpeedMultiplier,
                Attr.BaseDefenseMultiplier));
        }
    }
}

void ULesFightMartialArtsDevTools::LogStanceData()
{
    if (!OwnerManager.IsValid()) return;

    ULesFightStanceSystem* StanceSys = OwnerManager->GetStanceSystem();
    if (!StanceSys) return;

    FStanceAttributes Attr = StanceSys->GetCurrentStanceAttributes();
    AddToLog(FString::Printf(TEXT("Stance: %s (Dmg:%.2f Spd:%.2f Def:%.2f Regen:%.2f)"),
        *UEnum::GetValueAsString(StanceSys->GetCurrentStance()),
        Attr.DamageModifier, Attr.SpeedModifier,
        Attr.DefenseModifier, Attr.StaminaRegenModifier));
}

void ULesFightMartialArtsDevTools::SimulatePerfectCounter()
{
    AddToLog(TEXT("Perfect counter simulated"));
    BroadcastResult(FName(TEXT("PerfectCounter")), TEXT("Simulated"));
}

void ULesFightMartialArtsDevTools::SimulatePerfectDodge()
{
    AddToLog(TEXT("Perfect dodge simulated"));
    BroadcastResult(FName(TEXT("PerfectDodge")), TEXT("Simulated"));
}

void ULesFightMartialArtsDevTools::SetInfiniteStamina(bool bInfinite)
{
    bInfiniteStamina = bInfinite;
    AddToLog(FString::Printf(TEXT("Infinite stamina: %s"), bInfinite ? TEXT("ON") : TEXT("OFF")));
}

void ULesFightMartialArtsDevTools::SetOneHitKO(bool bOneHit)
{
    bOneHitKO = bOneHit;
    AddToLog(FString::Printf(TEXT("One-hit KO: %s"), bOneHit ? TEXT("ON") : TEXT("OFF")));
}

void ULesFightMartialArtsDevTools::ResetDevSettings()
{
    bInfiniteStamina = false;
    bOneHitKO = false;
    bDebugMode = false;
    bShowOverlay = false;
    DebugLog.Empty();
    AddToLog(TEXT("Dev settings reset"));
}

void ULesFightMartialArtsDevTools::AddToLog(const FString& Message)
{
    DebugLog.Add(Message);
    if (DebugLog.Num() > MaxLogEntries)
    {
        DebugLog.RemoveAt(0);
    }
    UE_LOG(LogLesFight, Log, TEXT("[MartialArtsDev] %s"), *Message);
}

void ULesFightMartialArtsDevTools::BroadcastResult(FName ToolName, const FString& Result)
{
    OnDevToolExecuted.Broadcast(ToolName, Result);
}
