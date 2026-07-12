#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationStateMachine.h"
#include "LesFightAnimationLayerSystem.h"
#include "LesFightAnimationEventManager.h"
#include "LesFightLocomotionSystem.h"
#include "LesFightCombatAnimHandler.h"
#include "LesFightBlendingSystem.h"
#include "LesFightRootMotionHandler.h"
#include "LesFightMotionWarpingSystem.h"
#include "LesFightIKSystem.h"
#include "LesFightHitReactionAnimation.h"
#include "LesFightFacialAnimationSystem.h"
#include "LesFightBaseFighter.h"
#include "LesFightCombatComponent.h"
#include "Net/UnrealNetwork.h"
#include "LesFight.h"

ULesFightCharacterAnimationComponent::ULesFightCharacterAnimationComponent()
    : CurrentLocomotionState(ELocomotionState::Idle)
    , CurrentCombatAnimType(ECombatAnimType::None)
    , CurrentHitReactionAnim(EHitReactionAnimType::None)
    , GlobalPlayRate(1.0f)
    , bAnimationsPaused(false)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.0f;
    SetIsReplicatedByDefault(true);
}

void ULesFightCharacterAnimationComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightCharacterAnimationComponent::Initialize(ALesFightBaseFighter* InOwner,
    ULesFightAnimationDataAsset* AnimData)
{
    OwnerFighter = InOwner;
    AnimationDataAsset = AnimData;

    if (!OwnerFighter) return;

    CreateSubSystems(InOwner);

    USkeletalMeshComponent* Mesh = GetMesh();
    if (Mesh)
    {
        ULesFightAnimBlueprintBase* AnimBP = Cast<ULesFightAnimBlueprintBase>(Mesh->GetAnimInstance());
        if (AnimBP)
        {
            AnimBP->InitializeWithCharacter(InOwner);
        }
    }

    if (StateMachine) StateMachine->Initialize(this, AnimData);
    if (LayerSystem) LayerSystem->Initialize(this, AnimData);
    if (EventManager) EventManager->Initialize(this);
    if (LocomotionSystem) LocomotionSystem->Initialize(this, AnimData);
    if (CombatAnimHandler) CombatAnimHandler->Initialize(this, AnimData);
    if (BlendingSystem) BlendingSystem->Initialize(this, AnimData);
    if (RootMotionHandler) RootMotionHandler->Initialize(this);
    if (MotionWarpingSystem) MotionWarpingSystem->Initialize(this);
    if (IKSystem) IKSystem->Initialize(this, AnimData);
    if (HitReactionAnimation) HitReactionAnimation->Initialize(this, AnimData);
    if (FacialSystem) FacialSystem->Initialize(this, AnimData);

    BindCombatEvents();

    UE_LOG(LogLesFight, Log, TEXT("CharacterAnimationComponent initialized for %s"), *InOwner->GetName());
}

void ULesFightCharacterAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bAnimationsPaused || !OwnerFighter.IsValid()) return;

    float AdjustedDelta = DeltaTime * GlobalPlayRate;

    UpdateAnimationStates(AdjustedDelta);

    if (LocomotionSystem) LocomotionSystem->Update(AdjustedDelta);
    if (BlendingSystem) BlendingSystem->Update(AdjustedDelta);
    if (IKSystem) IKSystem->Update(AdjustedDelta);
    if (RootMotionHandler) RootMotionHandler->Update(AdjustedDelta);
    if (MotionWarpingSystem) MotionWarpingSystem->Update(AdjustedDelta);
    if (HitReactionAnimation) HitReactionAnimation->Update(AdjustedDelta);
    if (FacialSystem) FacialSystem->Update(AdjustedDelta);
    if (StateMachine) StateMachine->Update(AdjustedDelta);
    if (LayerSystem) LayerSystem->Update(AdjustedDelta);
    if (EventManager) EventManager->Update(AdjustedDelta);
}

void ULesFightCharacterAnimationComponent::PlayAnimationMontage(
    const FAnimationMontageData& MontageData)
{
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP && MontageData.Montage)
    {
        AnimBP->PlayMontageFromData(MontageData);
        OnMontageStarted.Broadcast(MontageData.Montage);
    }
}

void ULesFightCharacterAnimationComponent::StopAnimationMontage(float BlendOut)
{
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP)
    {
        AnimBP->StopAllMontages(BlendOut);
    }
}

