#include "LesFightHitDetection.h"
#include "LesFightCombatComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ULesFightHitDetection::ULesFightHitDetection()
    : HitboxForwardOffset(80.0f)
    , HitboxRadius(30.0f)
    , HitboxHalfHeight(40.0f)
    , ThrowRange(150.0f)
    , bHitboxEnabled(true)
    , bDebugDrawHitbox(false)
{
}

void ULesFightHitDetection::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
}

FHitResultData ULesFightHitDetection::PerformHitCheck(FName AttackID)
{
    FHitResultData Result;

    if (!bHitboxEnabled || !OwnerFighter.IsValid()) return Result;

    FVector OwnerLocation = OwnerFighter->GetActorLocation();
    FVector OwnerForward = OwnerFighter->GetActorForwardVector();

    CurrentHitbox.BoneName = NAME_None;
    CurrentHitbox.Location = OwnerForward * HitboxForwardOffset;
    CurrentHitbox.Extents = FVector(HitboxRadius, HitboxRadius, HitboxHalfHeight);
    CurrentHitbox.ActiveStartFrame = 0;
    CurrentHitbox.ActiveEndFrame = 5;

    if (bDebugDrawHitbox)
    {
        DrawDebugHitbox(CurrentHitbox);
    }

    TArray<FHitResult> HitResults;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(OwnerFighter.Get());

    FVector BoxCenter = OwnerLocation + CurrentHitbox.Location;
    FBox HitBox(BoxCenter - CurrentHitbox.Extents, BoxCenter + CurrentHitbox.Extents);

    bool bHit = GetWorld()->SweepMultiByChannel(HitResults, BoxCenter, BoxCenter,
        FQuat::Identity, ECC_WorldDynamic, FCollisionShape::MakeBox(CurrentHitbox.Extents), QueryParams);

    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            ALesFightBaseFighter* HitFighter = Cast<ALesFightBaseFighter>(Hit.GetActor());
            if (HitFighter && !HasHitThisAttack(HitFighter))
            {
                Result.bHit = true;
                Result.HitActor = HitFighter;
                Result.HitLocation = Hit.Location;
                Result.HitNormal = Hit.Normal;
                Result.HitBone = Hit.BoneName;
                Result.BlockType = IsAttackBlocked(HitFighter) ? EBlockType::Standing : EBlockType::None;

                HitActorsThisAttack.Add(HitFighter);
                OnHitConfirmed.Broadcast(HitFighter, Hit);

                UE_LOG(LogLesFight, Verbose, TEXT("Hit confirmed on %s"), *HitFighter->GetName());
                break;
            }
        }
    }

    if (!Result.bHit)
    {
        OnHitMissed.Broadcast();
    }

    return Result;
}

FHitResultData ULesFightHitDetection::PerformThrowCheck()
{
    FHitResultData Result;

    if (!OwnerFighter.IsValid()) return Result;

    FVector Start = OwnerFighter->GetActorLocation();
    FVector End = Start + OwnerFighter->GetActorForwardVector() * ThrowRange;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(OwnerFighter.Get());

    FHitResult Hit;
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, QueryParams);

    if (bHit)
    {
        ALesFightBaseFighter* Target = Cast<ALesFightBaseFighter>(Hit.GetActor());
        if (Target)
        {
            Result.bHit = true;
            Result.HitActor = Target;
            UE_LOG(LogLesFight, Verbose, TEXT("Throw connected on %s"), *Target->GetName());
        }
    }

    return Result;
}

void ULesFightHitDetection::ResetHitActors()
{
    HitActorsThisAttack.Empty();
}

bool ULesFightHitDetection::HasHitThisAttack(AActor* Actor) const
{
    return HitActorsThisAttack.Contains(Actor);
}

void ULesFightHitDetection::DrawDebugHitbox(const FHitboxShape& Hitbox)
{
    if (!OwnerFighter.IsValid() || !GetWorld()) return;

    FVector Center = OwnerFighter->GetActorLocation() + Hitbox.Location;
    DrawDebugBox(GetWorld(), Center, Hitbox.Extents, FQuat::Identity,
        FColor::Red, false, 0.1f, 0, 2.0f);
}

bool ULesFightHitDetection::IsAttackBlocked(ALesFightBaseFighter* Target) const
{
    if (!Target) return false;
    ULesFightCombatComponent* CombatComp = Target->FindComponentByClass<ULesFightCombatComponent>();
    return CombatComp && CombatComp->IsBlocking();
}
