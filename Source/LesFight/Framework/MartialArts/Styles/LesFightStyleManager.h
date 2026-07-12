#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightStyleManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStyleChanged, EFightingStyle, NewStyle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStyleUnlocked, EFightingStyle, UnlockedStyle);

UCLASS(Blueprintable)
class ULesFightStyleManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightStyleManager();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    bool EquipStyle(EFightingStyle StyleID);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    bool UnlockStyle(EFightingStyle StyleID);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    class ULesFightFightingStyle* GetCurrentStyle() const { return CurrentStyle; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    EFightingStyle GetCurrentStyleID() const { return CurrentStyleID; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    class ULesFightFightingStyle* GetStyle(EFightingStyle StyleID) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Styles")
    TArray<EFightingStyle> GetUnlockedStyles() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Styles")
    TArray<EFightingStyle> GetAllAvailableStyles() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    FStyleAttributes GetCurrentAttributes() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    void SetStyleDataAsset(class ULesFightMartialArtsDataAsset* DataAsset);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Styles")
    void ResetToDefault();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStyleChanged OnStyleChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStyleUnlocked OnStyleUnlocked;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFightingStyle CurrentStyleID;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TObjectPtr<class ULesFightFightingStyle> CurrentStyle;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<EFightingStyle, TObjectPtr<class ULesFightFightingStyle>> StyleRegistry;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TSet<EFightingStyle> UnlockedStylesSet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TObjectPtr<class ULesFightMartialArtsDataAsset> StyleData;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;

    class ULesFightFightingStyle* CreateStyleInstance(EFightingStyle StyleID);
    void RegisterAllStyles();
    void ApplyStyleAttributes(ULesFightFightingStyle* Style);
};