void ULesFightCharacterAnimationComponent::SetLocomotionState(ELocomotionState State)
{
    CurrentLocomotionState = State;
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP) AnimBP->SetLocomotionState(State);
}

void ULesFightCharacterAnimationComponent::SetCombatAnimType(ECombatAnimType Type)
{
    CurrentCombatAnimType = Type;
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP) AnimBP->SetCombatAnimType(Type);
}

void ULesFightCharacterAnimationComponent::SetHitReactionAnim(EHitReactionAnimType ReactionType)
{
    CurrentHitReactionAnim = ReactionType;
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP) AnimBP->SetHitReactionAnim(ReactionType);
}

void ULesFightCharacterAnimationComponent::SetMotionWarpTarget(
    const FMotionWarpTargetData& WarpTarget)
{
    if (MotionWarpingSystem)
    {
        MotionWarpingSystem->SetWarpTarget(WarpTarget);
    }
}

void ULesFightCharacterAnimationComponent::SetFacialExpression(EFacialExpression Expression,
    float BlendTime)
{
    if (FacialSystem)
    {
        FacialSystem->SetExpression(Expression, BlendTime);
    }
}

void ULesFightCharacterAnimationComponent::TriggerAdditiveAnimation(FName SlotName,
    UAnimSequence* AdditiveAnim, float BlendIn)
{
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP)
    {
        AnimBP->TriggerAdditiveAnimation(SlotName, AdditiveAnim, BlendIn);
    }
}

void ULesFightCharacterAnimationComponent::SetAnimationQuality(EAnimationQuality Quality)
{
    if (StateMachine) StateMachine->SetAnimationQuality(Quality);
    if (IKSystem) IKSystem->SetIKQuality(Quality);
    if (BlendingSystem) BlendingSystem->SetBlendQuality(Quality);

    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP) AnimBP->SetAnimationQuality(Quality);
}

void ULesFightCharacterAnimationComponent::SetGlobalPlayRate(float Rate)
{
    GlobalPlayRate = FMath::Clamp(Rate, 0.1f, 3.0f);
}

void ULesFightCharacterAnimationComponent::PauseAnimation()
{
    bAnimationsPaused = true;
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (AnimBP) AnimBP->StopAllMontages(0.0f);
}

void ULesFightCharacterAnimationComponent::ResumeAnimation()
{
    bAnimationsPaused = false;
}

ULesFightAnimBlueprintBase* ULesFightCharacterAnimationComponent::GetAnimBlueprintInstance() const
{
    USkeletalMeshComponent* Mesh = GetMesh();
    if (!Mesh) return nullptr;
    return Cast<ULesFightAnimBlueprintBase>(Mesh->GetAnimInstance());
}

bool ULesFightCharacterAnimationComponent::IsPlayingMontage() const
{
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    return AnimBP && AnimBP->IsPlayingMontage();
}

float ULesFightCharacterAnimationComponent::GetCurrentMontagePlayTime() const
{
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (!AnimBP) return 0.0f;
    UAnimMontage* CurrentMontage = AnimBP->GetCurrentActiveMontage();
    return CurrentMontage ? AnimBP->GetSlotMontageCurrentTime(CurrentMontage->GetSlots()[0].SlotName) : 0.0f;
}

float ULesFightCharacterAnimationComponent::GetNormalizedMontageTime() const
{
    ULesFightAnimBlueprintBase* AnimBP = GetAnimBlueprintInstance();
    if (!AnimBP) return 0.0f;
    UAnimMontage* CurrentMontage = AnimBP->GetCurrentActiveMontage();
    if (!CurrentMontage) return 0.0f;
    float CurrentTime = AnimBP->GetSlotMontageCurrentTime(CurrentMontage->GetSlots()[0].SlotName);
    return CurrentMontage->GetPlayLength() > 0.0f ? CurrentTime / CurrentMontage->GetPlayLength() : 0.0f;
}

USkeletalMeshComponent* ULesFightCharacterAnimationComponent::GetMesh() const
{
    return OwnerFighter.IsValid() ? OwnerFighter->GetMesh() : nullptr;
}

