#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightComboData.h"
#include "LesFightSpecialMoveComponent.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class ESpecialMoveState : uint8
{
    Ready,
    Startup,
    Active,
    Recovery,
    Cooldown,
};

UENUM(BlueprintType)
enum class ESpecialMoveInput : uint8
{
    Forward,
    Backward,
    Down,
    Up,
    DownForward,
    DownBackward,
    UpForward,
    UpBackward,
    QuarterCircleForward,
    QuarterCircleBackward,
    HalfCircleForward,
    HalfCircleBackward,
    DragonPunch,
    ChargeBack,
    ChargeDown,
    DoubleTap,
    MAX UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpecialMoveExecuted, FName, MoveID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpecialMoveFailed, FName, MoveID);

USTRUCT(BlueprintType)
struct FSpecialMoveInputSequence
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ESpecialMoveInput> InputSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InputWindow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresButtonPress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAttackType RequiredButton;

    FSpecialMoveInputSequence()
        : InputWindow(0.3f)
        , bRequiresButtonPress(true)
        , RequiredButton(EAttackType::Special)
    {}
};

UCLASS(Blueprintable)
class ULesFightSpecialMoveComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightSpecialMoveComponent();

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    void RegisterSpecialMove(const FSpecialMoveDefinition& MoveDef);

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    bool TryExecuteSpecialMove(FName MoveID);

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    bool DetectSpecialMoveInput(TArray<ESpecialMoveInput> RecentInputs, EAttackType ButtonPressed);

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    bool HasMeterForMove(FName MoveID) const;

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    void ConsumeMeterForMove(FName MoveID);

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    void StartSpecialMove(FName MoveID);

    UFUNCTION(BlueprintCallable, Category = "SpecialMove")
    void EndSpecialMove();

    UFUNCTION(BlueprintPure, Category = "SpecialMove")
    ESpecialMoveState GetSpecialMoveState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "SpecialMove")
    bool IsExecutingSpecial() const { return CurrentState == ESpecialMoveState::Active; }

    UFUNCTION(BlueprintPure, Category = "SpecialMove")
    bool HasSpecialMove(FName MoveID) const { return RegisteredMoves.Contains(MoveID); }

    UFUNCTION(BlueprintPure, Category = "SpecialMove")
    TArray<FName> GetAvailableMoves() const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSpecialMoveExecuted OnSpecialMoveExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSpecialMoveFailed OnSpecialMoveFailed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpecialMove")
    float MeterPoolMax;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpecialMove")
    float MeterRegenRate;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    TMap<FName, FSpecialMoveDefinition> RegisteredMoves;
    ESpecialMoveState CurrentState;
    float CurrentMeter;
    TArray<ESpecialMoveInput> RecentInputHistory;

    bool MatchInputSequence(const TArray<ESpecialMoveInput>& Sequence);
};
