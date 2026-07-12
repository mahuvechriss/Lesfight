#include "Framework/FightingAI/Integration/LesFightAIAnimationHandler.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

void ULesFightAIAnimationHandler::PlayAnimation(const FAIDecisionContext& Decision)
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    FName* FoundAnimation = ActionAnimations.Find(Decision.ChosenAction);
    if (FoundAnimation)
    {
        CurrentAnimation = *FoundAnimation;
        bAnimationPlaying = true;
    }
}

FName ULesFightAIAnimationHandler::GetCurrentAnimationName() const
{
    return CurrentAnimation;
}

bool ULesFightAIAnimationHandler::IsAnimationPlaying() const
{
    return bAnimationPlaying;
}

float ULesFightAIAnimationHandler::GetAnimationProgress() const
{
    return 0.0f;
}

void ULesFightAIAnimationHandler::SetAnimationSpeed(float Speed)
{
    AnimationSpeed = Speed;
}

void ULesFightAIAnimationHandler::BlendToAnimation(FName AnimationName, float InBlendTime)
{
    CurrentAnimation = AnimationName;
    BlendTime = InBlendTime;
    bAnimationPlaying = true;
}

void ULesFightAIAnimationHandler::HandleAnimationEvent(EAIAnimationEvent Event)
{
    FName* FoundAnimation = EventAnimations.Find(Event);
    if (FoundAnimation)
    {
        CurrentAnimation = *FoundAnimation;
        bAnimationPlaying = true;
    }
}

bool ULesFightAIAnimationHandler::CanPlayAnimation(FName AnimationName) const
{
    return ActionAnimations.FindKey(AnimationName) != nullptr || EventAnimations.FindKey(AnimationName) != nullptr;
}

FName ULesFightAIAnimationHandler::GetMontageSection(FName MontageName) const
{
    return MontageName;
}

void ULesFightAIAnimationHandler::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;

    ActionAnimations.Empty();
    ActionAnimations.Add(EAIActionType::LightAttack, FName("Attack_Light"));
    ActionAnimations.Add(EAIActionType::HeavyAttack, FName("Attack_Heavy"));
    ActionAnimations.Add(EAIActionType::ComboAttack, FName("Attack_Combo"));
    ActionAnimations.Add(EAIActionType::SpecialMove, FName("Attack_Special"));
    ActionAnimations.Add(EAIActionType::UltimateAttack, FName("Attack_Ultimate"));
    ActionAnimations.Add(EAIActionType::Block, FName("Block_Idle"));
    ActionAnimations.Add(EAIActionType::Dodge, FName("Dodge_Forward"));
    ActionAnimations.Add(EAIActionType::Parry, FName("Parry"));
    ActionAnimations.Add(EAIActionType::Counter, FName("Counter_Punch"));
    ActionAnimations.Add(EAIActionType::Grab, FName("Grab_Attempt"));
    ActionAnimations.Add(EAIActionType::Throw, FName("Throw_Release"));
    ActionAnimations.Add(EAIActionType::StepBack, FName("Step_Back"));
    ActionAnimations.Add(EAIActionType::StepForward, FName("Step_Forward"));
    ActionAnimations.Add(EAIActionType::Sidestep, FName("Sidestep"));
    ActionAnimations.Add(EAIActionType::Jump, FName("Jump"));
    ActionAnimations.Add(EAIActionType::Crouch, FName("Crouch"));
    ActionAnimations.Add(EAIActionType::Taunt, FName("Taunt"));
    ActionAnimations.Add(EAIActionType::Recover, FName("Recover"));
    ActionAnimations.Add(EAIActionType::Wait, FName("Wait_Idle"));

    EventAnimations.Empty();
    EventAnimations.Add(EAIAnimationEvent::AttackStart, FName("Attack_Light"));
    EventAnimations.Add(EAIAnimationEvent::AttackHit, FName("Hit_Reaction"));
    EventAnimations.Add(EAIAnimationEvent::AttackMiss, FName("Miss_Recovery"));
    EventAnimations.Add(EAIAnimationEvent::ComboStart, FName("Combo_Start"));
    EventAnimations.Add(EAIAnimationEvent::ComboEnd, FName("Combo_End"));
    EventAnimations.Add(EAIAnimationEvent::BlockStart, FName("Block_Idle"));
    EventAnimations.Add(EAIAnimationEvent::BlockHit, FName("Block_Hit"));
    EventAnimations.Add(EAIAnimationEvent::DodgeStart, FName("Dodge_Forward"));
    EventAnimations.Add(EAIAnimationEvent::DodgeComplete, FName("Dodge_Recover"));
    EventAnimations.Add(EAIAnimationEvent::ParrySuccess, FName("Parry_Success"));
    EventAnimations.Add(EAIAnimationEvent::CounterStart, FName("Counter_Punch"));
    EventAnimations.Add(EAIAnimationEvent::CounterHit, FName("Counter_Hit"));
    EventAnimations.Add(EAIAnimationEvent::GetHit, FName("Get_Hit"));
    EventAnimations.Add(EAIAnimationEvent::Knockdown, FName("Knockdown"));
    EventAnimations.Add(EAIAnimationEvent::GetUp, FName("GetUp"));
    EventAnimations.Add(EAIAnimationEvent::Stunned, FName("Stunned"));
    EventAnimations.Add(EAIAnimationEvent::RecoverStart, FName("Recover_Start"));
    EventAnimations.Add(EAIAnimationEvent::RecoverEnd, FName("Recover_End"));
    EventAnimations.Add(EAIAnimationEvent::Taunt, FName("Taunt"));
    EventAnimations.Add(EAIAnimationEvent::Victory, FName("Victory"));
    EventAnimations.Add(EAIAnimationEvent::Defeat, FName("Defeat"));
}
