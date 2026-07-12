#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationLayerSystem.generated.h"

class ULesFightCharacterAnimationComponent;

USTRUCT(BlueprintType)
struct FLayerWeightInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimationLayer Layer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TargetWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bActive;

    FLayerWeightInfo()
        : Layer(EAnimationLayer::BasePose)
        , TargetWeight(1.0f), CurrentWeight(1.0f)
        , BlendSpeed(5.0f), bActive(true)
    {}
};

UCLASS(Blueprintable)
class ULesFightAnimationLayerSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationLayerSystem();

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void SetLayerWeight(EAnimationLayer Layer, float TargetWeight, float BlendSpeed = 5.0f);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void ActivateLayer(EAnimationLayer Layer);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void DeactivateLayer(EAnimationLayer Layer);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void BlendToUpperBody(float BlendTime = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void BlendToFullBody(float BlendTime = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void SetUpperBodyOverride(UAnimSequence* OverrideAnim, FName SlotName);

    UFUNCTION(BlueprintCallable, Category = "Animation Layers")
    void ClearUpperBodyOverride();

    UFUNCTION(BlueprintPure, Category = "Animation Layers")
    float GetLayerWeight(EAnimationLayer Layer) const;

    UFUNCTION(BlueprintPure, Category = "Animation Layers")
    bool IsLayerActive(EAnimationLayer Layer) const;

    UFUNCTION(BlueprintPure, Category = "Animation Layers")
    TArray<FLayerWeightInfo> GetAllLayerWeights() const { return LayerWeights; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation Layers")
    TArray<FLayerWeightInfo> LayerWeights;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Layers")
    float DefaultBlendSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Layers")
    float UpperBodyBlendWeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Layers")
    float LowerBodyBlendWeight;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAnimBlueprintBase> AnimBP;
    FLayerWeightInfo* FindLayerInfo(EAnimationLayer Layer);
};
