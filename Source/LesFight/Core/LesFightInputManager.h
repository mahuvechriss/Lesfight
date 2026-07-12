#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputActionValue.h"
#include "LesFightInputManager.generated.h"

class UInputMappingContext;
class UInputAction;
class APlayerController;

UENUM(BlueprintType)
enum class EInputBindingPriority : uint8
{
    UI,
    Menu,
    Gameplay,
    Combat,
    Debug
};

USTRUCT(BlueprintType)
struct FInputMappingConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputMappingContext> MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Priority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsActive;

    FInputMappingConfig()
        : MappingContext(nullptr)
        , Priority(0)
        , bIsActive(true)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChanged, int32, DeviceType);

UCLASS(Blueprintable)
class ULesFightInputManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightInputManager();

    void InitializeInputSystem(APlayerController* InPlayerController);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void AddInputMapping(UInputMappingContext* MappingContext, int32 Priority = 0);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void RemoveInputMapping(UInputMappingContext* MappingContext);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void EnableInputMapping(const FString& MappingName);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void DisableInputMapping(const FString& MappingName);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void ClearAllMappings();

    UFUNCTION(BlueprintPure, Category = "LesFight|Input")
    int32 GetConnectedDeviceCount() const;

    UFUNCTION(BlueprintPure, Category = "LesFight|Input")
    bool IsKeyboardConnected() const { return bKeyboardConnected; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Input")
    bool IsGamepadConnected(int32 ControllerId) const;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void SetInputEnabled(bool bEnabled);

    UFUNCTION(BlueprintPure, Category = "LesFight|Input")
    bool IsInputEnabled() const { return bInputEnabled; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void VibrateController(int32 ControllerId, float Intensity, float Duration);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void RebindAction(const FString& ActionName, const FKey& NewKey);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void ResetToDefaultBindings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void SaveInputSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Input")
    void LoadInputSettings();

protected:
    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnInputDeviceChanged OnInputDeviceChanged;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TArray<FInputMappingConfig> InputMappings;

    UPROPERTY()
    TObjectPtr<APlayerController> PlayerController;

private:
    bool bKeyboardConnected;
    bool bInputEnabled;

    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
};
