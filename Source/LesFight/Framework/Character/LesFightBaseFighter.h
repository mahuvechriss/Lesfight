#pragma once

#include "CoreMinimal.h"
#include "Framework/Player/LesFightPlayerCharacter.h"
#include "LesFightCharacterData.h"
#include "LesFightBaseFighter.generated.h"

class ULesFightHealthComponent;
class ULesFightStaminaComponent;
class ULesFightAnimationComponent;
class ULesFightAudioComponent;
class ULesFightStatisticsComponent;
class ULesFightAppearanceComponent;
class ULesFightInteractionComponent;
class ULesFightCharacterProgression;
class ULesFightFighterDataAsset;
class ULesFightCombatComponent;
class ULesFightCombatDataAsset;
class ULesFightCharacterAnimationComponent;
class ULesFightMartialArtsManager;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFighterInitialized, const FName&, CharacterID);

UCLASS()
class ALesFightBaseFighter : public ALesFightPlayerCharacter
{
    GENERATED_BODY()

public:
    ALesFightBaseFighter(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Landed(const FHitResult& Hit) override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
        class AController* EventInstigator, AActor* DamageCauser) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Fighter")
    void InitializeFighter(ULesFightFighterDataAsset* FighterData);

    UFUNCTION(BlueprintCallable, Category = "Fighter")
    void ApplyFighterData(const FCharacterTableRow& Data);

    UFUNCTION(BlueprintPure, Category = "Fighter")
    FName GetFighterID() const { return FighterID; }

    UFUNCTION(BlueprintPure, Category = "Fighter")
    FString GetFighterName() const { return FighterName; }

    UFUNCTION(BlueprintPure, Category = "Fighter")
    FString GetDisplayName() const { return DisplayName; }

    UFUNCTION(BlueprintPure, Category = "Fighter")
    FCharacterIdentity GetIdentity() const { return Identity; }

    UFUNCTION(BlueprintPure, Category = "Fighter")
    FCharacterPhysicalAttributes GetPhysicalAttributes() const { return PhysicalAttributes; }

    UFUNCTION(BlueprintPure, Category = "Fighter")
    bool IsFighterInitialized() const { return bFighterInitialized; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightHealthComponent* GetHealthComponent() const { return HealthComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightStaminaComponent* GetStaminaComponent() const { return StaminaComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightAnimationComponent* GetAnimationComponent() const { return AnimationComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightAudioComponent* GetAudioComponent() const { return AudioComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightStatisticsComponent* GetStatisticsComponent() const { return StatisticsComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightAppearanceComponent* GetAppearanceComponent() const { return AppearanceComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightCharacterProgression* GetProgression() const { return Progression; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightCombatComponent* GetCombatComponent() const { return CombatComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightCharacterAnimationComponent* GetCharacterAnimComponent() const { return CharacterAnimComponent; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Components")
    ULesFightMartialArtsManager* GetMartialArtsManager() const { return MartialArtsManager; }

    UFUNCTION(BlueprintCallable, Category = "Fighter|Lifecycle")
    void OnFighterDeath();

    UFUNCTION(BlueprintCallable, Category = "Fighter|Lifecycle")
    void OnFighterRevive();

    UFUNCTION(BlueprintCallable, Category = "Fighter|Lifecycle")
    void OnRoundStart();

    UFUNCTION(BlueprintCallable, Category = "Fighter|Lifecycle")
    void OnRoundEnd();

    UFUNCTION(BlueprintCallable, Category = "Fighter|Lifecycle")
    void OnMatchStart();

    UFUNCTION(BlueprintCallable, Category = "Fighter|Lifecycle")
    void OnMatchEnd();

    UFUNCTION(BlueprintCallable, Category = "Fighter|Visual")
    void SetFighterVisibility(bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "Fighter|Network")
    void SetPlayerIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Fighter|Network")
    void SetOwnerPlayerIndex(int32 Index);

    UFUNCTION(BlueprintPure, Category = "Fighter|Network")
    int32 GetPlayerIndex() const { return PlayerIndex; }

    UFUNCTION(BlueprintPure, Category = "Fighter|Network")
    int32 GetOwnerPlayerIndex() const { return OwnerPlayerIndex; }

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetPlayerIndex(int32 Index);

    UFUNCTION(Client, Reliable)
    void ClientOnDeath();

    UFUNCTION(Client, Reliable)
    void ClientOnRevive();

    UFUNCTION(Client, Reliable)
    void ClientOnRoundStart();

    UFUNCTION(Client, Reliable)
    void ClientOnRoundEnd();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightHealthComponent> HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightStaminaComponent> StaminaComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightAnimationComponent> AnimationComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightAudioComponent> AudioComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightStatisticsComponent> StatisticsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightAppearanceComponent> AppearanceComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightInteractionComponent> InteractionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightCharacterProgression> Progression;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightCombatComponent> CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightCharacterAnimationComponent> CharacterAnimComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fighter|Components")
    TObjectPtr<ULesFightMartialArtsManager> MartialArtsManager;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fighter|Data")
    TObjectPtr<ULesFightAnimationDataAsset> DefaultAnimationData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fighter|Data")
    TObjectPtr<ULesFightCombatDataAsset> DefaultCombatData;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FName FighterID;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FString FighterName;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FString DisplayName;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FCharacterIdentity Identity;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FCharacterPhysicalAttributes PhysicalAttributes;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FCharacterMovementAttributes MovementAttributes;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FCharacterCombatAttributes CombatAttributes;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter|Identity")
    FCharacterResourceAttributes ResourceAttributes;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterInitialized OnFighterInitialized;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fighter|Data")
    TObjectPtr<ULesFightFighterDataAsset> DefaultFighterData;

    UPROPERTY(BlueprintReadOnly, Category = "Fighter")
    bool bFighterInitialized;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Fighter|Network")
    int32 PlayerIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Fighter|Network")
    int32 OwnerPlayerIndex;

private:
    void CreateComponents();
    void BindComponentEvents();
    void ApplyMovementStatsFromData();

    UFUNCTION()
    void OnHealthComponentDeath();
};
