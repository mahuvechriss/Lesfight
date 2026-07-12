#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightMaterialCustomization.generated.h"

USTRUCT(BlueprintType)
struct FMaterialEditState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MaterialSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor BaseColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Metallic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Roughness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> DiffuseTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> NormalTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UMaterialInterface> OverrideMaterial;
};

UCLASS(Blueprintable)
class ULesFightMaterialCustomization : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMaterialCustomization();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    void EditMaterialSlot(const FMaterialEditState& EditState);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    FMaterialEditState GetMaterialSlotState(FName SlotName) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    TArray<FName> GetEditableMaterialSlots() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    void ResetMaterialSlot(FName SlotName);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    void ResetAllMaterialSlots();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    TArray<FMaterialEditState> GetAllEditStates() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    void SetAllEditStates(const TArray<FMaterialEditState>& States);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    void SaveMaterialPreset(FName PresetName);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Materials")
    bool LoadMaterialPreset(FName PresetName);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<FName, FMaterialEditState> MaterialEditStates;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FName> DefaultMaterialSlots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TMap<FName, FMaterialEditState> SavedPresets;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
