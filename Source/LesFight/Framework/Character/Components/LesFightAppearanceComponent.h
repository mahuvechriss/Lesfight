#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightCharacterData.h"
#include "LesFightAppearanceComponent.generated.h"

class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppearanceChanged, const FString&, ChangeType);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightAppearanceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightAppearanceComponent();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void Initialize(USkeletalMeshComponent* InMesh, const FCharacterCosmeticReferences& Cosmetics);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void ApplyBaseMesh(USkeletalMesh* Mesh);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void ApplySkinMaterial(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void ApplyHairMaterial(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void SetClothingSlot(int32 SlotIndex, UStaticMesh* ClothingMesh);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void SetAccessorySlot(int32 SlotIndex, UStaticMesh* AccessoryMesh);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void ClearClothingSlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void ClearAccessorySlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void ClearAllCosmetics();

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void SetMaterialParameter(const FName& ParameterName, float Value);

    UFUNCTION(BlueprintCallable, Category = "Appearance")
    void SetTextureParameter(const FName& ParameterName, UTexture* Texture);

    UFUNCTION(BlueprintPure, Category = "Appearance")
    FCharacterCosmeticReferences GetCosmeticReferences() const { return CosmeticRefs; }

    UFUNCTION(BlueprintPure, Category = "Appearance")
    USkeletalMeshComponent* GetTargetMesh() const { return TargetMesh.Get(); }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
    TArray<FName> ClothingSlotNames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
    TArray<FName> AccessorySlotNames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance")
    FCharacterCosmeticReferences CosmeticRefs;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAppearanceChanged OnAppearanceChanged;

private:
    TWeakObjectPtr<USkeletalMeshComponent> TargetMesh;
    TMap<int32, TObjectPtr<UStaticMesh>> CurrentClothing;
    TMap<int32, TObjectPtr<UStaticMesh>> CurrentAccessories;
};
