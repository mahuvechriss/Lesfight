#include "LesFightInputManager.h"
#include "LesFight.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

ULesFightInputManager::ULesFightInputManager()
    : bKeyboardConnected(true)
    , bInputEnabled(true)
{
}

void ULesFightInputManager::InitializeInputSystem(APlayerController* InPlayerController)
{
    PlayerController = InPlayerController;

    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
        if (Subsystem)
        {
            for (const FInputMappingConfig& Config : InputMappings)
            {
                if (Config.MappingContext && Config.bIsActive)
                {
                    Subsystem->AddMappingContext(Config.MappingContext, Config.Priority);
                }
            }
        }
    }

    UE_LOG(LogLesFight, Log, TEXT("Input system initialized"));
}

void ULesFightInputManager::AddInputMapping(UInputMappingContext* MappingContext, int32 Priority)
{
    if (!MappingContext) return;

    FInputMappingConfig NewConfig;
    NewConfig.MappingContext = MappingContext;
    NewConfig.Priority = Priority;
    NewConfig.bIsActive = true;
    InputMappings.Add(NewConfig);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
    if (Subsystem)
    {
        Subsystem->AddMappingContext(MappingContext, Priority);
    }
}

void ULesFightInputManager::RemoveInputMapping(UInputMappingContext* MappingContext)
{
    if (!MappingContext) return;

    InputMappings.RemoveAll([MappingContext](const FInputMappingConfig& Config)
    {
        return Config.MappingContext == MappingContext;
    });

    UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
    if (Subsystem)
    {
        Subsystem->RemoveMappingContext(MappingContext);
    }
}

void ULesFightInputManager::EnableInputMapping(const FString& MappingName)
{
    for (FInputMappingConfig& Config : InputMappings)
    {
        if (Config.MappingContext && Config.MappingContext->GetName() == MappingName)
        {
            Config.bIsActive = true;
            UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
            if (Subsystem)
            {
                Subsystem->AddMappingContext(Config.MappingContext, Config.Priority);
            }
            break;
        }
    }
}

void ULesFightInputManager::DisableInputMapping(const FString& MappingName)
{
    for (FInputMappingConfig& Config : InputMappings)
    {
        if (Config.MappingContext && Config.MappingContext->GetName() == MappingName)
        {
            Config.bIsActive = false;
            UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
            if (Subsystem)
            {
                Subsystem->RemoveMappingContext(Config.MappingContext);
            }
            break;
        }
    }
}

void ULesFightInputManager::ClearAllMappings()
{
    UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
    if (Subsystem)
    {
        for (const FInputMappingConfig& Config : InputMappings)
        {
            if (Config.MappingContext)
            {
                Subsystem->RemoveMappingContext(Config.MappingContext);
            }
        }
    }
    InputMappings.Empty();
}

int32 ULesFightInputManager::GetConnectedDeviceCount() const
{
    return 1;
}

bool ULesFightInputManager::IsGamepadConnected(int32 ControllerId) const
{
    return false;
}

void ULesFightInputManager::SetInputEnabled(bool bEnabled)
{
    bInputEnabled = bEnabled;
}

void ULesFightInputManager::VibrateController(int32 ControllerId, float Intensity, float Duration)
{
}

void ULesFightInputManager::RebindAction(const FString& ActionName, const FKey& NewKey)
{
}

void ULesFightInputManager::ResetToDefaultBindings()
{
}

void ULesFightInputManager::SaveInputSettings()
{
}

void ULesFightInputManager::LoadInputSettings()
{
}

UEnhancedInputLocalPlayerSubsystem* ULesFightInputManager::GetEnhancedInputSubsystem() const
{
    if (!PlayerController) return nullptr;

    ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
    if (!LocalPlayer) return nullptr;

    return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
}
