#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHUDElementUpdated, FName, ElementName, FText, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStyleDisplayChanged, EFightingStyle, NewStyle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStanceDisplayChanged, ECombatStance, NewStance);

UCLASS(Blueprintable)
class ULesFightMartialArtsHUD : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsHUD();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void UpdateStyleDisplay(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void UpdateStanceDisplay(ECombatStance Stance);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void UpdateComboCounter(int32 ComboCount);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void ShowCounterNotification(ECounterType CounterType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void UpdateUltimateMeter(float CurrentMeter, float MaxMeter);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void ShowSpecialTechniqueIndicator(FName TechniqueName, float Cooldown);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void ShowEnvironmentalInteractionPrompt(EEnvironmentInteraction InteractionType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void ShowCinematicOverlay(ECinematicEffect EffectType, bool bShow);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void ShowSlowMotionIndicator(bool bActive);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void UpdateHitNotification(float Damage, bool bWasCounter);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void UpdateStanceModifiers(const FStanceAttributes& Attributes);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void ClearAllNotifications();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|HUD")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHUDElementUpdated OnHUDElementUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStyleDisplayChanged OnStyleDisplayChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStanceDisplayChanged OnStanceDisplayChanged;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFightingStyle CurrentDisplayedStyle;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECombatStance CurrentDisplayedStance;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentComboCount;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float CurrentUltimateMeter;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float MaxUltimateMeter;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<FName, float> TechniqueCooldowns;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float NotificationDisplayTime;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    TMap<FName, float> NotificationTimers;
    float ComboDisplayTimer;

    void BroadcastElementUpdate(FName ElementName, FText Value);
};
