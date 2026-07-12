#include "LesFightDebugOverlay.h"
#include "LesFight.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULesFightDebugOverlay::ULesFightDebugOverlay()
    : bIsVisible(false)
{
}

void ULesFightDebugOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bIsVisible)
    {
        CollectDebugInfo();
    }
}

void ULesFightDebugOverlay::ToggleDebugOverlay()
{
    if (bIsVisible)
    {
        HideDebugOverlay();
    }
    else
    {
        ShowDebugOverlay();
    }
}

void ULesFightDebugOverlay::ShowDebugOverlay()
{
    bIsVisible = true;
    SetVisibility(ESlateVisibility::Visible);
    UE_LOG(LogLesFight, Log, TEXT("Debug overlay shown"));
}

void ULesFightDebugOverlay::HideDebugOverlay()
{
    bIsVisible = false;
    SetVisibility(ESlateVisibility::Hidden);
    UE_LOG(LogLesFight, Log, TEXT("Debug overlay hidden"));
}

void ULesFightDebugOverlay::CollectDebugInfo()
{
    if (!GetWorld()) return;

    CurrentDebugInfo.FrameRate = 1.0f / GetWorld()->GetDeltaSeconds();
    CurrentDebugInfo.FrameTime = GetWorld()->GetDeltaSeconds() * 1000.0f;
    CurrentDebugInfo.GameTime = GetWorld()->GetTimeSeconds();

    if (GEngine)
    {
        CurrentDebugInfo.TriangleCount = 0;
        CurrentDebugInfo.DrawCalls = 0;
    }

    OnDebugDisplayUpdate(CurrentDebugInfo);
    OnDebugInfoUpdated.Broadcast(CurrentDebugInfo);
}

void ULesFightDebugOverlay::ExecuteConsoleCommand(const FString& Command)
{
    if (GetWorld())
    {
        GetWorld()->GetFirstPlayerController()->ConsoleCommand(Command);
    }
}
