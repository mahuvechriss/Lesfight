#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LesFightBasePawn.generated.h"

UCLASS()
class ALesFightBasePawn : public APawn
{
    GENERATED_BODY()

public:
    ALesFightBasePawn();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
        class AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category = "LesFight|Pawn")
    bool IsPossessed() const { return GetController() != nullptr; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Pawn")
    float MaxHealth;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Pawn")
    float Health;

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
