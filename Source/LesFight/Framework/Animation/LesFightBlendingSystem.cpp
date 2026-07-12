#include "LesFightBlendingSystem.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFight.h"

ULesFightBlendingSystem::ULesFightBlendingSystem()
    : DefaultBlendTime(0.2f)
    , MaxActiveBlends(4)
    , bUseInertialization(false)
    , BlendQuality(EAnimationQuality::High)
{
}

void ULesFightBlendingSystem::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AnimBP = AnimComponent->GetAnimBlueprintInstance();
    }
    if (AnimData)
    {
        DefaultBlendTime = AnimData->DefaultBlendInTime;
    }
}

void ULesFightBlendingSystem::Update(float DeltaTime)
{
    for (int32 i = ActiveBlends.Num() - 1; i >= 0; i--)
    {
        ProcessBlend(ActiveBlends[i], DeltaTime);
        if (ActiveBlends[i].BlendProgress >= 1.0f)
        {
            ActiveBlends.RemoveAt(i);
        }
    }

    while (PendingBlends.Num() > 0 && ActiveBlends.Num() < MaxActiveBlends)
    {
        ActiveBlends.Add(PendingBlends[0]);
        PendingBlends.RemoveAt(0);
    }
}

void ULesFightBlendingSystem::RequestBlend(const FBlendRequest& Request)
{
    if (ActiveBlends.Num() >= MaxActiveBlends)
    {
        PendingBlends.Add(Request);
    }
    else
    {
        ActiveBlends.Add(Request);
    }
}

void ULesFightBlendingSystem::RequestDirectionalBlend(float Speed, float Direction)
{
    FBlendRequest Request;
    Request.BlendTime = DefaultBlendTime;
    Request.Method = EAnimTransitionMethod::StandardBlend;
    Request.TargetLayer = EAnimationLayer::Locomotion;
    RequestBlend(Request);
}

void ULesFightBlendingSystem::RequestLayerBlend(EAnimationLayer Layer, float TargetWeight,
    float BlendTime)
{
    FBlendRequest Request;
    Request.BlendTime = BlendTime;
    Request.TargetLayer = Layer;
    Request.Method = EAnimTransitionMethod::StandardBlend;
    RequestBlend(Request);
}

void ULesFightBlendingSystem::SetBlendQuality(EAnimationQuality Quality)
{
    BlendQuality = Quality;
    switch (Quality)
    {
    case EAnimationQuality::Low:
        DefaultBlendTime = 0.05f;
        MaxActiveBlends = 2;
        break;
    case EAnimationQuality::Medium:
        DefaultBlendTime = 0.1f;
        MaxActiveBlends = 3;
        break;
    case EAnimationQuality::High:
    case EAnimationQuality::Epic:
    case EAnimationQuality::Cinematic:
        DefaultBlendTime = 0.2f;
        MaxActiveBlends = 4;
        break;
    }
}

void ULesFightBlendingSystem::CompleteAllBlends()
{
    for (FBlendRequest& Blend : ActiveBlends)
    {
        Blend.BlendProgress = 1.0f;
    }
    ActiveBlends.Empty();
    PendingBlends.Empty();
}

bool ULesFightBlendingSystem::IsBlending() const
{
    return ActiveBlends.Num() > 0 || PendingBlends.Num() > 0;
}

float ULesFightBlendingSystem::GetBlendProgress() const
{
    if (ActiveBlends.Num() == 0) return 1.0f;
    float Total = 0.0f;
    for (const FBlendRequest& Blend : ActiveBlends)
    {
        Total += Blend.BlendProgress;
    }
    return Total / ActiveBlends.Num();
}

void ULesFightBlendingSystem::ProcessBlend(FBlendRequest& Blend, float DeltaTime)
{
    float Speed = GetBlendSpeedForMethod(Blend.Method);
    Blend.BlendProgress = FMath::Clamp(Blend.BlendProgress + Speed * DeltaTime, 0.0f, 1.0f);
}

float ULesFightBlendingSystem::GetBlendSpeedForMethod(EAnimTransitionMethod Method) const
{
    switch (Method)
    {
    case EAnimTransitionMethod::StandardBlend:
        return 1.0f / FMath::Max(DefaultBlendTime, 0.01f);
    case EAnimTransitionMethod::Inertialization:
        return 2.0f / FMath::Max(DefaultBlendTime, 0.01f);
    case EAnimTransitionMethod::CustomCurve:
        return 1.5f / FMath::Max(DefaultBlendTime, 0.01f);
    case EAnimTransitionMethod::Snap:
        return 100.0f;
    default:
        return 1.0f / FMath::Max(DefaultBlendTime, 0.01f);
    }
}
