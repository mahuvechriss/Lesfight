#include "LesFightUIAnimationSystem.h"

void ULesFightUIAnimationSystem::Initialize()
{
    AnimationRegistry.Empty();

    FUIAnimationDef FadeIn;
    FadeIn.Duration = 0.3f;
    FadeIn.Opacity = 1.0f;
    RegisterAnimationDef(TEXT("FadeIn"), FadeIn);

    FUIAnimationDef FadeOut;
    FadeOut.Duration = 0.2f;
    FadeOut.Opacity = 0.0f;
    RegisterAnimationDef(TEXT("FadeOut"), FadeOut);

    FUIAnimationDef SlideIn;
    SlideIn.Duration = 0.3f;
    SlideIn.OffsetX = 100.0f;
    RegisterAnimationDef(TEXT("SlideIn"), SlideIn);

    FUIAnimationDef SlideOut;
    SlideOut.Duration = 0.2f;
    SlideOut.OffsetX = -100.0f;
    RegisterAnimationDef(TEXT("SlideOut"), SlideOut);

    FUIAnimationDef ScaleIn;
    ScaleIn.Duration = 0.3f;
    ScaleIn.Scale = 1.0f;
    RegisterAnimationDef(TEXT("ScaleIn"), ScaleIn);

    FUIAnimationDef Pulse;
    Pulse.Duration = 0.5f;
    Pulse.bLoop = true;
    RegisterAnimationDef(TEXT("Pulse"), Pulse);

    FUIAnimationDef Shake;
    Shake.Duration = 0.2f;
    RegisterAnimationDef(TEXT("Shake"), Shake);
}

void ULesFightUIAnimationSystem::Shutdown()
{
    ActiveWidgetAnimations.Empty();
}

void ULesFightUIAnimationSystem::Tick(float DeltaTime)
{
    if (!bAnimationsEnabled)
    {
        return;
    }

    TArray<UUserWidget*> CompletedWidgets;

    for (auto& Pair : ActiveWidgetAnimations)
    {
        UUserWidget* Widget = Pair.Key;
        TArray<FActiveAnimation>& Animations = Pair.Value;

        for (int32 i = Animations.Num() - 1; i >= 0; --i)
        {
            FActiveAnimation& Anim = Animations[i];
            if (Anim.bPaused)
            {
                continue;
            }

            Anim.ElapsedTime += DeltaTime * GlobalSpeed;

            if (Anim.ElapsedTime >= Anim.Def.Duration)
            {
                if (Anim.Def.bLoop)
                {
                    Anim.ElapsedTime = 0.0f;
                }
                else
                {
                    Animations.RemoveAt(i);
                }
            }
        }

        if (Animations.Num() == 0)
        {
            CompletedWidgets.Add(Widget);
        }
    }

    for (UUserWidget* Widget : CompletedWidgets)
    {
        ActiveWidgetAnimations.Remove(Widget);
    }
}

void ULesFightUIAnimationSystem::PlayAnimationOnWidget(UUserWidget* Widget, FName AnimationName)
{
    if (!Widget || !bAnimationsEnabled)
    {
        return;
    }

    const FUIAnimationDef* Def = AnimationRegistry.Find(AnimationName);
    if (!Def)
    {
        return;
    }

    FActiveAnimation NewAnim;
    NewAnim.AnimationName = AnimationName;
    NewAnim.Def = *Def;
    NewAnim.ElapsedTime = 0.0f;
    NewAnim.bPaused = false;

    TArray<FActiveAnimation>& Animations = ActiveWidgetAnimations.FindOrAdd(Widget);
    Animations.Add(NewAnim);
}

void ULesFightUIAnimationSystem::StopAnimationOnWidget(UUserWidget* Widget, FName AnimationName)
{
    if (!Widget)
    {
        return;
    }

    TArray<FActiveAnimation>* Animations = ActiveWidgetAnimations.Find(Widget);
    if (!Animations)
    {
        return;
    }

    for (int32 i = Animations->Num() - 1; i >= 0; --i)
    {
        if ((*Animations)[i].AnimationName == AnimationName)
        {
            Animations->RemoveAt(i);
        }
    }

    if (Animations->Num() == 0)
    {
        ActiveWidgetAnimations.Remove(Widget);
    }
}

void ULesFightUIAnimationSystem::StopAllAnimationsOnWidget(UUserWidget* Widget)
{
    if (!Widget)
    {
        return;
    }
    ActiveWidgetAnimations.Remove(Widget);
}

bool ULesFightUIAnimationSystem::IsAnimating(UUserWidget* Widget) const
{
    if (!Widget)
    {
        return false;
    }
    return ActiveWidgetAnimations.Contains(Widget);
}

void ULesFightUIAnimationSystem::RegisterAnimationDef(FName Name, FUIAnimationDef Def)
{
    AnimationRegistry.Add(Name, Def);
}

TArray<FName> ULesFightUIAnimationSystem::GetRegisteredAnimations() const
{
    TArray<FName> Names;
    AnimationRegistry.GetKeys(Names);
    return Names;
}

void ULesFightUIAnimationSystem::SetGlobalSpeed(float Speed)
{
    GlobalSpeed = FMath::Max(0.0f, Speed);
}

void ULesFightUIAnimationSystem::SetAnimationsEnabled(bool bEnabled)
{
    bAnimationsEnabled = bEnabled;
    if (!bAnimationsEnabled)
    {
        ActiveWidgetAnimations.Empty();
    }
}
