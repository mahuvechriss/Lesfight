#include "LesFightCharCreatorWidget.h"

void ULesFightCharCreatorWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Categories.SetNum(7);

    Categories[0].CategoryName = FText::FromString("Face");
    Categories[0].SubOptions = { FText::FromString("Angular"), FText::FromString("Round"), FText::FromString("Strong"), FText::FromString("Elven") };

    Categories[1].CategoryName = FText::FromString("Body");
    Categories[1].SubOptions = { FText::FromString("Lean"), FText::FromString("Athletic"), FText::FromString("Heavy"), FText::FromString("Muscular") };

    Categories[2].CategoryName = FText::FromString("Hair");
    Categories[2].SubOptions = { FText::FromString("Bald"), FText::FromString("Short"), FText::FromString("Long"), FText::FromString("Spiked"), FText::FromString("Ponytail") };

    Categories[3].CategoryName = FText::FromString("Clothing");
    Categories[3].SubOptions = { FText::FromString("Gi"), FText::FromString("Streetwear"), FText::FromString("Armor"), FText::FromString("Casual") };

    Categories[4].CategoryName = FText::FromString("Accessories");
    Categories[4].SubOptions = { FText::FromString("None"), FText::FromString("Headband"), FText::FromString("Gloves"), FText::FromString("Amulet"), FText::FromString("Mask") };

    Categories[5].CategoryName = FText::FromString("Voice");
    Categories[5].SubOptions = { FText::FromString("Bold"), FText::FromString("Calm"), FText::FromString("Rough"), FText::FromString("Elegant") };

    Categories[6].CategoryName = FText::FromString("FightingStyle");
    Categories[6].SubOptions = { FText::FromString("Balanced"), FText::FromString("Rushdown"), FText::FromString("Grappler"), FText::FromString("Zoner"), FText::FromString("Trickster") };
}

void ULesFightCharCreatorWidget::SelectCategory(int32 CategoryIndex)
{
    if (Categories.IsValidIndex(CategoryIndex))
    {
        CurrentCategoryIndex = CategoryIndex;
        CurrentSubOptionIndex = -1;
        OnCategoryChanged.Broadcast(CategoryIndex);
    }
}

void ULesFightCharCreatorWidget::SelectSubOption(int32 CategoryIndex, int32 OptionIndex)
{
    if (Categories.IsValidIndex(CategoryIndex))
    {
        const TArray<FText>& SubOptions = Categories[CategoryIndex].SubOptions;
        if (SubOptions.IsValidIndex(OptionIndex))
        {
            FUndoRedoState State;
            State.CategoryIndex = CurrentCategoryIndex;
            State.SubOptionIndex = CurrentSubOptionIndex;

            if (UndoStack.Num() >= 20)
            {
                UndoStack.RemoveAt(0);
            }
            UndoStack.Add(State);
            RedoStack.Empty();

            CurrentCategoryIndex = CategoryIndex;
            CurrentSubOptionIndex = OptionIndex;
        }
    }
}

void ULesFightCharCreatorWidget::ConfirmSelection()
{
    CurrentCharacterID = FName(*FString::Printf(TEXT("CustomChar_%d_%d"), CurrentCategoryIndex, CurrentSubOptionIndex));
    OnCharacterConfirmed.Broadcast(CurrentCharacterID);
}

void ULesFightCharCreatorWidget::UndoLastChange()
{
    if (UndoStack.Num() == 0)
    {
        return;
    }

    FUndoRedoState CurrentState;
    CurrentState.CategoryIndex = CurrentCategoryIndex;
    CurrentState.SubOptionIndex = CurrentSubOptionIndex;

    if (RedoStack.Num() >= 20)
    {
        RedoStack.RemoveAt(0);
    }
    RedoStack.Add(CurrentState);

    FUndoRedoState PreviousState = UndoStack.Pop();
    CurrentCategoryIndex = PreviousState.CategoryIndex;
    CurrentSubOptionIndex = PreviousState.SubOptionIndex;
}

void ULesFightCharCreatorWidget::RedoLastChange()
{
    if (RedoStack.Num() == 0)
    {
        return;
    }

    FUndoRedoState CurrentState;
    CurrentState.CategoryIndex = CurrentCategoryIndex;
    CurrentState.SubOptionIndex = CurrentSubOptionIndex;

    if (UndoStack.Num() >= 20)
    {
        UndoStack.RemoveAt(0);
    }
    UndoStack.Add(CurrentState);

    FUndoRedoState NextState = RedoStack.Pop();
    CurrentCategoryIndex = NextState.CategoryIndex;
    CurrentSubOptionIndex = NextState.SubOptionIndex;
}

void ULesFightCharCreatorWidget::RandomizeCharacter()
{
    for (int32 i = 0; i < Categories.Num(); ++i)
    {
        if (Categories[i].SubOptions.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, Categories[i].SubOptions.Num() - 1);
            SelectSubOption(i, RandomIndex);
        }
    }
}

void ULesFightCharCreatorWidget::SavePreset(FText PresetName)
{
}

void ULesFightCharCreatorWidget::LoadPreset(FName PresetID)
{
}

void ULesFightCharCreatorWidget::SetLivePreview(USkeletalMeshComponent* PreviewMesh)
{
    bLivePreviewActive = (PreviewMesh != nullptr);
}

void ULesFightCharCreatorWidget::ToggleCompareMode()
{
    bCompareMode = !bCompareMode;
}

bool ULesFightCharCreatorWidget::IsCompareModeActive() const
{
    return bCompareMode;
}

int32 ULesFightCharCreatorWidget::GetCurrentCategory() const
{
    return CurrentCategoryIndex;
}

int32 ULesFightCharCreatorWidget::GetCurrentSubOption() const
{
    return CurrentSubOptionIndex;
}

void ULesFightCharCreatorWidget::SetPreviewLighting(FLinearColor Color, float Intensity)
{
}
