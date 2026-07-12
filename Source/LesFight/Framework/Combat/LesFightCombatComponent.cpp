#include "LesFightCombatComponent.h"
#include "LesFightComboManager.h"
#include "LesFightDamageManager.h"
#include "LesFightHitDetection.h"
#include "LesFightInputBuffer.h"
#include "LesFightBlockingComponent.h"
#include "LesFightDodgeComponent.h"
#include "LesFightThrowComponent.h"
#include "LesFightSpecialMoveComponent.h"
#include "LesFightUltimateMoveComponent.h"
#include "LesFightCombatEffects.h"
#include "LesFightReactionSystem.h"
#include "LesFightBaseFighter.h"
#include "LesFightCombatDataAsset.h"
#include "LesFightHealthComponent.h"
#include "LesFightStaminaComponent.h"
#include "LesFightAnimationComponent.h"
#include "LesFight.h"
#include "LesFightNetworkPlayerController.h"
#include "Net/UnrealNetwork.h"

ULesFightCombatComponent::ULesFightCombatComponent()
    : bIsAttacking(false)
    , bCombatEnabled(true)
    , CurrentAttackType(EAttackType::LightPunch)
    , ComboCount(0)
    , CurrentFrameTimer(0.0f)
    , CurrentFrame(0)
    , TotalFrames(0)
    , CurrentPhase(EAttackPhase::None)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.0f;
    SetIsReplicatedByDefault(true);
}

void ULesFightCombatComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bCombatEnabled) return;

    if (bIsAttacking)
    {
        UpdateAttackFrames(DeltaTime);
    }

    UpdateCooldowns(DeltaTime);

    if (InputBuffer && InputBuffer->HasPendingInput() && CanAttack())
    {
        FBufferedInput Pending = InputBuffer->ConsumeNextInput();
        if (!Pending.InputID.IsNone())
        {
            PerformAttack(Pending.InputID);
        }
    }

    if (BlockingComponent)
    {
        BlockingComponent->ApplyGuardRegen(DeltaTime);
    }

    if (UltimateMoveComponent)
    {
        UltimateMoveComponent->AddMeter(DeltaTime * 2.0f);
    }
}

void ULesFightCombatComponent::Initialize(ALesFightBaseFighter* InOwner,
    ULesFightCombatDataAsset* CombatData)
{
    OwnerFighter = InOwner;
    CombatDataAsset = CombatData;

    if (!OwnerFighter) return;

    CreateSubManagers(OwnerFighter);

    if (CombatData)
    {
        for (const FAttackDefinition& Attack : CombatData->BasicAttacks)
        {
            AttackMap.Add(Attack.AttackID, Attack);
        }
        for (const FSpecialMoveDefinition& Special : CombatData->SpecialMoves)
        {
            if (SpecialMoveComponent)
            {
                SpecialMoveComponent->RegisterSpecialMove(Special);
            }
            if (AttackMap.Contains(Special.AttackData.AttackID))
            {
                AttackMap.Add(Special.AttackData.AttackID, Special.AttackData);
            }
        }
        for (const FUltimateMoveDefinition& Ultimate : CombatData->UltimateMoves)
        {
            if (UltimateMoveComponent)
            {
                UltimateMoveComponent->RegisterUltimateMove(Ultimate);
            }
            if (AttackMap.Contains(Ultimate.AttackData.AttackID))
            {
                AttackMap.Add(Ultimate.AttackData.AttackID, Ultimate.AttackData);
            }
        }
        for (const FComboDefinition& Combo : CombatData->Combos)
        {
            if (Combo.ComboSequence.Num() > 0)
            {
                for (const FComboEntry& Entry : Combo.ComboSequence)
                {
                    if (!AttackMap.Contains(Entry.AttackID))
                    {
                        AttackMap.Add(Entry.AttackID, Entry.AttackData);
                    }
                }
            }
        }
    }
    else
    {
        SetupDefaultAttacks();
    }

    if (ComboManager) ComboManager->Initialize(this, CombatData);
    if (DamageManager) DamageManager->Initialize();
    if (HitDetection) HitDetection->Initialize(OwnerFighter);
    if (BlockingComponent) BlockingComponent->Initialize(OwnerFighter);
    if (DodgeComponent) DodgeComponent->Initialize(OwnerFighter);
    if (ThrowComponent) ThrowComponent->Initialize(OwnerFighter);
    if (SpecialMoveComponent) SpecialMoveComponent->Initialize(OwnerFighter);
    if (UltimateMoveComponent) UltimateMoveComponent->Initialize(OwnerFighter);
    if (CombatEffects) CombatEffects->Initialize(OwnerFighter);
    if (ReactionSystem) ReactionSystem->Initialize(OwnerFighter);
    if (InputBuffer) InputBuffer->Initialize();

    UE_LOG(LogLesFight, Log, TEXT("CombatComponent fully initialized with %d attacks"),
        AttackMap.Num());
}

