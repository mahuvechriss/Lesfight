#include "LesFightAIResultEditor.h"
#include "Pipeline/LesFightAIPipelineManager.h"

ULesFightAIResultEditor::ULesFightAIResultEditor()
    : MaxEditHistory(50)
    , bHasUnsavedChanges(false)
{
}

void ULesFightAIResultEditor::Initialize(ULesFightAIManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightAIResultEditor::SetInitialPreset(const FCharacterCustomizationPreset& Preset)
{
    CurrentPreset = Preset;
    OriginalAIPreset = Preset;
    EditHistory.Empty();
    bHasUnsavedChanges = false;
}

void ULesFightAIResultEditor::EditFaceMorph(EFaceMorphType MorphType, float NewValue)
{
    CurrentPreset.FaceMorphs.Add(MorphType, NewValue);
    EditHistory.Add(FString::Printf(TEXT("FaceMorph %s = %.2f"), *UEnum::GetValueAsString(MorphType), NewValue));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::EditBodyMorph(EBodyMorphType MorphType, float NewValue)
{
    CurrentPreset.BodyMorphs.Add(MorphType, NewValue);
    EditHistory.Add(FString::Printf(TEXT("BodyMorph %s = %.2f"), *UEnum::GetValueAsString(MorphType), NewValue));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::EditHair(EHairStyle Style, FLinearColor Color)
{
    CurrentPreset.Hair.Style = Style;
    CurrentPreset.Hair.HairColor = Color;
    EditHistory.Add(FString::Printf(TEXT("Hair %s"), *UEnum::GetValueAsString(Style)));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::EditSkinTone(FLinearColor Tone)
{
    CurrentPreset.Skin.SkinTone = Tone;
    EditHistory.Add(FString::Printf(TEXT("SkinTone (%.2f, %.2f, %.2f)"), Tone.R, Tone.G, Tone.B));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::EditClothing(const TMap<EClothingSlot, FClothingItemData>& Clothing)
{
    CurrentPreset.Clothing = Clothing;
    EditHistory.Add(TEXT("Clothing replaced"));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::EditVoice(EVoicePack Pack, float Pitch, float Tone)
{
    CurrentPreset.Voice.VoicePack = Pack;
    CurrentPreset.Voice.Pitch = Pitch;
    CurrentPreset.Voice.Tone = Tone;
    EditHistory.Add(FString::Printf(TEXT("Voice %s Pitch=%.2f Tone=%.2f"), *UEnum::GetValueAsString(Pack), Pitch, Tone));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::EditBiography(const FCharacterBiographyData& Bio)
{
    CurrentPreset.Biography = Bio;
    EditHistory.Add(FString::Printf(TEXT("Biography: %s"), *Bio.CharacterName));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

FCharacterCustomizationPreset ULesFightAIResultEditor::GetCurrentPreset() const
{
    return CurrentPreset;
}

void ULesFightAIResultEditor::ApplyEditsToCharacter(AActor* CharacterActor)
{
    // Stub: apply CurrentPreset to the character actor
    bHasUnsavedChanges = false;
}

void ULesFightAIResultEditor::ResetToAIGenerated()
{
    CurrentPreset = OriginalAIPreset;
    EditHistory.Add(TEXT("Reset to AI-generated"));
    if (EditHistory.Num() > MaxEditHistory)
    {
        EditHistory.RemoveAt(0);
    }
    bHasUnsavedChanges = true;
}

void ULesFightAIResultEditor::UndoLastEdit()
{
    if (EditHistory.Num() == 0)
    {
        return;
    }
    EditHistory.RemoveAt(EditHistory.Num() - 1);
    CurrentPreset = OriginalAIPreset;
    for (const FString& Entry : EditHistory)
    {
        // In a full implementation this would replay the history
    }
    bHasUnsavedChanges = CurrentPreset != OriginalAIPreset;
}

TArray<FString> ULesFightAIResultEditor::GetEditHistory() const
{
    return EditHistory;
}

bool ULesFightAIResultEditor::HasUnsavedChanges() const
{
    return bHasUnsavedChanges;
}
