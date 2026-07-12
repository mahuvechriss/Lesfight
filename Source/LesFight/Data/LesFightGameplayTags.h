#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LesFightGameplayTags.generated.h"

UCLASS(Config = Game)
class ULesFightGameplayTags : public UObject
{
    GENERATED_BODY()

public:
    static const ULesFightGameplayTags& Get();

    UFUNCTION(BlueprintPure, Category = "LesFight|Tags")
    static FGameplayTag GetTag(const FString& TagString);

    UFUNCTION(BlueprintPure, Category = "LesFight|Tags")
    static bool HasTag(const FGameplayTagContainer& Container, const FString& TagString);

    UFUNCTION(BlueprintPure, Category = "LesFight|Tags")
    static FGameplayTagContainer MakeContainerFromTag(const FString& TagString);

    UFUNCTION(BlueprintPure, Category = "LesFight|Tags")
    static FGameplayTagContainer CombineContainers(const FGameplayTagContainer& A, const FGameplayTagContainer& B);

    FGameplayTag State_Idle;
    FGameplayTag State_Walking;
    FGameplayTag State_Running;
    FGameplayTag State_Jumping;
    FGameplayTag State_Falling;
    FGameplayTag State_Attacking;
    FGameplayTag State_Blocking;
    FGameplayTag State_HitStun;
    FGameplayTag State_KnockedDown;
    FGameplayTag State_GettingUp;
    FGameplayTag State_Dead;

    FGameplayTag Combat_LightPunch;
    FGameplayTag Combat_HeavyPunch;
    FGameplayTag Combat_LightKick;
    FGameplayTag Combat_HeavyKick;
    FGameplayTag Combat_Special;
    FGameplayTag Combo_Active;

    FGameplayTag Input_ButtonLight;
    FGameplayTag Input_ButtonMedium;
    FGameplayTag Input_ButtonHeavy;
    FGameplayTag Input_ButtonSpecial;
    FGameplayTag Input_ButtonBlock;

    FGameplayTag Damage_Physical;
    FGameplayTag Damage_Special;

    FGameplayTag Modifier_Armored;
    FGameplayTag Modifier_Unblockable;
    FGameplayTag Modifier_Invulnerable;

    FGameplayTag Effect_Stun;
    FGameplayTag Effect_Launch;
    FGameplayTag Effect_Knockdown;

    void InitializeTag(FGameplayTag& Tag, const FString& TagString);
};
