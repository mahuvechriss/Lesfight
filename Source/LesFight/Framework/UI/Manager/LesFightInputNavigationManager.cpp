#include "LesFightInputNavigationManager.h"

void ULesFightInputNavigationManager::Initialize()
{
	KeyBindings.Empty();
	DeviceBindings.Empty();
	bInputAllowed = true;
	ActiveDevice = EInputDeviceType::Keyboard;

	auto AddBinding = [&](EInputDeviceType Device, FName ActionName, FKey Key, FText DisplayName)
	{
		FUINavigationAction Action;
		Action.DeviceType = Device;
		Action.ActionName = ActionName;
		Action.Key = Key;
		Action.DisplayName = DisplayName;

		KeyBindings.Add(Key, Action);
		DeviceBindings.FindOrAdd(Device).Add(Action);
	};

	AddBinding(EInputDeviceType::Keyboard, FName("NavigateUp"), EKeys::W, FText::FromString("Navigate Up"));
	AddBinding(EInputDeviceType::Keyboard, FName("NavigateDown"), EKeys::S, FText::FromString("Navigate Down"));
	AddBinding(EInputDeviceType::Keyboard, FName("NavigateLeft"), EKeys::A, FText::FromString("Navigate Left"));
	AddBinding(EInputDeviceType::Keyboard, FName("NavigateRight"), EKeys::D, FText::FromString("Navigate Right"));
	AddBinding(EInputDeviceType::Keyboard, FName("Confirm"), EKeys::Enter, FText::FromString("Confirm"));
	AddBinding(EInputDeviceType::Keyboard, FName("Back"), EKeys::Escape, FText::FromString("Back"));
	AddBinding(EInputDeviceType::Keyboard, FName("Next"), EKeys::Tab, FText::FromString("Next"));
	AddBinding(EInputDeviceType::Keyboard, FName("Previous"), EKeys::Tab, FText::FromString("Previous"));

	AddBinding(EInputDeviceType::Gamepad, FName("NavigateUp"), EKeys::Gamepad_DPad_Up, FText::FromString("Navigate Up"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateDown"), EKeys::Gamepad_DPad_Down, FText::FromString("Navigate Down"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateLeft"), EKeys::Gamepad_DPad_Left, FText::FromString("Navigate Left"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateRight"), EKeys::Gamepad_DPad_Right, FText::FromString("Navigate Right"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateUp"), EKeys::Gamepad_LeftStick_Up, FText::FromString("Navigate Up"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateDown"), EKeys::Gamepad_LeftStick_Down, FText::FromString("Navigate Down"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateLeft"), EKeys::Gamepad_LeftStick_Left, FText::FromString("Navigate Left"));
	AddBinding(EInputDeviceType::Gamepad, FName("NavigateRight"), EKeys::Gamepad_LeftStick_Right, FText::FromString("Navigate Right"));
	AddBinding(EInputDeviceType::Gamepad, FName("Confirm"), EKeys::Gamepad_FaceButton_Bottom, FText::FromString("Confirm"));
	AddBinding(EInputDeviceType::Gamepad, FName("Back"), EKeys::Gamepad_FaceButton_Right, FText::FromString("Back"));
	AddBinding(EInputDeviceType::Gamepad, FName("Menu"), EKeys::Gamepad_Special_Left, FText::FromString("Menu"));
	AddBinding(EInputDeviceType::Gamepad, FName("Pause"), EKeys::Gamepad_Special_Right, FText::FromString("Pause"));
}

void ULesFightInputNavigationManager::Shutdown()
{
	KeyBindings.Empty();
	DeviceBindings.Empty();
}

void ULesFightInputNavigationManager::BindAction(FName ActionName, FKey Key, EInputDeviceType DeviceType)
{
	FUINavigationAction Action;
	Action.DeviceType = DeviceType;
	Action.ActionName = ActionName;
	Action.Key = Key;
	Action.DisplayName = FText::FromName(ActionName);

	KeyBindings.Add(Key, Action);
	DeviceBindings.FindOrAdd(DeviceType).Add(Action);
}

void ULesFightInputNavigationManager::UnbindAction(FName ActionName)
{
	TArray<FKey> KeysToRemove;
	for (const auto& Pair : KeyBindings)
	{
		if (Pair.Value.ActionName == ActionName)
		{
			KeysToRemove.Add(Pair.Key);
		}
	}

	for (const FKey& Key : KeysToRemove)
	{
		KeyBindings.Remove(Key);
	}

	for (auto& DeviceEntry : DeviceBindings)
	{
		DeviceEntry.Value.RemoveAll([&](const FUINavigationAction& Action)
		{
			return Action.ActionName == ActionName;
		});
	}
}

void ULesFightInputNavigationManager::ProcessInput(FKey Key, EInputEvent InputEvent)
{
	if (!bInputAllowed)
	{
		return;
	}

	if (InputEvent != IE_Pressed && InputEvent != IE_Released)
	{
		return;
	}

	const FUINavigationAction* Action = KeyBindings.Find(Key);
	if (Action)
	{
		OnInputAction.Broadcast(Action->ActionName);
	}
}

bool ULesFightInputNavigationManager::SupportsAction(FName ActionName) const
{
	for (const auto& Pair : KeyBindings)
	{
		if (Pair.Value.ActionName == ActionName)
		{
			return true;
		}
	}
	return false;
}

TArray<FUINavigationAction> ULesFightInputNavigationManager::GetBoundActions() const
{
	const TArray<FUINavigationAction>* Actions = DeviceBindings.Find(ActiveDevice);
	if (Actions)
	{
		return *Actions;
	}
	return {};
}
