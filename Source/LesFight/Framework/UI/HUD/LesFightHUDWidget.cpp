#include "LesFightHUDWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    bHUDVisible = true;
}

void ULesFightHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

ULesFightCombatHUD* ULesFightHUDWidget::GetCombatHUD() const
{
    return CombatHUD;
}

void ULesFightHUDWidget::ShowHUD()
{
    bHUDVisible = true;
    SetVisibility(ESlateVisibility::Visible);

    if (CombatHUD) CombatHUD->SetVisibility(ESlateVisibility::Visible);
    if (CrosshairWidget) CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
    if (MiniMapWidget) MiniMapWidget->SetVisibility(ESlateVisibility::Visible);
    if (TargetIndicator) TargetIndicator->SetVisibility(ESlateVisibility::Visible);
}

void ULesFightHUDWidget::HideHUD()
{
    bHUDVisible = false;
    SetVisibility(ESlateVisibility::Hidden);

    if (CombatHUD) CombatHUD->SetVisibility(ESlateVisibility::Hidden);
    if (CrosshairWidget) CrosshairWidget->SetVisibility(ESlateVisibility::Hidden);
    if (MiniMapWidget) MiniMapWidget->SetVisibility(ESlateVisibility::Hidden);
    if (DebugInfoWidget) DebugInfoWidget->SetVisibility(ESlateVisibility::Hidden);
    if (TargetIndicator) TargetIndicator->SetVisibility(ESlateVisibility::Hidden);
}

void ULesFightHUDWidget::ToggleHUD()
{
    if (bHUDVisible)
    {
        HideHUD();
    }
    else
    {
        ShowHUD();
    }
}

void ULesFightHUDWidget::ShowCrosshair(bool bShow)
{
    if (CrosshairWidget)
    {
        CrosshairWidget->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void ULesFightHUDWidget::ShowTargetIndicator(FVector WorldLocation, bool bShow)
{
    if (TargetIndicator)
    {
        TargetIndicator->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void ULesFightHUDWidget::ShowMiniMap(bool bShow)
{
    if (MiniMapWidget)
    {
        MiniMapWidget->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void ULesFightHUDWidget::ShowDebugInfo(FText DebugText)
{
    if (DebugInfoWidget)
    {
        DebugInfoWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void ULesFightHUDWidget::HideDebugInfo()
{
    if (DebugInfoWidget)
    {
        DebugInfoWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ULesFightHUDWidget::SetHUDScale(float Scale)
{
    FWidgetTransform NewTransform;
    NewTransform.Scale = FVector2D(Scale, Scale);
    SetRenderTransform(NewTransform);
}

TArray<UUserWidget*> ULesFightHUDWidget::GetHUDWidgets() const
{
    TArray<UUserWidget*> Widgets;
    if (CombatHUD) Widgets.Add(CombatHUD);
    if (CrosshairWidget) Widgets.Add(CrosshairWidget);
    if (MiniMapWidget) Widgets.Add(MiniMapWidget);
    if (DebugInfoWidget) Widgets.Add(DebugInfoWidget);
    if (TargetIndicator) Widgets.Add(TargetIndicator);
    return Widgets;
}
