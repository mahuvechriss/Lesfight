#include "LesFightHUD.h"
#include "LesFight.h"

void ULesFightHUD::NativeConstruct()
{
    Super::NativeConstruct();
    bIsHUDVisible = true;
    UE_LOG(LogLesFightUI, Log, TEXT("HUD constructed"));
}

void ULesFightHUD::NativeDestruct()
{
    Super::NativeDestruct();
    bIsHUDVisible = false;
    UE_LOG(LogLesFightUI, Log, TEXT("HUD destructed"));
}

void ULesFightHUD::Show()
{
    if (!bIsHUDVisible)
    {
        SetVisibility(ESlateVisibility::Visible);
        bIsHUDVisible = true;
        OnHUDVisibilityChanged.Broadcast(true);
    }
}

void ULesFightHUD::Hide()
{
    if (bIsHUDVisible)
    {
        SetVisibility(ESlateVisibility::Hidden);
        bIsHUDVisible = false;
        OnHUDVisibilityChanged.Broadcast(false);
    }
}
