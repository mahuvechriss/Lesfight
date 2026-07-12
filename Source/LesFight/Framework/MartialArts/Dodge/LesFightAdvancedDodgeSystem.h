#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightAdvancedDodgeSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDodgeExecuted, EAdvancedDodgeType, DodgeType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerfectDodge, EAdvancedDodgeType, DodgeType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDodgeFailed, EAdvancedDodgeType, DodgeType);

UCLASS(Blueprintable)
class ULesFightAdvancedDodgeSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAdvancedDodgeSystem();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Dodge")
    bool ExecuteDodge(EAdvancedDodgeType DodgeType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Dodge")
    bool CanDodge(EAdvancedDodgeType DodgeType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Dodge")
    void CancelDodge();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Dodge")
    void SetDodgeData(const TMap<EAdvancedDodgeType, FAdvancedDodgeData>& Data);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Dodge")
    void SetAvailableDodges(const TArray<EAdvancedDodgeType>& Dodges);

    UFUNCTION(BlueprintPure, Category = "MartialArts|Dodge")
    bool IsDodging() const { return bIsDodging; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Dodge")
    EAdvancedDodgeType GetCurrentDodge() const { return CurrentDodge; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Dodge")
    TArray<EAdvancedDodgeType> GetAvailableDodges() const { return AvailableDodges; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Dodge")
    float GetDodgeDistance(EAdvancedDodgeType DodgeType) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Dodge")
    float GetIFrameDuration(EAdvancedDodgeType DodgeType) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Dodge")
    float GetPerfectDodgeWindow(EAdvancedDodgeType DodgeType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Dodge")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDodgeExecuted OnDodgeExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPerfectDodge OnPerfectDodge;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDodgeFailed OnDodgeFailed;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsDodging;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EAdvancedDodgeType CurrentDodge;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float IFrameTimer;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float DodgeTimer;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<EAdvancedDodgeType> AvailableDodges;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<EAdvancedDodgeType, FAdvancedDodgeData> DodgeDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float StaminaCostMultiplier;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    bool bPerfectDodgeWindow;
    float PerfectDodgeTimer;
    float DodgeCooldown;
    FVector DodgeDirection;

    void ProcessDodge(float DeltaTime);
    void OnDodgeComplete();
    void ApplyIFrames();
    void RemoveIFrames();
    bool IsPerfectDodge(EAdvancedDodgeType DodgeType) const;
};
