#include "LesFightCombatAnimHandler.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationDataAsset.h"
#include "LesFightCombatComponent.h"
#include "LesFight.h"

ULesFightCombatAnimHandler::ULesFightCombatAnimHandler()
    : CurrentType(ECombatAnimType::None)
    , bPlayingCombatAnim(false)
{
}

void ULesFightCombatAnimHandler::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AnimBP = AnimComponent->GetAnimBlueprintInstance();
        AActor* Owner = AnimComponent->GetOwner();
        if (Owner)
        {
            CombatComponent = Owner->FindComponentByClass<ULesFightCombatComponent>();
        }
    }
    if (AnimData)
    {
        CurrentAnimSet = AnimData->CombatSet;
    }
}

void ULesFightCombatAnimHandler::PlayAttackAnimation(const FAnimationMontageData& MontageData)
{
    if (!MontageData.Montage || !AnimComponent.IsValid()) return;

    bPlayingCombatAnim = true;
    AnimComponent->PlayAnimationMontage(MontageData);
}

void ULesFightCombatAnimHandler::PlayBlockAnimation(bool bPerfect)
{
    UAnimMontage* Montage = bPerfect
        ? CurrentAnimSet.PerfectBlockMontage
        : CurrentAnimSet.BlockMontage;
    if (Montage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Montage;
        MontageData.bEnableRootMotion = false;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCombatAnimHandler::PlayDodgeAnimation()
{
    if (CurrentAnimSet.DodgeMontage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = CurrentAnimSet.DodgeMontage;
        MontageData.bEnableRootMotion = true;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCombatAnimHandler::PlayThrowAnimation(bool bIsAttacker)
{
    UAnimMontage* Montage = bIsAttacker
        ? CurrentAnimSet.ThrowMontage
        : CurrentAnimSet.BeingThrownMontage;
    if (Montage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Montage;
        MontageData.bEnableRootMotion = bIsAttacker;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCombatAnimHandler::PlayVictoryAnimation()
{
    UAnimMontage* Montage = CurrentAnimSet.AttackAnimations.FindRef(FName(TEXT("Victory")));
    if (Montage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Montage;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCombatAnimHandler::PlayDefeatAnimation()
{
    UAnimMontage* Montage = CurrentAnimSet.AttackAnimations.FindRef(FName(TEXT("Defeat")));
    if (Montage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Montage;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCombatAnimHandler::PlayTauntAnimation(int32 TauntIndex)
{
    FName TauntID = *FString::Printf(TEXT("Taunt%d"), TauntIndex);
    UAnimMontage* Montage = CurrentAnimSet.AttackAnimations.FindRef(TauntID);
    if (Montage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Montage;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCombatAnimHandler::SetCombatAnimSet(const FCombatAnimSet& AnimSet)
{
    CurrentAnimSet = AnimSet;
}

void ULesFightCombatAnimHandler::StopCombatAnimation(float BlendOut)
{
    if (AnimComponent.IsValid())
    {
        AnimComponent->StopAnimationMontage(BlendOut);
    }
    bPlayingCombatAnim = false;
}

void ULesFightCombatAnimHandler::SetCombatAnimType(ECombatAnimType Type)
{
    CurrentType = Type;
    if (AnimBP.IsValid())
    {
        AnimBP->SetCombatAnimType(Type);
    }
}

UAnimMontage* ULesFightCombatAnimHandler::FindAttackMontage(FName AttackID) const
{
    return CurrentAnimSet.AttackAnimations.FindRef(AttackID);
}
