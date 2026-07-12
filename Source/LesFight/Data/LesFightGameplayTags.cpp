#include "LesFightGameplayTags.h"
#include "LesFight.h"

const ULesFightGameplayTags& ULesFightGameplayTags::Get()
{
    static const ULesFightGameplayTags* Instance = nullptr;
    if (!Instance)
    {
        Instance = NewObject<ULesFightGameplayTags>(GetTransientPackage(), TEXT("GameplayTags"));
        Instance->AddToRoot();

        Instance->InitializeTag(Instance->State_Idle, TEXT("LesFight.State.Idle"));
        Instance->InitializeTag(Instance->State_Walking, TEXT("LesFight.State.Walking"));
        Instance->InitializeTag(Instance->State_Running, TEXT("LesFight.State.Running"));
        Instance->InitializeTag(Instance->State_Jumping, TEXT("LesFight.State.Jumping"));
        Instance->InitializeTag(Instance->State_Falling, TEXT("LesFight.State.Falling"));
        Instance->InitializeTag(Instance->State_Attacking, TEXT("LesFight.State.Attacking"));
        Instance->InitializeTag(Instance->State_Blocking, TEXT("LesFight.State.Blocking"));
        Instance->InitializeTag(Instance->State_HitStun, TEXT("LesFight.State.HitStun"));
        Instance->InitializeTag(Instance->State_KnockedDown, TEXT("LesFight.State.KnockedDown"));
        Instance->InitializeTag(Instance->State_GettingUp, TEXT("LesFight.State.GettingUp"));
        Instance->InitializeTag(Instance->State_Dead, TEXT("LesFight.State.Dead"));

        Instance->InitializeTag(Instance->Combat_LightPunch, TEXT("LesFight.Combat.LightPunch"));
        Instance->InitializeTag(Instance->Combat_HeavyPunch, TEXT("LesFight.Combat.HeavyPunch"));
        Instance->InitializeTag(Instance->Combat_LightKick, TEXT("LesFight.Combat.LightKick"));
        Instance->InitializeTag(Instance->Combat_HeavyKick, TEXT("LesFight.Combat.HeavyKick"));
        Instance->InitializeTag(Instance->Combat_Special, TEXT("LesFight.Combat.Special"));
        Instance->InitializeTag(Instance->Combo_Active, TEXT("LesFight.Combo.Active"));

        Instance->InitializeTag(Instance->Input_ButtonLight, TEXT("LesFight.Input.ButtonLight"));
        Instance->InitializeTag(Instance->Input_ButtonMedium, TEXT("LesFight.Input.ButtonMedium"));
        Instance->InitializeTag(Instance->Input_ButtonHeavy, TEXT("LesFight.Input.ButtonHeavy"));
        Instance->InitializeTag(Instance->Input_ButtonSpecial, TEXT("LesFight.Input.ButtonSpecial"));
        Instance->InitializeTag(Instance->Input_ButtonBlock, TEXT("LesFight.Input.ButtonBlock"));

        Instance->InitializeTag(Instance->Damage_Physical, TEXT("LesFight.Damage.Physical"));
        Instance->InitializeTag(Instance->Damage_Special, TEXT("LesFight.Damage.Special"));

        Instance->InitializeTag(Instance->Modifier_Armored, TEXT("LesFight.Modifier.Armored"));
        Instance->InitializeTag(Instance->Modifier_Unblockable, TEXT("LesFight.Modifier.Unblockable"));
        Instance->InitializeTag(Instance->Modifier_Invulnerable, TEXT("LesFight.Modifier.Invulnerable"));

        Instance->InitializeTag(Instance->Effect_Stun, TEXT("LesFight.Effect.Stun"));
        Instance->InitializeTag(Instance->Effect_Launch, TEXT("LesFight.Effect.Launch"));
        Instance->InitializeTag(Instance->Effect_Knockdown, TEXT("LesFight.Effect.Knockdown"));
    }
    return *Instance;
}

FGameplayTag ULesFightGameplayTags::GetTag(const FString& TagString)
{
    return FGameplayTag::RequestGameplayTag(FName(*TagString));
}

bool ULesFightGameplayTags::HasTag(const FGameplayTagContainer& Container, const FString& TagString)
{
    return Container.HasTag(GetTag(TagString));
}

FGameplayTagContainer ULesFightGameplayTags::MakeContainerFromTag(const FString& TagString)
{
    FGameplayTagContainer Container;
    Container.AddTag(GetTag(TagString));
    return Container;
}

FGameplayTagContainer ULesFightGameplayTags::CombineContainers(
    const FGameplayTagContainer& A, const FGameplayTagContainer& B)
{
    FGameplayTagContainer Result;
    Result = A;
    Result.AppendTags(B);
    return Result;
}

void ULesFightGameplayTags::InitializeTag(FGameplayTag& Tag, const FString& TagString)
{
    Tag = FGameplayTag::RequestGameplayTag(FName(*TagString));
    if (!Tag.IsValid())
    {
        UE_LOG(LogLesFight, Warning, TEXT("Failed to initialize gameplay tag: %s"), *TagString);
    }
}
