#include "LesFightCharacterSelectWidget.h"

void ULesFightCharacterSelectWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void ULesFightCharacterSelectWidget::AddFighter(FName FighterID, FText DisplayName, UTexture2D* Portrait, USkeletalMesh* Mesh, EFightingStyle Style)
{
    FFighterEntry Entry;
    Entry.FighterID = FighterID;
    Entry.DisplayName = DisplayName;
    Entry.Portrait = Portrait;
    Entry.Mesh = Mesh;
    Entry.Style = Style;
    AvailableFighters.Add(Entry);
}

void ULesFightCharacterSelectWidget::RemoveFighter(FName FighterID)
{
    for (int32 i = 0; i < AvailableFighters.Num(); ++i)
    {
        if (AvailableFighters[i].FighterID == FighterID)
        {
            AvailableFighters.RemoveAt(i);
            return;
        }
    }
}

void ULesFightCharacterSelectWidget::ClearFighters()
{
    AvailableFighters.Empty();
    SelectedIndex = -1;
    SelectedFighterID = NAME_None;
    bReady = false;
}

void ULesFightCharacterSelectWidget::SelectFighter(int32 GridIndex)
{
    if (!AvailableFighters.IsValidIndex(GridIndex))
    {
        return;
    }

    SelectedIndex = GridIndex;
    SelectedFighterID = AvailableFighters[GridIndex].FighterID;
    OnSelectionConfirmed.Broadcast(SelectedFighterID);
}

FName ULesFightCharacterSelectWidget::GetSelectedFighter() const
{
    return SelectedFighterID;
}

void ULesFightCharacterSelectWidget::SetFighterPreviewRotation(float Yaw)
{
    PreviewRotation = Yaw;
}

void ULesFightCharacterSelectWidget::ZoomPreview(float Delta)
{
    PreviewZoom = FMath::Clamp(PreviewZoom + Delta, 0.5f, 3.0f);
}

void ULesFightCharacterSelectWidget::ToggleFighterInfo()
{
    bInfoVisible = !bInfoVisible;
}

void ULesFightCharacterSelectWidget::SetReady(bool bNewReady)
{
    bReady = bNewReady;
    OnReadyChanged.Broadcast(bReady);
}

bool ULesFightCharacterSelectWidget::IsReady() const
{
    return bReady;
}

void ULesFightCharacterSelectWidget::SetCharacterInfo(FText Name, FText Style, FText Stats, FText Biography)
{
}

void ULesFightCharacterSelectWidget::NavigateToCreator()
{
    OnNavigateToCreator.Broadcast();
}

void ULesFightCharacterSelectWidget::NavigateToAIGeneration()
{
    OnNavigateToAI.Broadcast();
}

void ULesFightCharacterSelectWidget::NavigateBack()
{
    OnNavigateBack.Broadcast();
}
