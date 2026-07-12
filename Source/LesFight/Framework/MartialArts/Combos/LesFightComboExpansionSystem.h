#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightComboExpansionSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboBranch, int32, BranchIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboExpansion, EComboExpansionType, ExpansionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateChainReady);

UCLASS(Blueprintable)
class ULesFightComboExpansionSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightComboExpansionSystem();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    bool StartComboExpansion(EComboExpansionType ExpansionType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    bool ChainNextAttack(int32 BranchIndex = 0);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void CancelCombo();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void RegisterHit();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void SetLaunched(bool bLaunched);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void SetNearWall(bool bNearWall);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void SetOnGround(bool bOnGround);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void SetExpansionData(const TMap<EComboExpansionType, FComboExpansionData>& Data);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void SetAvailableExpansions(const TArray<EComboExpansionType>& Expansions);

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    bool IsInCombo() const { return bInCombo; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    int32 GetCurrentChainLength() const { return CurrentChainLength; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    int32 GetMaxChainLength() const { return MaxChainLength; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    EComboExpansionType GetCurrentExpansion() const { return CurrentExpansion; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    float GetChainTimeRemaining() const { return ChainTimer; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    bool CanEndWithUltimate() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Combos")
    TArray<EComboExpansionType> GetAvailableExpansions() const { return AvailableExpansions; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Combos")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboBranch OnComboBranch;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboExpansion OnComboExpansion;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnUltimateChainReady OnUltimateChainReady;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bInCombo;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentChainLength;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 MaxChainLength;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float ChainTimer;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EComboExpansionType CurrentExpansion;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<EComboExpansionType, FComboExpansionData> ExpansionDefinitions;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TArray<EComboExpansionType> AvailableExpansions;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    bool bTargetLaunched;
    bool bNearWall;
    bool bTargetOnGround;
    int32 TotalHitsInCombo;
    int32 BranchIndex;
    TArray<int32> BranchHistory;

    bool CanChain(EComboExpansionType ExpansionType) const;
    void OnComboTimeout();
    float GetChainWindow() const;
};
