#include "LesFightStyleManager.h"
#include "LesFightFightingStyle.h"
#include "LesFightMartialArtsManager.h"

ULesFightStyleManager::ULesFightStyleManager()
    : CurrentStyleID(EFightingStyle::None)
    , CurrentStyle(nullptr)
    , StyleData(nullptr)
{
}

void ULesFightStyleManager::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    RegisterAllStyles();

    if (StyleRegistry.Num() > 0)
    {
        auto FirstStyle = StyleRegistry.CreateIterator();
        EquipStyle(FirstStyle.Key());
    }
}

void ULesFightStyleManager::Tick(float DeltaTime)
{
    if (CurrentStyle)
    {
        CurrentStyle->Tick(DeltaTime);
    }
}

bool ULesFightStyleManager::EquipStyle(EFightingStyle StyleID)
{
    ULesFightFightingStyle** Found = StyleRegistry.Find(StyleID);
    if (!Found || !*Found) return false;

    if (CurrentStyle && CurrentStyleID == StyleID) return true;

    if (CurrentStyle)
    {
        CurrentStyle->OnUnequip();
    }

    CurrentStyle = *Found;
    CurrentStyleID = StyleID;
    ApplyStyleAttributes(CurrentStyle);
    CurrentStyle->OnEquip();
    OnStyleChanged.Broadcast(StyleID);

    return true;
}

bool ULesFightStyleManager::UnlockStyle(EFightingStyle StyleID)
{
    if (UnlockedStylesSet.Contains(StyleID)) return true;

    UnlockedStylesSet.Add(StyleID);
    OnStyleUnlocked.Broadcast(StyleID);
    return true;
}

ULesFightFightingStyle* ULesFightStyleManager::GetStyle(EFightingStyle StyleID) const
{
    const TObjectPtr<ULesFightFightingStyle>* Found = StyleRegistry.Find(StyleID);
    return Found ? Found->Get() : nullptr;
}

TArray<EFightingStyle> ULesFightStyleManager::GetUnlockedStyles() const
{
    TArray<EFightingStyle> Result;
    for (EFightingStyle Style : UnlockedStylesSet)
    {
        Result.Add(Style);
    }
    return Result;
}

TArray<EFightingStyle> ULesFightStyleManager::GetAllAvailableStyles() const
{
    TArray<EFightingStyle> Result;
    StyleRegistry.GetKeys(Result);
    return Result;
}

FStyleAttributes ULesFightStyleManager::GetCurrentAttributes() const
{
    if (CurrentStyle)
    {
        return CurrentStyle->GetAttributes();
    }
    return FStyleAttributes();
}

void ULesFightStyleManager::SetStyleDataAsset(ULesFightMartialArtsDataAsset* DataAsset)
{
    StyleData = DataAsset;
}

void ULesFightStyleManager::ResetToDefault()
{
    if (CurrentStyle)
    {
        CurrentStyle->OnUnequip();
    }
    CurrentStyle = nullptr;
    CurrentStyleID = EFightingStyle::None;
    UnlockedStylesSet.Empty();

    if (StyleRegistry.Num() > 0)
    {
        auto FirstStyle = StyleRegistry.CreateIterator();
        EquipStyle(FirstStyle.Key());
    }
}

ULesFightFightingStyle* ULesFightStyleManager::CreateStyleInstance(EFightingStyle StyleID)
{
    ULesFightFightingStyle* Instance = NewObject<ULesFightFightingStyle>(this);
    if (Instance)
    {
        Instance->Initialize(StyleID);
        if (StyleData)
        {
            const FStyleAttributes* Attr = StyleData->StyleDefinitions.Find(StyleID);
            if (Attr)
            {
                Instance->SetAttributes(*Attr);
            }
        }
    }
    return Instance;
}

void ULesFightStyleManager::RegisterAllStyles()
{
    for (int32 i = 1; i < static_cast<int32>(EFightingStyle::MAX); i++)
    {
        EFightingStyle Style = static_cast<EFightingStyle>(i);
        ULesFightFightingStyle* Instance = CreateStyleInstance(Style);
        if (Instance)
        {
            StyleRegistry.Add(Style, Instance);
            UnlockedStylesSet.Add(Style);
        }
    }
}

void ULesFightStyleManager::ApplyStyleAttributes(ULesFightFightingStyle* Style)
{
}