void ULesFightCombatComponent::InitializeDefault(ALesFightBaseFighter* InOwner)
{
    Initialize(InOwner, nullptr);
}

void ULesFightCombatComponent::PerformLightPunch()
{
    FName AttackID = FName(TEXT("LightPunch"));
    InputBuffer->BufferInput(AttackID, EAttackType::LightPunch);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformHeavyPunch()
{
    FName AttackID = FName(TEXT("HeavyPunch"));
    InputBuffer->BufferInput(AttackID, EAttackType::HeavyPunch);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformLightKick()
{
    FName AttackID = FName(TEXT("LightKick"));
    InputBuffer->BufferInput(AttackID, EAttackType::LightKick);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformHeavyKick()
{
    FName AttackID = FName(TEXT("HeavyKick"));
    InputBuffer->BufferInput(AttackID, EAttackType::HeavyKick);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformJumpAttack()
{
    bool bInAir = OwnerFighter && OwnerFighter->GetCharacterMovement()
        && OwnerFighter->GetCharacterMovement()->IsFalling();
    FName AttackID = bInAir ? FName(TEXT("JumpKick")) : FName(TEXT("JumpPunch"));
    InputBuffer->BufferInput(AttackID, bInAir ? EAttackType::LightKick : EAttackType::LightPunch);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformCrouchAttack()
{
    bool bCrouching = OwnerFighter && OwnerFighter->GetCharacterMovement()
        && OwnerFighter->GetCharacterMovement()->IsCrouching();
    FName AttackID = bCrouching ? FName(TEXT("CrouchKick")) : FName(TEXT("CrouchPunch"));
    InputBuffer->BufferInput(AttackID, bCrouching ? EAttackType::LightKick : EAttackType::LightPunch);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformDashAttack()
{
    FName AttackID = FName(TEXT("DashAttack"));
    InputBuffer->BufferInput(AttackID, EAttackType::HeavyPunch);

    if (CanAttack())
    {
        PerformAttack(AttackID);
    }
}

void ULesFightCombatComponent::PerformAttack(FName AttackID)
{
    if (!bCombatEnabled) return;

    FBufferedInput Pending = InputBuffer ? InputBuffer->PeekNextInput() : FBufferedInput();
    if (!Pending.bConsumed && Pending.InputID != AttackID)
    {
        InputBuffer->ClearBuffer();
    }

    if (!CanAttack() || !AttackMap.Contains(AttackID)) return;

    if (IsOnCooldown(AttackID)) return;

    const FAttackDefinition& Attack = AttackMap[AttackID];

    ULesFightStaminaComponent* Stamina = OwnerFighter
        ? OwnerFighter->GetStaminaComponent() : nullptr;
    if (Stamina && !Stamina->ConsumeStamina(Attack.DamageData.StaminaCost))
    {
        return;
    }

    ExecuteAttack(Attack);
}

void ULesFightCombatComponent::PerformBlock(EBlockType BlockType)
{
    if (!bCombatEnabled || !BlockingComponent) return;

    EBlockState BlockState = EBlockState::Standing;
    switch (BlockType)
    {
    case EBlockType::Standing:  BlockState = EBlockState::Standing; break;
    case EBlockType::Crouching: BlockState = EBlockState::Crouching; break;
    case EBlockType::Air:       BlockState = EBlockState::AirBlock; break;
    }

    BlockingComponent->StartBlocking(BlockState);
}

void ULesFightCombatComponent::ReleaseBlock()
{
    if (BlockingComponent)
    {
        BlockingComponent->StopBlocking();
    }
}

void ULesFightCombatComponent::PerformDodge(EDodgeType DodgeType)
{
    if (!bCombatEnabled || !DodgeComponent || !OwnerFighter) return;

    FVector DodgeDirection = FVector::ZeroVector;
    FVector OwnerForward = OwnerFighter->GetActorForwardVector();
    FVector OwnerRight = OwnerFighter->GetActorRightVector();

    switch (DodgeType)
    {
    case EDodgeType::ForwardDash: DodgeDirection = OwnerForward; break;
    case EDodgeType::BackDash:    DodgeDirection = -OwnerForward; break;
    case EDodgeType::SideStep:    DodgeDirection = OwnerRight; break;
    }

    if (DodgeDirection.IsNearlyZero())
    {
        DodgeDirection = OwnerForward;
    }

    DodgeComponent->StartDodge(DodgeDirection);
}

void ULesFightCombatComponent::PerformThrow()
{
    if (!bCombatEnabled || !ThrowComponent || !OwnerFighter) return;

    if (!CanAttack()) return;

    ThrowComponent->StartThrow();

    FHitResultData ThrowResult = HitDetection->PerformThrowCheck();
    if (ThrowResult.bHit)
    {
        ThrowComponent->PerformThrow();

        ALesFightBaseFighter* Target = Cast<ALesFightBaseFighter>(ThrowResult.HitActor);
        if (Target)
        {
            float ThrowDmg = ThrowComponent->GetThrowDamage();
            ULesFightHealthComponent* Health = Target->GetHealthComponent();
            if (Health)
            {
                Health->TakeDamage(ThrowDmg, OwnerFighter);
            }
        }
    }
    else
    {
        ThrowComponent->EndThrow();
    }
}

void ULesFightCombatComponent::PerformSpecialMove(int32 MoveIndex)
{
    if (!bCombatEnabled || !SpecialMoveComponent || !CombatDataAsset) return;

    if (!CombatDataAsset->SpecialMoves.IsValidIndex(MoveIndex)) return;

    const FSpecialMoveDefinition& Special = CombatDataAsset->SpecialMoves[MoveIndex];

    if (!SpecialMoveComponent->TryExecuteSpecialMove(Special.MoveID)) return;

    if (AttackMap.Contains(Special.AttackData.AttackID))
    {
        ExecuteAttack(AttackMap[Special.AttackData.AttackID]);
        CooldownMap.Add(Special.MoveID, FMath::RoundToInt(Special.CooldownTime));
    }
}

void ULesFightCombatComponent::PerformUltimate()
{
    if (!bCombatEnabled || !UltimateMoveComponent || !CombatDataAsset) return;

    if (CombatDataAsset->UltimateMoves.Num() == 0) return;

    const FUltimateMoveDefinition& Ultimate = CombatDataAsset->UltimateMoves[0];

    if (!UltimateMoveComponent->TryExecuteUltimate(Ultimate.MoveID)) return;

    if (AttackMap.Contains(Ultimate.AttackData.AttackID))
    {
        ExecuteAttack(AttackMap[Ultimate.AttackData.AttackID]);
    }
}

void ULesFightCombatComponent::OnRoundStart()
{
    bCombatEnabled = true;
    ComboCount = 0;
    bIsAttacking = false;
    CurrentPhase = EAttackPhase::None;

    if (ComboManager) ComboManager->ResetCombo();
    if (BlockingComponent) BlockingComponent->ResetGuardMeter();
    if (DodgeComponent) DodgeComponent->ResetDodge();
    if (UltimateMoveComponent) UltimateMoveComponent->ResetMeter();
    if (InputBuffer) InputBuffer->ClearBuffer();
    if (HitDetection) HitDetection->ResetHitActors();

    OnRoundStartEvent.Broadcast(1);
}

void ULesFightCombatComponent::OnRoundEnd()
{
    bCombatEnabled = false;

    if (bIsAttacking)
    {
        EndAttack();
    }
    ReleaseBlock();

    if (DodgeComponent && DodgeComponent->IsDodging())
    {
        DodgeComponent->EndDodge();
    }

    OnRoundEndEvent.Broadcast(false);
}

bool ULesFightCombatComponent::CanAttack() const
{
    if (!bCombatEnabled) return false;
    if (bIsAttacking) return false;
    if (BlockingComponent && BlockingComponent->IsBlocking()) return false;
    if (DodgeComponent && DodgeComponent->IsDodging()) return false;
    if (ReactionSystem && !ReactionSystem->CanAct()) return false;
    if (!OwnerFighter) return false;
    ULesFightHealthComponent* HC = OwnerFighter->GetHealthComponent();
    if (!HC || HC->GetCurrentHealth() <= 0.0f) return false;
    return true;
}

void ULesFightCombatComponent::ExecuteAttack(const FAttackDefinition& Attack)
{
    bIsAttacking = true;
    CurrentAttackID = Attack.AttackID;
    CurrentAttackType = Attack.AttackType;
    CurrentAttackDefinition = Attack;
    CurrentFrameData = Attack.FrameData;
    CurrentFrame = 0;
    CurrentFrameTimer = 0.0f;
    TotalFrames = Attack.FrameData.StartupFrames + Attack.FrameData.ActiveFrames
        + Attack.FrameData.RecoveryFrames;
    CurrentPhase = EAttackPhase::Startup;

    HitDetection->ResetHitActors();
    HitDetection->SetHitboxEnabled(true);

    if (OwnerFighter)
    {
        if (UCharacterMovementComponent* MoveComp = OwnerFighter->GetCharacterMovement())
        {
            MoveComp->SetMovementMode(MOVE_None);
        }
    }

    OnAttackStarted.Broadcast(Attack.AttackID, Attack.AttackType);
    UE_LOG(LogLesFight, Verbose, TEXT("Attack started: %s (Startup=%d, Active=%d, Recovery=%d)"),
        *Attack.AttackID.ToString(),
        Attack.FrameData.StartupFrames,
        Attack.FrameData.ActiveFrames,
        Attack.FrameData.RecoveryFrames);
}

void ULesFightCombatComponent::UpdateAttackFrames(float DeltaTime)
{
    const float FrameDuration = 1.0f / 60.0f;
    CurrentFrameTimer += DeltaTime;

    while (CurrentFrameTimer >= FrameDuration)
    {
        CurrentFrameTimer -= FrameDuration;
        CurrentFrame++;

        int32 Start = CurrentFrameData.StartupFrames;
        int32 Active = CurrentFrameData.ActiveFrames;
        int32 Recovery = CurrentFrameData.RecoveryFrames;

        if (CurrentFrame <= Start)
        {
            CurrentPhase = EAttackPhase::Startup;
        }
        else if (CurrentFrame <= Start + Active)
        {
            CurrentPhase = EAttackPhase::Active;

            FHitResultData HitResult = HitDetection->PerformHitCheck(CurrentAttackID);
            if (HitResult.bHit)
            {
                ProcessHit(HitResult.HitActor);
            }
        }
        else if (CurrentFrame <= Start + Active + Recovery)
        {
            CurrentPhase = EAttackPhase::Recovery;
        }

        if (CurrentFrame >= TotalFrames)
        {
            EndAttack();
            break;
        }
    }
}

void ULesFightCombatComponent::OnAttackConnect(AActor* Target)
{
}

void ULesFightCombatComponent::ProcessHit(AActor* Target)
{
    if (!Target || !OwnerFighter) return;

    ALesFightBaseFighter* TargetFighter = Cast<ALesFightBaseFighter>(Target);
    if (!TargetFighter) return;

    ULesFightCombatComponent* TargetCombat = TargetFighter->FindComponentByClass<ULesFightCombatComponent>();
    if (!TargetCombat) return;

    bool bIsBlocked = TargetCombat->BlockingComponent && TargetCombat->BlockingComponent->IsBlocking()
        && TargetCombat->BlockingComponent->TryBlock(CurrentAttackDefinition, OwnerFighter);

    FDamageResult DamageResult = DamageManager->CalculateFullDamage(
        CurrentAttackDefinition, ComboCount, bIsBlocked);

    ULesFightHealthComponent* TargetHealth = TargetFighter->GetHealthComponent();
    if (TargetHealth)
    {
        TargetHealth->TakeDamage(DamageResult.FinalDamage, OwnerFighter);
    }

    FVector HitDirection = (Target->GetActorLocation() - OwnerFighter->GetActorLocation()).GetSafeNormal();

    if (bIsBlocked)
    {
        TargetCombat->ReactionSystem->ApplyBlockReaction(CurrentAttackDefinition, HitDirection);
        CombatEffects->PlayBlockEffect(Target->GetActorLocation(), HitDirection.Rotation());
    }
    else
    {
        TargetCombat->ReactionSystem->ApplyHitReaction(CurrentAttackDefinition, HitDirection,
            DamageResult.FinalDamage);

        CombatEffects->PlayHitEffect(Target->GetActorLocation(),
            HitDirection.Rotation(), DamageResult.HitReaction);

        CombatEffects->TriggerHitstop();
    }

    if (!bIsBlocked)
    {
        ComboCount++;
        ComboManager->RegisterHit(CurrentAttackID);
        OnComboUpdated.Broadcast(ComboCount);
    }

    OnAttackHit.Broadcast(CurrentAttackID, Target);

    if (UltimateMoveComponent)
    {
        UltimateMoveComponent->AddMeter(DamageResult.FinalDamage * 0.5f);
    }

    OnFighterHit.Broadcast(TargetFighter, DamageResult);

    UE_LOG(LogLesFight, Verbose,
        TEXT("Attack %s -> %s: damage=%.1f (base=%.1f, scaled=%.1f), blocked=%d, combo=%d"),
        *CurrentAttackID.ToString(), *Target->GetName(),
        DamageResult.FinalDamage, DamageResult.BaseDamage, DamageResult.ScaledDamage,
        bIsBlocked, ComboCount);
}

void ULesFightCombatComponent::EndAttack()
{
    bIsAttacking = false;
    CurrentPhase = EAttackPhase::None;
    CurrentFrame = 0;
    CurrentFrameTimer = 0.0f;

    HitDetection->SetHitboxEnabled(false);

    if (OwnerFighter)
    {
        if (UCharacterMovementComponent* MoveComp = OwnerFighter->GetCharacterMovement())
        {
            MoveComp->SetMovementMode(MOVE_Walking);
        }
    }

    OnAttackRecovered.Broadcast();
}

void ULesFightCombatComponent::UpdateCooldowns(float DeltaTime)
{
    TArray<FName> ToRemove;
    for (auto& Pair : CooldownMap)
    {
        Pair.Value = FMath::Max(0, Pair.Value - 1);
        if (Pair.Value <= 0) ToRemove.Add(Pair.Key);
    }
    for (const FName& Key : ToRemove)
    {
        CooldownMap.Remove(Key);
    }
}

void ULesFightCombatComponent::ExecuteAttackByID(FName AttackID)
{
    PerformAttack(AttackID);
}

void ULesFightCombatComponent::CreateSubManagers(ALesFightBaseFighter* Owner)
{
    DamageManager = NewObject<ULesFightDamageManager>(this, TEXT("DamageManager"));
    HitDetection = NewObject<ULesFightHitDetection>(this, TEXT("HitDetection"));
    InputBuffer = NewObject<ULesFightInputBuffer>(this, TEXT("InputBuffer"));
    CombatEffects = NewObject<ULesFightCombatEffects>(this, TEXT("CombatEffects"));
    ReactionSystem = NewObject<ULesFightReactionSystem>(this, TEXT("ReactionSystem"));

    ComboManager = NewObject<ULesFightComboManager>(Owner, TEXT("ComboManager"));
    ComboManager->RegisterComponent();

    BlockingComponent = NewObject<ULesFightBlockingComponent>(Owner, TEXT("BlockingComponent"));
    BlockingComponent->RegisterComponent();

    DodgeComponent = NewObject<ULesFightDodgeComponent>(Owner, TEXT("DodgeComponent"));
    DodgeComponent->RegisterComponent();

    ThrowComponent = NewObject<ULesFightThrowComponent>(Owner, TEXT("ThrowComponent"));
    ThrowComponent->RegisterComponent();

    SpecialMoveComponent = NewObject<ULesFightSpecialMoveComponent>(Owner, TEXT("SpecialMoveComponent"));
    SpecialMoveComponent->RegisterComponent();

    UltimateMoveComponent = NewObject<ULesFightUltimateMoveComponent>(Owner, TEXT("UltimateMoveComponent"));
    UltimateMoveComponent->RegisterComponent();
}

void ULesFightCombatComponent::SetupDefaultAttacks()
{
    FAttackDefinition LightPunch;
    LightPunch.AttackID = FName(TEXT("LightPunch"));
    LightPunch.AttackName = TEXT("Light Punch");
    LightPunch.AttackType = EAttackType::LightPunch;
    LightPunch.FrameData.StartupFrames = 4;
    LightPunch.FrameData.ActiveFrames = 2;
    LightPunch.FrameData.RecoveryFrames = 6;
    LightPunch.FrameData.HitstunFrames = 10;
    LightPunch.FrameData.BlockstunFrames = 5;
    LightPunch.DamageData.BaseDamage = 10.0f;
    LightPunch.DamageData.KnockbackForce = 50.0f;
    LightPunch.DamageData.LaunchForce = 0.0f;
    LightPunch.DamageData.StaminaCost = 5.0f;
    LightPunch.DamageData.bCanCrit = false;
    LightPunch.Properties.HitReaction = EHitReaction::LightStun;
    LightPunch.Properties.AntiBlock = EAntiBlock::None;
    LightPunch.Properties.AttackRange = 80.0f;
    LightPunch.Properties.AttackHeight = EAttackHeight::Standing;
    AttackMap.Add(LightPunch.AttackID, LightPunch);

    FAttackDefinition HeavyPunch;
    HeavyPunch.AttackID = FName(TEXT("HeavyPunch"));
    HeavyPunch.AttackName = TEXT("Heavy Punch");
    HeavyPunch.AttackType = EAttackType::HeavyPunch;
    HeavyPunch.FrameData.StartupFrames = 8;
    HeavyPunch.FrameData.ActiveFrames = 3;
    HeavyPunch.FrameData.RecoveryFrames = 10;
    HeavyPunch.FrameData.HitstunFrames = 18;
    HeavyPunch.FrameData.BlockstunFrames = 8;
    HeavyPunch.DamageData.BaseDamage = 25.0f;
    HeavyPunch.DamageData.KnockbackForce = 120.0f;
    HeavyPunch.DamageData.LaunchForce = 50.0f;
    HeavyPunch.DamageData.StaminaCost = 10.0f;
    HeavyPunch.DamageData.bCanCrit = true;
    HeavyPunch.DamageData.CritMultiplier = 1.5f;
    HeavyPunch.Properties.HitReaction = EHitReaction::HeavyStun;
    HeavyPunch.Properties.AntiBlock = EAntiBlock::None;
    HeavyPunch.Properties.AttackRange = 90.0f;
    HeavyPunch.Properties.AttackHeight = EAttackHeight::Standing;
    AttackMap.Add(HeavyPunch.AttackID, HeavyPunch);

    FAttackDefinition LightKick;
    LightKick.AttackID = FName(TEXT("LightKick"));
    LightKick.AttackName = TEXT("Light Kick");
    LightKick.AttackType = EAttackType::LightKick;
    LightKick.FrameData.StartupFrames = 5;
    LightKick.FrameData.ActiveFrames = 3;
    LightKick.FrameData.RecoveryFrames = 8;
    LightKick.FrameData.HitstunFrames = 12;
    LightKick.FrameData.BlockstunFrames = 6;
    LightKick.DamageData.BaseDamage = 12.0f;
    LightKick.DamageData.KnockbackForce = 60.0f;
    LightKick.DamageData.LaunchForce = 0.0f;
    LightKick.DamageData.StaminaCost = 6.0f;
    LightKick.DamageData.bCanCrit = false;
    LightKick.Properties.HitReaction = EHitReaction::LightStun;
    LightKick.Properties.AntiBlock = EAntiBlock::None;
    LightKick.Properties.AttackRange = 100.0f;
    LightKick.Properties.AttackHeight = EAttackHeight::Standing;
    AttackMap.Add(LightKick.AttackID, LightKick);

    FAttackDefinition HeavyKick;
    HeavyKick.AttackID = FName(TEXT("HeavyKick"));
    HeavyKick.AttackName = TEXT("Heavy Kick");
    HeavyKick.AttackType = EAttackType::HeavyKick;
    HeavyKick.FrameData.StartupFrames = 10;
    HeavyKick.FrameData.ActiveFrames = 4;
    HeavyKick.FrameData.RecoveryFrames = 14;
    HeavyKick.FrameData.HitstunFrames = 20;
    HeavyKick.FrameData.BlockstunFrames = 10;
    HeavyKick.DamageData.BaseDamage = 30.0f;
    HeavyKick.DamageData.KnockbackForce = 150.0f;
    HeavyKick.DamageData.LaunchForce = 80.0f;
    HeavyKick.DamageData.StaminaCost = 12.0f;
    HeavyKick.DamageData.bCanCrit = true;
    HeavyKick.DamageData.CritMultiplier = 1.5f;
    HeavyKick.Properties.HitReaction = EHitReaction::Knockback;
    HeavyKick.Properties.AntiBlock = EAntiBlock::None;
    HeavyKick.Properties.AttackRange = 110.0f;
    HeavyKick.Properties.AttackHeight = EAttackHeight::Standing;
    AttackMap.Add(HeavyKick.AttackID, HeavyKick);

    FAttackDefinition JumpPunch;
    JumpPunch.AttackID = FName(TEXT("JumpPunch"));
    JumpPunch.AttackName = TEXT("Jump Punch");
    JumpPunch.AttackType = EAttackType::LightPunch;
    JumpPunch.FrameData.StartupFrames = 6;
    JumpPunch.FrameData.ActiveFrames = 4;
    JumpPunch.FrameData.RecoveryFrames = 4;
    JumpPunch.FrameData.HitstunFrames = 14;
    JumpPunch.FrameData.BlockstunFrames = 7;
    JumpPunch.DamageData.BaseDamage = 15.0f;
    JumpPunch.DamageData.KnockbackForce = 80.0f;
    JumpPunch.DamageData.LaunchForce = 30.0f;
    JumpPunch.DamageData.StaminaCost = 8.0f;
    JumpPunch.Properties.HitReaction = EHitReaction::AirHit;
    JumpPunch.Properties.AttackRange = 90.0f;
    JumpPunch.Properties.AttackHeight = EAttackHeight::Air;
    AttackMap.Add(JumpPunch.AttackID, JumpPunch);

    FAttackDefinition CrouchPunch;
    CrouchPunch.AttackID = FName(TEXT("CrouchPunch"));
    CrouchPunch.AttackName = TEXT("Crouch Punch");
    CrouchPunch.AttackType = EAttackType::LightPunch;
    CrouchPunch.FrameData.StartupFrames = 5;
    CrouchPunch.FrameData.ActiveFrames = 3;
    CrouchPunch.FrameData.RecoveryFrames = 7;
    CrouchPunch.FrameData.HitstunFrames = 11;
    CrouchPunch.FrameData.BlockstunFrames = 6;
    CrouchPunch.DamageData.BaseDamage = 11.0f;
    CrouchPunch.DamageData.KnockbackForce = 55.0f;
    CrouchPunch.DamageData.StaminaCost = 6.0f;
    CrouchPunch.Properties.HitReaction = EHitReaction::LightStun;
    CrouchPunch.Properties.AttackRange = 75.0f;
    CrouchPunch.Properties.AttackHeight = EAttackHeight::Crouching;
    AttackMap.Add(CrouchPunch.AttackID, CrouchPunch);

    FAttackDefinition DashAttack;
    DashAttack.AttackID = FName(TEXT("DashAttack"));
    DashAttack.AttackName = TEXT("Dash Attack");
    DashAttack.AttackType = EAttackType::HeavyPunch;
    DashAttack.FrameData.StartupFrames = 6;
    DashAttack.FrameData.ActiveFrames = 4;
    DashAttack.FrameData.RecoveryFrames = 12;
    DashAttack.FrameData.HitstunFrames = 16;
    DashAttack.FrameData.BlockstunFrames = 8;
    DashAttack.DamageData.BaseDamage = 20.0f;
    DashAttack.DamageData.KnockbackForce = 100.0f;
    DashAttack.DamageData.StaminaCost = 10.0f;
    DashAttack.Properties.HitReaction = EHitReaction::HeavyStun;
    DashAttack.AttackRange = 120.0f;
    DashAttack.Properties.AttackHeight = EAttackHeight::Standing;
    AttackMap.Add(DashAttack.AttackID, DashAttack);
}

bool ULesFightCombatComponent::IsOnCooldown(FName AttackID) const
{
    const int32* Cooldown = CooldownMap.Find(AttackID);
    return Cooldown && *Cooldown > 0;
}

void ULesFightCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool ULesFightCombatComponent::ServerPerformAttack_Validate(FName AttackID) { return true; }
void ULesFightCombatComponent::ServerPerformAttack_Implementation(FName AttackID)
{
    PerformAttack(AttackID);
}

bool ULesFightCombatComponent::ServerPerformBlock_Validate(EBlockType BlockType) { return true; }
void ULesFightCombatComponent::ServerPerformBlock_Implementation(EBlockType BlockType)
{
    PerformBlock(BlockType);
}

bool ULesFightCombatComponent::ServerReleaseBlock_Validate() { return true; }
void ULesFightCombatComponent::ServerReleaseBlock_Implementation()
{
    ReleaseBlock();
}

bool ULesFightCombatComponent::ServerPerformDodge_Validate(EDodgeType DodgeType) { return true; }
void ULesFightCombatComponent::ServerPerformDodge_Implementation(EDodgeType DodgeType)
{
    PerformDodge(DodgeType);
}

bool ULesFightCombatComponent::ServerPerformThrow_Validate() { return true; }
void ULesFightCombatComponent::ServerPerformThrow_Implementation()
{
    PerformThrow();
}

bool ULesFightCombatComponent::ServerPerformSpecialMove_Validate(int32 MoveIndex) { return true; }
void ULesFightCombatComponent::ServerPerformSpecialMove_Implementation(int32 MoveIndex)
{
    PerformSpecialMove(MoveIndex);
}

bool ULesFightCombatComponent::ServerPerformUltimate_Validate() { return true; }
void ULesFightCombatComponent::ServerPerformUltimate_Implementation()
{
    PerformUltimate();
}

void ULesFightCombatComponent::ClientOnAttackHit_Implementation(
    AActor* Target, const FDamageResult& DamageResult)
{
    OnFighterHit.Broadcast(Target, DamageResult);
}

void ULesFightCombatComponent::ClientOnAttackMissed_Implementation()
{
    OnAttackMissed.Broadcast();
}

void ULesFightCombatComponent::ClientOnAttackStarted_Implementation(
    FName InAttackID, EAttackType InAttackType)
{
    OnAttackStarted.Broadcast(InAttackID, InAttackType);
}

void ULesFightCombatComponent::ClientOnComboUpdated_Implementation(int32 InComboCount)
{
    OnComboUpdated.Broadcast(InComboCount);
}

void ULesFightCombatComponent::ClientOnComboBroken_Implementation()
{
    OnComboBroken.Broadcast();
}

void ULesFightCombatComponent::ClientOnAttackRecovered_Implementation()
{
    OnAttackRecovered.Broadcast();
}
