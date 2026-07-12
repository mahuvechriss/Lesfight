#include "LesFightAIGenerationUI.h"

void ULesFightAIGenerationUI::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    CurrentStage = EPhotoProcessingStage::WaitingForPhoto;
}

void ULesFightAIGenerationUI::OpenPhotoUpload()
{
    OnPhotoSelected.Broadcast(nullptr);
}

void ULesFightAIGenerationUI::SelectPhotoFromDevice()
{
}

void ULesFightAIGenerationUI::TakePhoto()
{
}

void ULesFightAIGenerationUI::SetImagePreview(UTexture2D* Image)
{
    SelectedPhoto = Image;
}

void ULesFightAIGenerationUI::ClearImagePreview()
{
    SelectedPhoto = nullptr;
}

void ULesFightAIGenerationUI::StartProcessing()
{
    CurrentStage = EPhotoProcessingStage::Processing;
    ProcessingProgress = 0.0f;
}

void ULesFightAIGenerationUI::CancelProcessing()
{
    CurrentStage = EPhotoProcessingStage::WaitingForPhoto;
    ProcessingProgress = 0.0f;
}

void ULesFightAIGenerationUI::SetProcessingProgress(float Progress)
{
    ProcessingProgress = FMath::Clamp(Progress, 0.0f, 1.0f);
}

void ULesFightAIGenerationUI::SetProcessingStatus(FText Status)
{
}

void ULesFightAIGenerationUI::SetProcessingStage(EPhotoProcessingStage Stage)
{
    CurrentStage = Stage;
}

void ULesFightAIGenerationUI::ShowGeneratedPreview(USkeletalMesh* Mesh, UTexture2D* Texture)
{
    GeneratedMesh = Mesh;
    GeneratedTexture = Texture;
    CurrentStage = EPhotoProcessingStage::Complete;
}

void ULesFightAIGenerationUI::AdjustResult(float ParameterIndex, float Value)
{
    int32 Index = FMath::Clamp((int32)ParameterIndex, 0, AdjustmentParameters.Num() - 1);
    if (AdjustmentParameters.Num() > 0)
    {
        AdjustmentParameters[Index] = Value;
    }
}

void ULesFightAIGenerationUI::ConfirmCharacter(FName CharacterName)
{
    if (CharacterName.IsNone())
    {
        return;
    }

    CurrentStage = EPhotoProcessingStage::Complete;
    OnGenerationConfirmed.Broadcast(CharacterName);
}

void ULesFightAIGenerationUI::RegenerateCharacter()
{
    CurrentStage = EPhotoProcessingStage::Processing;
    ProcessingProgress = 0.0f;
}

void ULesFightAIGenerationUI::ResetToDefaults()
{
    SelectedPhoto = nullptr;
    GeneratedTexture = nullptr;
    GeneratedMesh.Reset();
    ProcessingProgress = 0.0f;
    CurrentStage = EPhotoProcessingStage::WaitingForPhoto;
    AdjustmentParameters.Empty();
}
