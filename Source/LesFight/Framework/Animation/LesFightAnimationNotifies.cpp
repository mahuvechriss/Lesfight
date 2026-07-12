#include "LesFightAnimationNotifies.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

void ULesFightAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
    ULesFightCharacterAnimationComponent* AnimComp =
        Owner ? Owner->FindComponentByClass<ULesFightCharacterAnimationComponent>() : nullptr;
    if (AnimComp)
    {
        AnimComp->OnAnimationEvent.Broadcast(FName(TEXT("Footstep")), 0.0f);
    }
}

void ULesFightAnimNotify_Hit::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
    ULesFightCharacterAnimationComponent* AnimComp =
        Owner ? Owner->FindComponentByClass<ULesFightCharacterAnimationComponent>() : nullptr;
    if (AnimComp)
    {
        AnimComp->OnAnimationEvent.Broadcast(FName(TEXT("HitImpact")), 0.0f);
    }
}

void ULesFightAnimNotify_Sound::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if (!Sound || !MeshComp) return;

    if (AttachSocketName != NAME_None)
    {
        UGameplayStatics::PlaySoundAtLocation(MeshComp->GetOwner(), Sound,
            MeshComp->GetSocketLocation(AttachSocketName), VolumeMultiplier, PitchMultiplier);
    }
    else
    {
        UGameplayStatics::PlaySoundAtLocation(MeshComp->GetOwner(), Sound,
            MeshComp->GetComponentLocation(), VolumeMultiplier, PitchMultiplier);
    }
}

void ULesFightAnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if (!ShakeClass || !MeshComp) return;
    APlayerController* PC = Cast<APlayerController>(
        MeshComp->GetOwner()->GetInstigatorController());
    if (PC) PC->ClientStartCameraShake(ShakeClass, Scale);
}

void ULesFightAnimNotify_VFX::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if (!MeshComp) return;

    FVector SpawnLoc = MeshComp->GetComponentLocation();
    FRotator SpawnRot = MeshComp->GetComponentRotation();

    if (AttachSocketName != NAME_None)
    {
        SpawnLoc = MeshComp->GetSocketLocation(AttachSocketName);
        SpawnRot = MeshComp->GetSocketRotation(AttachSocketName);
    }

    SpawnLoc += SpawnRot.RotateVector(LocationOffset);
    SpawnRot = FRotator(SpawnRot.Pitch + RotationOffset.Pitch,
        SpawnRot.Yaw + RotationOffset.Yaw,
        SpawnRot.Roll + RotationOffset.Roll);

    if (NiagaraSystem)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetOwner()->GetWorld(),
            NiagaraSystem, SpawnLoc, SpawnRot, Scale);
    }
    else if (ParticleSystem)
    {
        UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetOwner()->GetWorld(),
            ParticleSystem, SpawnLoc, SpawnRot, Scale);
    }
}

void ULesFightAnimNotifyState_ComboWindow::NotifyBegin(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, float TotalDuration,
    const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
    AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
    ULesFightCharacterAnimationComponent* AnimComp =
        Owner ? Owner->FindComponentByClass<ULesFightCharacterAnimationComponent>() : nullptr;
    if (AnimComp)
    {
        AnimComp->OnAnimationEvent.Broadcast(FName(TEXT("ComboWindowOpen")), 0.0f);
    }
}

void ULesFightAnimNotifyState_ComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);
    AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
    ULesFightCharacterAnimationComponent* AnimComp =
        Owner ? Owner->FindComponentByClass<ULesFightCharacterAnimationComponent>() : nullptr;
    if (AnimComp)
    {
        AnimComp->OnAnimationEvent.Broadcast(FName(TEXT("ComboWindowClose")), 0.0f);
    }
}

void ULesFightAnimNotify_UltimateTrigger::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
    ULesFightCharacterAnimationComponent* AnimComp =
        Owner ? Owner->FindComponentByClass<ULesFightCharacterAnimationComponent>() : nullptr;
    if (AnimComp)
    {
        AnimComp->OnAnimationEvent.Broadcast(FName(TEXT("UltimateTrigger")), 0.0f);
    }
}

void ULesFightAnimNotify_RootMotion::Notify(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
}

void ULesFightAnimNotifyState_MotionWarp::NotifyBegin(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, float TotalDuration,
    const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void ULesFightAnimNotifyState_MotionWarp::NotifyTick(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, float FrameDeltaTime,
    const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void ULesFightAnimNotifyState_MotionWarp::NotifyEnd(USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);
}
