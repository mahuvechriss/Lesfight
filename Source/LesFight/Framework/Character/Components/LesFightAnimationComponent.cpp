#include "LesFightAnimationComponent.h"
#include "LesFightAnimInstance.h"
#include "LesFight.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

ULesFightAnimationComponent::ULesFightAnimationComponent()
    : AnimationSpeedMultiplier(1.0f)
    , CurrentAnimationState(TEXT("Idle"))
{
    PrimaryActorTick.bCanEverTick = false;
}

void ULesFightAnimationComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULesFightAnimationComponent::Initialize(USkeletalMeshComponent* InMesh)
{
    SkeletalMesh = InMesh;
    UE_LOG(LogLesFight, Log, TEXT("AnimationComponent initialized for %s"),
        InMesh ? *InMesh->GetName() : TEXT("None"));
}

void ULesFightAnimationComponent::PlayMontage(UAnimMontage* Montage, float PlayRate)
{
    if (!Montage || !SkeletalMesh.IsValid()) return;

    UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
    if (AnimInstance)
    {
        AnimInstance->Montage_Play(Montage, PlayRate * AnimationSpeedMultiplier);
    }
}

void ULesFightAnimationComponent::StopMontage(UAnimMontage* Montage)
{
    if (!Montage || !SkeletalMesh.IsValid()) return;

    UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
    if (AnimInstance)
    {
        AnimInstance->Montage_Stop(0.25f, Montage);
    }
}

void ULesFightAnimationComponent::SetAnimationState(const FString& StateName)
{
    CurrentAnimationState = StateName;
    OnAnimationStateChanged.Broadcast(StateName);
}

void ULesFightAnimationComponent::SetBlendSpaceParameter(const FName& ParameterName, float Value)
{
    if (!SkeletalMesh.IsValid()) return;

    ULesFightAnimInstance* AnimInst = GetFighterAnimInstance();
    if (AnimInst)
    {
        AnimInst->SetBlendSpaceParameter(ParameterName, Value);
    }
}

void ULesFightAnimationComponent::PlayIdleVariation()
{
    if (IdleVariations.Num() == 0 || !SkeletalMesh.IsValid()) return;

    int32 VariationIndex = FMath::RandRange(0, IdleVariations.Num() - 1);
    UAnimSequence* IdleAnim = IdleVariations[VariationIndex];

    if (IdleAnim)
    {
        UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
        if (AnimInstance)
        {
            AnimInstance->PlaySlotAnimationAsDynamicMontage(IdleAnim, TEXT("DefaultSlot"), 0.25f, 0.25f);
        }
    }
}

void ULesFightAnimationComponent::SetAnimationSpeed(float SpeedMultiplier)
{
    AnimationSpeedMultiplier = SpeedMultiplier;
}

void ULesFightAnimationComponent::SetLocomotionValues(float Speed, float Direction)
{
    ULesFightAnimInstance* AnimInst = GetFighterAnimInstance();
    if (AnimInst)
    {
        AnimInst->SetLocomotionSpeed(Speed);
        AnimInst->SetLocomotionDirection(Direction);
    }
}

void ULesFightAnimationComponent::TriggerPunchPlaceholder()
{
    if (PunchMontages.Num() > 0)
    {
        PlayMontage(PunchMontages[FMath::RandRange(0, PunchMontages.Num() - 1)]);
    }
}

void ULesFightAnimationComponent::TriggerKickPlaceholder()
{
    if (KickMontages.Num() > 0)
    {
        PlayMontage(KickMontages[FMath::RandRange(0, KickMontages.Num() - 1)]);
    }
}

void ULesFightAnimationComponent::TriggerBlockPlaceholder()
{
    if (BlockMontage)
    {
        PlayMontage(BlockMontage);
    }
}

void ULesFightAnimationComponent::TriggerHitReactionPlaceholder()
{
    if (HitReactionMontage)
    {
        PlayMontage(HitReactionMontage);
    }
}

ULesFightAnimInstance* ULesFightAnimationComponent::GetFighterAnimInstance() const
{
    if (!SkeletalMesh.IsValid()) return nullptr;
    return Cast<ULesFightAnimInstance>(SkeletalMesh->GetAnimInstance());
}

bool ULesFightAnimationComponent::IsMontagePlaying() const
{
    if (!SkeletalMesh.IsValid()) return false;
    UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
    return AnimInstance && AnimInstance->IsAnyMontagePlaying();
}
