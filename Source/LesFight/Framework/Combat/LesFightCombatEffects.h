#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "NiagaraSystem.h"
#include "LesFightCombatEffects.generated.h"

class ALesFightBaseFighter;
class UNiagaraComponent;

USTRUCT(BlueprintType)
struct FHitEffectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UNiagaraSystem> HitEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USoundBase> HitSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UParticleSystem> LegacyHitEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EffectScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EffectDuration;

    FHitEffectData()
        : HitEffect(nullptr)
        , HitSound(nullptr)
        , LegacyHitEffect(nullptr)
        , EffectScale(FVector::OneVector)
        , EffectDuration(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FBlockEffectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UNiagaraSystem> BlockEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USoundBase> BlockSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UParticleSystem> LegacyBlockEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EffectScale;

    FBlockEffectData()
        : BlockEffect(nullptr)
        , BlockSound(nullptr)
        , LegacyBlockEffect(nullptr)
        , EffectScale(FVector::OneVector)
    {}
};

USTRUCT(BlueprintType)
struct FSpecialEffectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UNiagaraSystem> Effect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USoundBase> Sound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EffectScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EffectDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAttachToOwner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttachSocket;

    FSpecialEffectData()
        : Effect(nullptr)
        , Sound(nullptr)
        , EffectScale(FVector::OneVector)
        , EffectDuration(1.0f)
        , bAttachToOwner(false)
        , AttachSocket(NAME_None)
    {}
};

UENUM(BlueprintType)
enum class EEffectPlayMode : uint8
{
    Instant,
    Loop,
    Duration,
};

UCLASS(Blueprintable)
class ULesFightCombatEffects : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatEffects();

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlayHitEffect(FVector Location, FRotator Rotation, EHitReaction ReactionType);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlayBlockEffect(FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlaySpecialEffect(FName EffectID, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlayKnockbackEffect(FVector Location, FVector Direction);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlayLaunchEffect(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlayGroundHitEffect(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void PlayEffectByType(EAttackType AttackType, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void StopAllEffects();

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void SetEffectsEnabled(bool bEnabled) { bEffectsEnabled = bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void SetSoundEnabled(bool bEnabled) { bSoundEnabled = bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void SetScreenShakeEnabled(bool bEnabled) { bScreenShakeEnabled = bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void SetTimeDilationEnabled(bool bEnabled) { bTimeDilationEnabled = bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void SetHitstopDuration(float Duration) { HitstopDuration = Duration; }

    UFUNCTION(BlueprintCallable, Category = "CombatEffects")
    void TriggerHitstop(float Duration = -1.0f);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TMap<EHitReaction, FHitEffectData> HitEffects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    FBlockEffectData BlockEffects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TMap<FName, FSpecialEffectData> SpecialEffects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    float HitstopDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    float KnockbackEffectScale;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    float LaunchEffectScale;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    float GroundHitEffectScale;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    float ScreenShakeIntensity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    float ScreenShakeDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    class UCurveFloat* HitstopCurve;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TSubclassOf<class UCameraShakeBase> HitShakeClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TSubclassOf<class UCameraShakeBase> BlockShakeClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TSubclassOf<class UCameraShakeBase> HeavyHitShakeClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    TSubclassOf<class UCameraShakeBase> LaunchShakeClass;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    TArray<TObjectPtr<UNiagaraComponent>> ActiveEffects;
    bool bEffectsEnabled;
    bool bSoundEnabled;
    bool bScreenShakeEnabled;
    bool bTimeDilationEnabled;
    float HitstopRemaining;

    UNiagaraComponent* SpawnNiagaraEffect(UNiagaraSystem* Effect, FVector Location,
        FRotator Rotation, FVector Scale, bool bAttach, FName Socket);
    void PlaySound(USoundBase* Sound, FVector Location);
    void PlayCameraShake(TSubclassOf<class UCameraShakeBase> ShakeClass);
};
