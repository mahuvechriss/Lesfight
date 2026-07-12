#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightCombatHUD.h"
#include "LesFightHUDWidget.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    ULesFightCombatHUD* GetCombatHUD() const;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowHUD();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void HideHUD();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ToggleHUD();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowCrosshair(bool bShow);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowTargetIndicator(FVector WorldLocation, bool bShow);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowMiniMap(bool bShow);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowDebugInfo(FText DebugText);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void HideDebugInfo();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetHUDScale(float Scale);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    TArray<UUserWidget*> GetHUDWidgets() const;

protected:
    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "HUD")
    ULesFightCombatHUD* CombatHUD = nullptr;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "HUD")
    class UUserWidget* CrosshairWidget = nullptr;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "HUD")
    class UUserWidget* MiniMapWidget = nullptr;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "HUD")
    class UUserWidget* DebugInfoWidget = nullptr;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "HUD")
    class UUserWidget* TargetIndicator = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "HUD")
    bool bHUDVisible = true;
};