void ULesFightCharacterAnimationComponent::CreateSubSystems(ALesFightBaseFighter* Owner)
{
    StateMachine = NewObject<ULesFightAnimationStateMachine>(this, TEXT("AnimStateMachine"));
    LayerSystem = NewObject<ULesFightAnimationLayerSystem>(this, TEXT("AnimLayerSystem"));
    EventManager = NewObject<ULesFightAnimationEventManager>(this, TEXT("AnimEventManager"));
    LocomotionSystem = NewObject<ULesFightLocomotionSystem>(this, TEXT("LocomotionSystem"));
    CombatAnimHandler = NewObject<ULesFightCombatAnimHandler>(this, TEXT("CombatAnimHandler"));
    BlendingSystem = NewObject<ULesFightBlendingSystem>(this, TEXT("BlendingSystem"));
    RootMotionHandler = NewObject<ULesFightRootMotionHandler>(this, TEXT("RootMotionHandler"));
    MotionWarpingSystem = NewObject<ULesFightMotionWarpingSystem>(this, TEXT("MotionWarpingSystem"));
    IKSystem = NewObject<ULesFightIKSystem>(this, TEXT("IKSystem"));
    HitReactionAnimation = NewObject<ULesFightHitReactionAnimation>(this, TEXT("HitReactionAnimation"));
    FacialSystem = NewObject<ULesFightFacialAnimationSystem>(this, TEXT("FacialSystem"));
}

void ULesFightCharacterAnimationComponent::UpdateAnimationStates(float DeltaTime)
{
    if (!OwnerFighter.IsValid()) return;

    FVector Velocity = OwnerFighter->GetVelocity();
    float Speed2D = Velocity.Size2D();
    bool bInAir = OwnerFighter->GetCharacterMovement()
        ? OwnerFighter->GetCharacterMovement()->IsFalling() : false;
    bool bCrouching = OwnerFighter->bIsCrouched;

    if (bInAir)
    {
        SetLocomotionState(ELocomotionState::Falling);
    }
    else if (bCrouching)
    {
        SetLocomotionState(Speed2D > 10.0f
            ? ELocomotionState::CrouchWalk : ELocomotionState::Crouch);
    }
    else if (Speed2D < 10.0f)
    {
        SetLocomotionState(ELocomotionState::Idle);
    }
    else if (Speed2D < 200.0f)
    {
        SetLocomotionState(ELocomotionState::Walk);
    }
    else if (Speed2D < 450.0f)
    {
        SetLocomotionState(ELocomotionState::Jog);
    }
    else
    {
        SetLocomotionState(ELocomotionState::Sprint);
    }
}

void ULesFightCharacterAnimationComponent::BindCombatEvents()
{
    if (!OwnerFighter.IsValid()) return;
    CombatComponentWeak = OwnerFighter->FindComponentByClass<ULesFightCombatComponent>();
}

bool ULesFightCharacterAnimationComponent::ServerPlayMontage_Validate(const FAnimationMontageData& MontageData) { return true; }
void ULesFightCharacterAnimationComponent::ServerPlayMontage_Implementation(const FAnimationMontageData& MontageData)
{
    PlayAnimationMontage(MontageData);
}

bool ULesFightCharacterAnimationComponent::ServerStopMontage_Validate(float BlendOut) { return true; }
void ULesFightCharacterAnimationComponent::ServerStopMontage_Implementation(float BlendOut)
{
    StopAnimationMontage(BlendOut);
}

bool ULesFightCharacterAnimationComponent::ServerSetLocomotionState_Validate(ELocomotionState State) { return true; }
void ULesFightCharacterAnimationComponent::ServerSetLocomotionState_Implementation(ELocomotionState State)
{
    SetLocomotionState(State);
}

bool ULesFightCharacterAnimationComponent::ServerSetHitReaction_Validate(EHitReactionAnimType ReactionType) { return true; }
void ULesFightCharacterAnimationComponent::ServerSetHitReaction_Implementation(EHitReactionAnimType ReactionType)
{
    SetHitReactionAnim(ReactionType);
}

void ULesFightCharacterAnimationComponent::ClientSyncAnimationState_Implementation(const FNetworkAnimSyncData& AnimData)
{
    if (AnimData.CurrentState != NAME_None)
    {
        SetLocomotionState(static_cast<ELocomotionState>(AnimData.StatePlayTime > 0.5f ? 1 : 0));
    }
}
