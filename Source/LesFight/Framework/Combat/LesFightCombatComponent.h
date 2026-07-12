#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightAttackData.h"
#include "LesFightComboData.h"
#include "LesFightCombatComponent.generated.h"

class ALesFightBaseFighter;
class ULesFightComboManager;
class ULesFightDamageManager;
class ULesFightHitDetection;
class ULesFightInputBuffer;
class ULesFightCombatDataAsset;
class ULesFightBlockingComponent;
class ULesFightDodgeComponent;
class ULesFightThrowComponent;
class ULesFightSpecialMoveComponent;
class ULesFightUltimateMoveComponent;
class ULesFightCombatEffects;
class ULesFightReactionSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttackStarted, FName, AttackID, EAttackType, AttackType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttackHit, FName, AttackID, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackMissed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackRecovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboUpdated, int32, ComboCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboBroken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFighterHit, AActor*, Attacker, const FDamageResult&, DamageResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStartEvent, int32, RoundNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundEndEvent, bool, bWon);

UENUM(BlueprintType)
enum class EAttackPhase : uint8
{
    None,
    Startup,
    Active,
    Recovery,
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightCombatComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Initialize(ALesFightBaseFighter* InOwner, ULesFightCombatDataAsset* CombatData);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void InitializeDefault(ALesFightBaseFighter* InOwner);

    void ExecuteAttackByID(FName AttackID);

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformAttack(FName AttackID);

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformLightPunch();

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformHeavyPunch();

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformLightKick();

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformHeavyKick();

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformJumpAttack();

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformCrouchAttack();

    UFUNCTION(BlueprintCallable, Category = "Attacks")
    void PerformDashAttack();

    UFUNCTION(BlueprintCallable, Category = "Defense")
    void PerformBlock(EBlockType BlockType);

    UFUNCTION(BlueprintCallable, Category = "Defense")
    void ReleaseBlock();

    UFUNCTION(BlueprintCallable, Category = "Defense")
    void PerformDodge(EDodgeType DodgeType);

    UFUNCTION(BlueprintCallable, Category = "Defense")
    void PerformThrow();

    UFUNCTION(BlueprintCallable, Category = "Special")
    void PerformSpecialMove(int32 MoveIndex);

    UFUNCTION(BlueprintCallable, Category = "Special")
    void PerformUltimate();

    UFUNCTION(BlueprintCallable, Category = "Round")
    void OnRoundStart();

    UFUNCTION(BlueprintCallable, Category = "Round")
    void OnRoundEnd();

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool CanAttack() const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsAttacking() const { return bIsAttacking; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsBlocking() const { return BlockingComponent && BlockingComponent->IsBlocking(); }

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsDodging() const { return DodgeComponent && DodgeComponent->IsDodging(); }

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsInHitstun() const { return ReactionSystem && !ReactionSystem->CanAct(); }

    UFUNCTION(BlueprintPure, Category = "Combat")
    int32 GetComboCount() const { return ComboCount; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    EAttackType GetCurrentAttackType() const { return CurrentAttackType; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    FName GetCurrentAttackID() const { return CurrentAttackID; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    EAttackPhase GetAttackPhase() const { return CurrentPhase; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightInputBuffer* GetInputBuffer() const { return InputBuffer; }

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPerformAttack(FName AttackID);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPerformBlock(EBlockType BlockType);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerReleaseBlock();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPerformDodge(EDodgeType DodgeType);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPerformThrow();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPerformSpecialMove(int32 MoveIndex);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPerformUltimate();

    UFUNCTION(Client, Reliable)
    void ClientOnAttackHit(AActor* Target, const FDamageResult& DamageResult);

    UFUNCTION(Client, Reliable)
    void ClientOnAttackMissed();

    UFUNCTION(Client, Reliable)
    void ClientOnAttackStarted(FName AttackID, EAttackType AttackType);

    UFUNCTION(Client, Reliable)
    void ClientOnComboUpdated(int32 ComboCount);

    UFUNCTION(Client, Reliable)
    void ClientOnComboBroken();

    UFUNCTION(Client, Reliable)
    void ClientOnAttackRecovered();

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightHitDetection* GetHitDetection() const { return HitDetection; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightComboManager* GetComboManager() const { return ComboManager; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightDamageManager* GetDamageManager() const { return DamageManager; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightBlockingComponent* GetBlockingComponent() const { return BlockingComponent; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightDodgeComponent* GetDodgeComponent() const { return DodgeComponent; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightSpecialMoveComponent* GetSpecialMoveComponent() const { return SpecialMoveComponent; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightUltimateMoveComponent* GetUltimateMoveComponent() const { return UltimateMoveComponent; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightCombatEffects* GetCombatEffects() const { return CombatEffects; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightReactionSystem* GetReactionSystem() const { return ReactionSystem; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightComboManager> ComboManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightDamageManager> DamageManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightHitDetection> HitDetection;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightInputBuffer> InputBuffer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightBlockingComponent> BlockingComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightDodgeComponent> DodgeComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightThrowComponent> ThrowComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightSpecialMoveComponent> SpecialMoveComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightUltimateMoveComponent> UltimateMoveComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightCombatEffects> CombatEffects;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<ULesFightReactionSystem> ReactionSystem;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttackStarted OnAttackStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttackHit OnAttackHit;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttackMissed OnAttackMissed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttackRecovered OnAttackRecovered;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboUpdated OnComboUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboBroken OnComboBroken;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterHit OnFighterHit;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRoundStartEvent OnRoundStartEvent;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRoundEndEvent OnRoundEndEvent;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    TMap<FName, FAttackDefinition> AttackMap;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    TMap<FName, int32> CooldownMap;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    TObjectPtr<ALesFightBaseFighter> OwnerFighter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    TObjectPtr<ULesFightCombatDataAsset> CombatDataAsset;

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Network")
    TObjectPtr<ALesFightNetworkPlayerController> NetworkController;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    bool bIsAttacking;
    bool bCombatEnabled;
    EAttackType CurrentAttackType;
    FName CurrentAttackID;
    int32 ComboCount;
    float CurrentFrameTimer;
    int32 CurrentFrame;
    int32 TotalFrames;
    FAttackFrameData CurrentFrameData;
    EAttackPhase CurrentPhase;
    FAttackDefinition CurrentAttackDefinition;

    void CreateSubManagers(ALesFightBaseFighter* Owner);
    void ExecuteAttack(const FAttackDefinition& Attack);
    void UpdateAttackFrames(float DeltaTime);
    void OnAttackConnect(AActor* Target);
    void ProcessHit(AActor* Target);
    void EndAttack();
    void UpdateCooldowns(float DeltaTime);
    void BufferAndExecute();
    void SetupDefaultAttacks();
    bool IsOnCooldown(FName AttackID) const;
};
