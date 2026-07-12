#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIBlackboard.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIBlackboard : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    void SetValue(FName Key, float Value);

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    void SetVector(FName Key, FVector Value);

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    void SetObject(FName Key, UObject* Value);

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    float GetValue(FName Key) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    FVector GetVector(FName Key) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    UObject* GetObject(FName Key) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    bool HasKey(FName Key) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    void ClearKey(FName Key);

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    void ClearAll();

    UFUNCTION(BlueprintCallable, Category = "AI|Blackboard")
    TArray<FName> GetAllKeys() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
    TMap<FName, float> FloatValues;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
    TMap<FName, FVector> VectorValues;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
    TMap<FName, TWeakObjectPtr<UObject>> ObjectValues;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
