#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationDebugger.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAnimBlueprintBase;

USTRUCT(BlueprintType)
struct FAnimationDebugInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString FighterName;

    UPROPERTY(BlueprintReadOnly)
    FString CurrentState;

    UPROPERTY(BlueprintReadOnly)
    FString CurrentCombatAnim;

    UPROPERTY(BlueprintReadOnly)
    FString CurrentHitReaction;

    UPROPERTY(BlueprintReadOnly)
    float Speed;

    UPROPERTY(BlueprintReadOnly)
    float Direction;

    UPROPERTY(BlueprintReadOnly)
    float BlendProgress;

    UPROPERTY(BlueprintReadOnly)
    bool bIsPlayingMontage;

    UPROPERTY(BlueprintReadOnly)
    FString MontageName;

    UPROPERTY(BlueprintReadOnly)
    float MontagePlayTime;

    UPROPERTY(BlueprintReadOnly)
    FString FacialExpression;

    UPROPERTY(BlueprintReadOnly)
    float PlayRate;

    FAnimationDebugInfo()
        : Speed(0.0f), Direction(0.0f), BlendProgress(1.0f)
        , bIsPlayingMontage(false), MontagePlayTime(0.0f), PlayRate(1.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightAnimationDebugger : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationDebugger();

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void RegisterAnimComponent(ULesFightCharacterAnimationComponent* AnimComp);

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void ToggleDebugDisplay();

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void ShowAnimationStates(bool bShow) { bShowStates = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void ShowBlendSpaces(bool bShow) { bShowBlendSpaces = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void ShowRootMotion(bool bShow) { bShowRootMotion = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void ShowAnimationNotifies(bool bShow) { bShowNotifies = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void ShowPerformance(bool bShow) { bShowPerformance = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void SetDebugMode(bool bEnabled) { bDebugEnabled = bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void SetSlowMotionMode(bool bEnabled, float TimeDilation = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Animation Debug")
    void SetAnimationPaused(bool bPaused);

    UFUNCTION(BlueprintPure, Category = "Animation Debug")
    TArray<FAnimationDebugInfo> GetDebugInfo() const { return DebugInfo; }

    UFUNCTION(BlueprintPure, Category = "Animation Debug")
    bool IsDebugEnabled() const { return bDebugEnabled; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    TArray<FAnimationDebugInfo> DebugInfo;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    TArray<TObjectPtr<ULesFightCharacterAnimationComponent>> RegisteredComponents;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    bool bDebugEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    bool bShowStates;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    bool bShowBlendSpaces;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    bool bShowRootMotion;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    bool bShowNotifies;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Debug")
    bool bShowPerformance;

private:
    void CollectDebugData();
    void DrawDebugOverlay(UWorld* World);
    float FrameTimeHistory[120];
    int32 FrameTimeIndex;
};
