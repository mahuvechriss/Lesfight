#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAccessorySystem.generated.h"

class ULesFightCharCreationManager;

UENUM(BlueprintType)
enum class EAccessorySlot : uint8
{
	Head		UMETA(DisplayName = "Head"),
	Ears		UMETA(DisplayName = "Ears"),
	Eyes		UMETA(DisplayName = "Eyes"),
	Face		UMETA(DisplayName = "Face"),
	Neck		UMETA(DisplayName = "Neck"),
	Shoulders	UMETA(DisplayName = "Shoulders"),
	Back		UMETA(DisplayName = "Back"),
	Chest		UMETA(DisplayName = "Chest"),
	Arms		UMETA(DisplayName = "Arms"),
	Hands		UMETA(DisplayName = "Hands"),
	Waist		UMETA(DisplayName = "Waist"),
	Legs		UMETA(DisplayName = "Legs"),
	Feet		UMETA(DisplayName = "Feet"),
	MAX			UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAccessoryEditState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	FName AccessoryID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	EAccessorySlot Slot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	bool bEquipped;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	FName MeshReference;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	FLinearColor Color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	FVector Offset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	FRotator Rotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Accessory")
	FVector Scale;

	FAccessoryEditState()
		: AccessoryID(NAME_None)
		, Slot(EAccessorySlot::MAX)
		, bEquipped(false)
		, MeshReference(NAME_None)
		, Color(FLinearColor::White)
		, Offset(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, Scale(FVector::OneVector)
	{
	}
};

UCLASS(Blueprintable, BlueprintType, Category = "Character Creation|Accessories")
class LESFIGHT_API ULesFightAccessorySystem : public UObject
{
	GENERATED_BODY()

public:
	ULesFightAccessorySystem();

	void Initialize(ULesFightCharCreationManager* InOwnerManager);

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	void EquipAccessory(const FAccessoryEditState& InAccessory);

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	void UnequipAccessory(EAccessorySlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	bool IsSlotOccupied(EAccessorySlot Slot) const;

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	FAccessoryEditState GetAccessory(EAccessorySlot Slot) const;

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	const TMap<EAccessorySlot, FAccessoryEditState>& GetAllAccessories() const;

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	void SetAccessoryTransform(EAccessorySlot Slot, const FVector& NewOffset, const FRotator& NewRotation, const FVector& NewScale);

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	void SetAccessoryColor(EAccessorySlot Slot, const FLinearColor& NewColor);

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	TArray<EAccessorySlot> GetAvailableSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	void ApplyToCharacter(AActor* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Accessory")
	void ResetToDefault();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Accessory")
	TMap<EAccessorySlot, FAccessoryEditState> EquippedAccessories;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Accessory")
	TArray<EAccessorySlot> AvailableSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Accessory", meta = (ClampMin = 1, ClampMax = 64))
	int32 MaxAccessories;

private:
	TWeakObjectPtr<ULesFightCharCreationManager> OwnerManager;
};
