#include "LesFightHitReactionAnimation.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationDataAsset.h"
#include "LesFight.h"

ULesFightHitReactionAnimation::ULesFightHitReactionAnimation()
    : CurrentReaction(EHitReactionAnimType::None)
    , ReactionTimer(0.0f)
    , bIsReacting(false)
    , ReactionIntensityMultiplier(1.0f)
    , LightReactionThreshold(15.0f)
    , HeavyReactionThreshold(30.0f)
    , KnockbackReactionThreshold(50.0f)
{
}

void ULesFightHitReactionAnimation::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AnimBP = AnimComponent->GetAnimBlueprintInstance();
    }

    if (AnimData)
    {
        for (const auto& Pair : AnimData->CombatSet.HitReactionMontages)
        {
            FHitReactionAnimData ReactionData;
            ReactionData.ReactionType = Pair.Key;
            ReactionData.ReactionMontage = Pair.Value;
            ReactionAnimData.Add(Pair.Key, ReactionData);
        }
    }
}

void ULesFightHitReactionAnimation::Update(float DeltaTime)
{
    if (bIsReacting)
    {
        ReactionTimer -= DeltaTime;
        if (ReactionTimer <= 0.0f)
        {
            if (!QueuedReactions.IsEmpty())
            {
                EHitReactionAnimType NextReaction;
                QueuedReactions.Dequeue(NextReaction);
                PlayHitReaction(NextReaction);
            }
            else
            {
                bIsReacting = false;
                CurrentReaction = EHitReactionAnimType::None;
                if (AnimBP.IsValid())
                {
                    AnimBP->SetHitReactionAnim(EHitReactionAnimType::None);
                }
            }
        }
    }
}

void ULesFightHitReactionAnimation::PlayHitReaction(EHitReactionAnimType ReactionType)
{
    if (bIsReacting && !ReactionAnimData.Contains(CurrentReaction))
    {
        QueueHitReaction(ReactionType);
        return;
    }

    const FHitReactionAnimData* AnimData = ReactionAnimData.Find(ReactionType);
    if (!AnimData || !AnimData->ReactionMontage || !AnimComponent.IsValid()) return;

    CurrentReaction = ReactionType;
    bIsReacting = true;
    ReactionTimer = AnimData->ReactivateTime;

    FAnimationMontageData MontageData;
    MontageData.Montage = AnimData->ReactionMontage;
    MontageData.bEnableRootMotion = AnimData->bUseRootMotion;
    MontageData.bLoop = false;
    AnimComponent->PlayAnimationMontage(MontageData);

    if (AnimBP.IsValid())
    {
        AnimBP->SetHitReactionAnim(ReactionType);
    }
}

void ULesFightHitReactionAnimation::PlayReactionForBone(FName HitBone, float Damage,
    FVector HitDirection)
{
    EHitReactionAnimType ReactionType = GetBoneHitReaction(HitBone, Damage);
    PlayHitReaction(ReactionType);
}

void ULesFightHitReactionAnimation::StopHitReaction(float BlendOut)
{
    if (bIsReacting && AnimComponent.IsValid())
    {
        AnimComponent->StopAnimationMontage(BlendOut);
    }
    bIsReacting = false;
    CurrentReaction = EHitReactionAnimType::None;
}

void ULesFightHitReactionAnimation::QueueHitReaction(EHitReactionAnimType ReactionType)
{
    QueuedReactions.Enqueue(ReactionType);
}

void ULesFightHitReactionAnimation::CancelQueuedReactions()
{
    QueuedReactions.Empty();
}

EHitReactionAnimType ULesFightHitReactionAnimation::GetBoneHitReaction(FName HitBone,
    float Damage) const
{
    float AdjustedDamage = Damage * ReactionIntensityMultiplier;
    FString BoneStr = HitBone.ToString();

    if (BoneStr.Contains(TEXT("head"), ESearchCase::IgnoreCase))
    {
        return AdjustedDamage >= HeavyReactionThreshold
            ? EHitReactionAnimType::HeadHit
            : EHitReactionAnimType::LightStun;
    }
    else if (BoneStr.Contains(TEXT("spine"), ESearchCase::IgnoreCase) ||
             BoneStr.Contains(TEXT("pelvis"), ESearchCase::IgnoreCase))
    {
        if (AdjustedDamage >= KnockbackReactionThreshold)
            return EHitReactionAnimType::Knockback;
        if (AdjustedDamage >= HeavyReactionThreshold)
            return EHitReactionAnimType::BodyHit;
        return EHitReactionAnimType::LightStun;
    }
    else if (BoneStr.Contains(TEXT("leg"), ESearchCase::IgnoreCase) ||
             BoneStr.Contains(TEXT("foot"), ESearchCase::IgnoreCase))
    {
        return AdjustedDamage >= HeavyReactionThreshold
            ? EHitReactionAnimType::LegHit
            : EHitReactionAnimType::Stagger;
    }

    if (AdjustedDamage >= KnockbackReactionThreshold)
        return EHitReactionAnimType::Knockback;
    if (AdjustedDamage >= HeavyReactionThreshold)
        return EHitReactionAnimType::BodyHit;
    return EHitReactionAnimType::LightStun;
}

void ULesFightHitReactionAnimation::SelectReactionByDamage(float Damage,
    EHitReactionAnimType& OutType)
{
    if (Damage >= KnockbackReactionThreshold)
        OutType = EHitReactionAnimType::Knockback;
    else if (Damage >= HeavyReactionThreshold)
        OutType = EHitReactionAnimType::BodyHit;
    else
        OutType = EHitReactionAnimType::LightStun;
}
