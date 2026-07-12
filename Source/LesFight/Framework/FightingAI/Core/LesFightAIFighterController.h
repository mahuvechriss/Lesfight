#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIFighterController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAIStateChanged, EAIBehaviorMode, NewMode);

class ULesFightAIFighterManager;

UCLASS(Blueprintable)
class LESFIGHT_API ALesFightAIFighterController : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    void Initialize(ULesFightAIFighterManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    void PossessFighter(AActor* FighterActor);

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    AActor* GetControlledFighter() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    void SetEnabled(bool bInEnabled);

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    bool IsEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    void SetTarget(AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    AActor* GetTarget() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Fighter")
    void Tick(float DeltaTime);

    UPROPERTY(BlueprintAssignable, Category = "AI|Events")
    FOnAIStateChanged OnAIStateChanged;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Fighter")
    AActor* ControlledFighter;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Fighter")
    AActor* CurrentTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Fighter")
    bool bEnabled;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Fighter")
    EAIBehaviorMode CurrentMode;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Fighter")
    TArray<UObject*> Subsystems;

private:
    TWeakObjectPtr<ULesFightAIFighterManager> OwnerManager;
};
