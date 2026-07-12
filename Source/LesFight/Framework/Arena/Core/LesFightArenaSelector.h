#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaSelector.generated.h"

class ULesFightArenaWorldManager;
class ULesFightArenaDataSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArenaSelected, EArenaType, Arena);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaSelector : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void SelectArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    EArenaType GetSelectedArena() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    FArenaInfo GetSelectedArenaInfo() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void SetRandomSelection(bool bRandom);

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void SelectRandomArena();

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void SetFilterCategory(EArenaEnvironmentCategory Category);

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void ClearFilter();

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    TArray<FArenaInfo> GetFilteredArenas() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void PreviewArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Selection")
    void ConfirmSelection();

    UPROPERTY(BlueprintAssignable, Category = "Arena|Selection")
    FOnArenaSelected OnArenaSelected;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager, ULesFightArenaDataSystem* InDataSystem);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Selection")
    EArenaType SelectedArena;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Selection")
    EArenaType PreviewArena;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Selection")
    bool bRandomSelection;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Selection")
    EArenaEnvironmentCategory FilterCategory;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Selection")
    bool bFilterActive;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
    TWeakObjectPtr<ULesFightArenaDataSystem> DataSystem;
};
