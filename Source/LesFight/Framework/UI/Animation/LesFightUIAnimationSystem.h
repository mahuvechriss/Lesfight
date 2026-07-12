#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightUIAnimationSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUIAnimationSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void Shutdown();

    UFUNCTION(BlueprintCallable)
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    void PlayAnimationOnWidget(UUserWidget* Widget, FName AnimationName);

    UFUNCTION(BlueprintCallable)
    void StopAnimationOnWidget(UUserWidget* Widget, FName AnimationName);

    UFUNCTION(BlueprintCallable)
    void StopAllAnimationsOnWidget(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable)
    bool IsAnimating(UUserWidget* Widget) const;

    UFUNCTION(BlueprintCallable)
    void RegisterAnimationDef(FName Name, FUIAnimationDef Def);

    UFUNCTION(BlueprintCallable)
    TArray<FName> GetRegisteredAnimations() const;

    UFUNCTION(BlueprintCallable)
    void SetGlobalSpeed(float Speed);

    UFUNCTION(BlueprintCallable)
    float GetGlobalSpeed() const { return GlobalSpeed; }

    UFUNCTION(BlueprintCallable)
    bool AreAnimationsEnabled() const { return bAnimationsEnabled; }

    UFUNCTION(BlueprintCallable)
    void SetAnimationsEnabled(bool bEnabled);

protected:
    UPROPERTY()
    TMap<FName, FUIAnimationDef> AnimationRegistry;

    UPROPERTY()
    TMap<UUserWidget*, TArray<FActiveAnimation>> ActiveWidgetAnimations;

    UPROPERTY()
    float GlobalSpeed = 1.0f;

    UPROPERTY()
    bool bAnimationsEnabled = true;
};
