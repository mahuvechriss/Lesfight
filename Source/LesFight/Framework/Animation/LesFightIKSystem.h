#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "LesFightAnimationData.h"
#include "LesFightIKSystem.generated.h"

class ULesFightCharacterAnimationComponent;

USTRUCT(BlueprintType)
struct FIKFootData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName FootBoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EffectorBoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName HipBoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FootOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TraceDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InterpSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector IKLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator IKRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float IKAlpha;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableLock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLocked;

    FIKFootData()
        : FootBoneName(NAME_None), EffectorBoneName(NAME_None), HipBoneName(NAME_None)
        , FootOffset(4.0f), TraceDistance(50.0f), InterpSpeed(8.0f)
        , IKLocation(FVector::ZeroVector), IKRotation(FRotator::ZeroRotator)
        , IKAlpha(1.0f), bEnableLock(true), bLocked(false)
    {}
};

USTRUCT(BlueprintType)
struct FIKHandData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName HandBoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EffectorBoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float IKAlpha;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector IKLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator IKRotation;

    FIKHandData()
        : HandBoneName(NAME_None), EffectorBoneName(NAME_None)
        , IKAlpha(0.0f)
        , IKLocation(FVector::ZeroVector), IKRotation(FRotator::ZeroRotator)
    {}
};

UCLASS(Blueprintable)
class ULesFightIKSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightIKSystem();

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void SetIKQuality(EAnimationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void EnableFootIK(bool bEnable) { bFootIKEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void EnableHandIK(bool bEnable) { bHandIKEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void EnableGroundAdaptation(bool bEnable) { bGroundAdaptationEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void SetFootLocking(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void SetIKAlpha(float Alpha);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void OverrideFootIK(FName FootBone, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void OverrideHandIK(FName HandBone, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void ResetIK();

    UFUNCTION(BlueprintCallable, Category = "IK System")
    void SetIKBlendSpeed(float Speed) { IKBlendSpeed = Speed; }

    UFUNCTION(BlueprintPure, Category = "IK System")
    TArray<FIKFootData> GetFootIKData() const { return FootIKData; }

    UFUNCTION(BlueprintPure, Category = "IK System")
    TArray<FIKHandData> GetHandIKData() const { return HandIKData; }

    UFUNCTION(BlueprintPure, Category = "IK System")
    float GetCurrentIKAlpha() const { return CurrentIKAlpha; }

    UFUNCTION(BlueprintPure, Category = "IK System")
    bool IsFootIKEnabled() const { return bFootIKEnabled; }

    UFUNCTION(BlueprintPure, Category = "IK System")
    bool IsHandIKEnabled() const { return bHandIKEnabled; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "IK System")
    TArray<FIKFootData> FootIKData;

    UPROPERTY(BlueprintReadOnly, Category = "IK System")
    TArray<FIKHandData> HandIKData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IK System")
    float IKBlendSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IK System")
    float IKTraceDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IK System")
    float FootRaiseDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IK System")
    float PelvisOffset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "IK System")
    EAnimationQuality IKQuality;

    UPROPERTY(BlueprintReadOnly, Category = "IK System")
    float CurrentIKAlpha;

    UPROPERTY(BlueprintReadOnly, Category = "IK System")
    bool bFootIKEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "IK System")
    bool bHandIKEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "IK System")
    bool bGroundAdaptationEnabled;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<USkeletalMeshComponent> MeshComponent;

    void UpdateFootIK(float DeltaTime);
    void UpdateHandIK(float DeltaTime);
    void UpdateGroundAdaptation(float DeltaTime);
    void UpdateFootLocking(float DeltaTime);
    FVector TraceGround(FName BoneName, float TraceDist) const;
    FHitResult LineTraceSingle(const FVector& Start, const FVector& End) const;
    void ApplyPelvisOffset(float DeltaTime);
};
