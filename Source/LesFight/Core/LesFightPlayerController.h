#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LesFightPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ULesFightHUD;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuToggleDelegate);

UCLASS()
class ALesFightPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ALesFightPlayerController();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void SetupInputComponent() override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnRep_PlayerState() override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|UI")
    void ShowHUD();

    UFUNCTION(BlueprintCallable, Category = "LesFight|UI")
    void HideHUD();

    UFUNCTION(BlueprintCallable, Category = "LesFight|UI")
    void ToggleMenu();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void SetCameraZoom(float ZoomValue);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void SetInputEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    class ULesFightInputManager* GetInputManager() const { return InputManager; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TObjectPtr<UInputMappingContext> DefaultInputMapping;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TObjectPtr<UInputAction> MenuAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TObjectPtr<UInputAction> PauseAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TSubclassOf<ULesFightHUD> HUDClass;

    UPROPERTY()
    TObjectPtr<ULesFightHUD> CurrentHUD;

    UPROPERTY()
    TObjectPtr<class ULesFightInputManager> InputManager;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnMenuToggleDelegate OnMenuToggled;

private:
    bool bIsMenuOpen;
    bool bIsInputEnabled;

    void HandleMoveInput(const FInputActionValue& Value);
    void HandleLookInput(const FInputActionValue& Value);
    void HandleMenuToggle();
    void HandlePauseGame();
};
