#include "LesFightAnimationLayerSystem.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationDataAsset.h"
#include "LesFight.h"

ULesFightAnimationLayerSystem::ULesFightAnimationLayerSystem()
    : DefaultBlendSpeed(5.0f)
    , UpperBodyBlendWeight(1.0f)
    , LowerBodyBlendWeight(1.0f)
{
    LayerWeights.SetNum((int32)EAnimationLayer::Max);
    for (int32 i = 0; i < (int32)EAnimationLayer::Max; i++)
    {
        LayerWeights[i].Layer = (EAnimationLayer)i;
        LayerWeights[i].CurrentWeight = (i == 0) ? 1.0f : 0.0f;
        LayerWeights[i].TargetWeight = (i == 0) ? 1.0f : 0.0f;
        LayerWeights[i].BlendSpeed = DefaultBlendSpeed;
        LayerWeights[i].bActive = (i == 0);
    }
}

void ULesFightAnimationLayerSystem::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AnimBP = AnimComponent->GetAnimBlueprintInstance();
    }

    if (AnimData)
    {
        DefaultBlendSpeed = 1.0f / FMath::Max(AnimData->DefaultBlendInTime, 0.01f);
    }
}

void ULesFightAnimationLayerSystem::Update(float DeltaTime)
{
    for (FLayerWeightInfo& Layer : LayerWeights)
    {
        if (Layer.CurrentWeight != Layer.TargetWeight)
        {
            float Step = Layer.BlendSpeed * DeltaTime;
            Layer.CurrentWeight = FMath::FInterpTo(Layer.CurrentWeight, Layer.TargetWeight,
                DeltaTime, Layer.BlendSpeed);
            if (FMath::IsNearlyEqual(Layer.CurrentWeight, Layer.TargetWeight, 0.01f))
            {
                Layer.CurrentWeight = Layer.TargetWeight;
            }
        }
    }
}

void ULesFightAnimationLayerSystem::SetLayerWeight(EAnimationLayer Layer, float TargetWeight,
    float BlendSpeed)
{
    FLayerWeightInfo* LayerInfo = FindLayerInfo(Layer);
    if (LayerInfo)
    {
        LayerInfo->TargetWeight = FMath::Clamp(TargetWeight, 0.0f, 1.0f);
        LayerInfo->BlendSpeed = BlendSpeed;
    }
}

void ULesFightAnimationLayerSystem::ActivateLayer(EAnimationLayer Layer)
{
    FLayerWeightInfo* LayerInfo = FindLayerInfo(Layer);
    if (LayerInfo)
    {
        LayerInfo->bActive = true;
        LayerInfo->TargetWeight = 1.0f;
    }
}

void ULesFightAnimationLayerSystem::DeactivateLayer(EAnimationLayer Layer)
{
    FLayerWeightInfo* LayerInfo = FindLayerInfo(Layer);
    if (LayerInfo)
    {
        LayerInfo->bActive = false;
        LayerInfo->TargetWeight = 0.0f;
    }
}

void ULesFightAnimationLayerSystem::BlendToUpperBody(float BlendTime)
{
    float BlendSpeed = 1.0f / FMath::Max(BlendTime, 0.01f);
    SetLayerWeight(EAnimationLayer::UpperBody, 1.0f, BlendSpeed);
    SetLayerWeight(EAnimationLayer::LowerBody, 1.0f, BlendSpeed);
}

void ULesFightAnimationLayerSystem::BlendToFullBody(float BlendTime)
{
    float BlendSpeed = 1.0f / FMath::Max(BlendTime, 0.01f);
    for (FLayerWeightInfo& Layer : LayerWeights)
    {
        Layer.TargetWeight = 1.0f;
        Layer.BlendSpeed = BlendSpeed;
    }
}

void ULesFightAnimationLayerSystem::SetUpperBodyOverride(UAnimSequence* OverrideAnim,
    FName SlotName)
{
    if (AnimBP.IsValid() && OverrideAnim)
    {
        AnimBP->TriggerAdditiveAnimation(SlotName, OverrideAnim, 0.2f);
    }
}

void ULesFightAnimationLayerSystem::ClearUpperBodyOverride()
{
    ActivateLayer(EAnimationLayer::BasePose);
}

float ULesFightAnimationLayerSystem::GetLayerWeight(EAnimationLayer Layer) const
{
    const FLayerWeightInfo* LayerInfo = nullptr;
    for (const FLayerWeightInfo& L : LayerWeights)
    {
        if (L.Layer == Layer)
        {
            LayerInfo = &L;
            break;
        }
    }
    return LayerInfo ? LayerInfo->CurrentWeight : 0.0f;
}

bool ULesFightAnimationLayerSystem::IsLayerActive(EAnimationLayer Layer) const
{
    const FLayerWeightInfo* LayerInfo = nullptr;
    for (const FLayerWeightInfo& L : LayerWeights)
    {
        if (L.Layer == Layer)
        {
            LayerInfo = &L;
            break;
        }
    }
    return LayerInfo ? LayerInfo->bActive : false;
}

FLayerWeightInfo* ULesFightAnimationLayerSystem::FindLayerInfo(EAnimationLayer Layer)
{
    for (FLayerWeightInfo& L : LayerWeights)
    {
        if (L.Layer == Layer) return &L;
    }
    return nullptr;
}
