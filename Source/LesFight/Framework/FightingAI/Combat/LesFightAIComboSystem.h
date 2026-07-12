#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIComboSystem.generated.h"

UCLASS(Blueprintable)
class ULesFightAIComboSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    void StartCombo(FName ComboName, const FAIStyleBehaviorProfile& Style);

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    void ExecuteNextAction(FAIDecisionContext& Context);

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    bool IsComboComplete() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    int32 GetRemainingComboLength() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    void CancelCombo();

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    void GenerateComboFromStyle(const FAIStyleBehaviorProfile& Style);

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    TArray<FName> GetComboList() const { return ComboList; }

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    bool HasComboOfLength(int32 MinLength, int32 MaxLength) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Combo")
    void Initialize(class ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo")
    TArray<EAIActionType> CurrentCombo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo")
    int32 CurrentIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo")
    TArray<FName> ComboList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
    TMap<FName, TArray<EAIActionType>> ComboDatabase;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
    int32 MaxComboLength;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;

    void BuildComboDatabase();
};
