#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightBlendingSystem.generated.h"

class ULesFightCharacterAnimationComponent;

USTRUCT(BlueprintType)
struct FBlendRequest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> FromAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> ToAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UBlendSpace> BlendSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimTransitionMethod Method;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimationLayer TargetLayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SlotName;

    FBlendRequest()
        : FromAnim(nullptr), ToAnim(nullptr), BlendSpace(nullptr)
        , BlendTime(0.2f), BlendProgress(0.0f)
        , bActive(false)
        , Method(EAnimTransitionMethod::StandardBlend)
        , TargetLayer(EAnimationLayer::FullBody)
        , SlotName(NAME_None)
    {}
};

UCLASS(Blueprintable)
class ULesFightBlendingSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightBlendingSystem();

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void RequestBlend(const FBlendRequest& Request);

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void RequestDirectionalBlend(float Speed, float Direction);

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void RequestLayerBlend(EAnimationLayer Layer, float TargetWeight, float BlendTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void SetBlendQuality(EAnimationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void SetDefaultBlendTime(float Time) { DefaultBlendTime = Time; }

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void UseInertialization(bool bEnable) { bUseInertialization = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Animation Blending")
    void CompleteAllBlends();

    UFUNCTION(BlueprintPure, Category = "Animation Blending")
    bool IsBlending() const;

    UFUNCTION(BlueprintPure, Category = "Animation Blending")
    float GetBlendProgress() const;

    UFUNCTION(BlueprintPure, Category = "Animation Blending")
    TArray<FBlendRequest> GetActiveBlends() const { return ActiveBlends; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation Blending")
    TArray<FBlendRequest> ActiveBlends;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Blending")
    TArray<FBlendRequest> PendingBlends;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Blending")
    float DefaultBlendTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Blending")
    float MaxActiveBlends;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Blending")
    bool bUseInertialization;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Blending")
    EAnimationQuality BlendQuality;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAnimBlueprintBase> AnimBP;

    void ProcessBlend(FBlendRequest& Blend, float DeltaTime);
    float GetBlendSpeedForMethod(EAnimTransitionMethod Method) const;
};
