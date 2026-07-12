#include "LesFightAppearanceComponent.h"
#include "LesFight.h"
#include "Components/SkeletalMeshComponent.h"

ULesFightAppearanceComponent::ULesFightAppearanceComponent()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ULesFightAppearanceComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightAppearanceComponent::Initialize(USkeletalMeshComponent* InMesh,
    const FCharacterCosmeticReferences& Cosmetics)
{
    TargetMesh = InMesh;
    CosmeticRefs = Cosmetics;

    if (TargetMesh.IsValid() && Cosmetics.BaseMesh.IsValid())
    {
        TargetMesh->SetSkeletalMesh(Cosmetics.BaseMesh.LoadSynchronous());
    }
}

void ULesFightAppearanceComponent::ApplyBaseMesh(USkeletalMesh* Mesh)
{
    if (TargetMesh.IsValid() && Mesh)
    {
        TargetMesh->SetSkeletalMesh(Mesh);
        OnAppearanceChanged.Broadcast(TEXT("BaseMesh"));
    }
}

void ULesFightAppearanceComponent::ApplySkinMaterial(int32 Index)
{
    if (!TargetMesh.IsValid() || !CosmeticRefs.SkinMaterials.IsValidIndex(Index)) return;

    UMaterialInstance* Material = CosmeticRefs.SkinMaterials[Index].LoadSynchronous();
    if (Material)
    {
        TargetMesh->SetMaterial(0, Material);
    }
}

void ULesFightAppearanceComponent::ApplyHairMaterial(int32 Index)
{
    if (!TargetMesh.IsValid() || !CosmeticRefs.HairMaterials.IsValidIndex(Index)) return;

    UMaterialInstance* Material = CosmeticRefs.HairMaterials[Index].LoadSynchronous();
    if (Material)
    {
        TargetMesh->SetMaterial(1, Material);
    }
}

void ULesFightAppearanceComponent::SetClothingSlot(int32 SlotIndex, UStaticMesh* ClothingMesh)
{
    if (!ClothingMesh) return;
    CurrentClothing.Add(SlotIndex, ClothingMesh);
    OnAppearanceChanged.Broadcast(TEXT("Clothing"));
}

void ULesFightAppearanceComponent::SetAccessorySlot(int32 SlotIndex, UStaticMesh* AccessoryMesh)
{
    if (!AccessoryMesh) return;
    CurrentAccessories.Add(SlotIndex, AccessoryMesh);
    OnAppearanceChanged.Broadcast(TEXT("Accessory"));
}

void ULesFightAppearanceComponent::ClearClothingSlot(int32 SlotIndex)
{
    CurrentClothing.Remove(SlotIndex);
}

void ULesFightAppearanceComponent::ClearAccessorySlot(int32 SlotIndex)
{
    CurrentAccessories.Remove(SlotIndex);
}

void ULesFightAppearanceComponent::ClearAllCosmetics()
{
    CurrentClothing.Empty();
    CurrentAccessories.Empty();
    OnAppearanceChanged.Broadcast(TEXT("AllCleared"));
}

void ULesFightAppearanceComponent::SetMaterialParameter(const FName& ParameterName, float Value)
{
    if (!TargetMesh.IsValid()) return;

    for (int32 i = 0; i < TargetMesh->GetNumMaterials(); i++)
    {
        UMaterialInstanceDynamic* DynamicMat = TargetMesh->CreateAndSetMaterialInstanceDynamic(i);
        if (DynamicMat)
        {
            DynamicMat->SetScalarParameterValue(ParameterName, Value);
        }
    }
}

void ULesFightAppearanceComponent::SetTextureParameter(const FName& ParameterName, UTexture* Texture)
{
    if (!TargetMesh.IsValid() || !Texture) return;

    for (int32 i = 0; i < TargetMesh->GetNumMaterials(); i++)
    {
        UMaterialInstanceDynamic* DynamicMat = TargetMesh->CreateAndSetMaterialInstanceDynamic(i);
        if (DynamicMat)
        {
            DynamicMat->SetTextureParameterValue(ParameterName, Texture);
        }
    }
}
