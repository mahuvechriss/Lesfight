#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightClothingSystem.generated.h"

UCLASS(Blueprintable)
class ULesFightClothingSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightClothingSystem();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    bool EquipItem(EClothingSlot Slot, const FClothingItemData& Item);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    bool UnequipItem(EClothingSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    bool IsSlotEquipped(EClothingSlot Slot) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    FClothingItemData GetEquippedItem(EClothingSlot Slot) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    TMap<EClothingSlot, FClothingItemData> GetAllClothing() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    void SetAllFromMap(const TMap<EClothingSlot, FClothingItemData>& Clothing);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    void SetColor(EClothingSlot Slot, FLinearColor Color);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    void SetMaterialOverride(EClothingSlot Slot, UMaterialInterface* Material);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    TArray<EClothingSlot> GetAvailableSlots() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Clothing")
    void ResetToDefault();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<EClothingSlot, FClothingItemData> EquippedItems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<EClothingSlot> AvailableSlots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxLayers;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    TMap<EClothingSlot, TSoftObjectPtr<UMaterialInterface>> MaterialOverrides;
};
