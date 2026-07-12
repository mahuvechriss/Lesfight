#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightCharCreatorWidget.generated.h"

USTRUCT(BlueprintType)
struct FCategoryDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Category")
    FText CategoryName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Category")
    TArray<FText> SubOptions;
};

USTRUCT(BlueprintType)
struct FUndoRedoState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UndoRedo")
    int32 CategoryIndex = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UndoRedo")
    int32 SubOptionIndex = -1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCategoryChanged, int32, CategoryIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterConfirmed, FName, CharacterID);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharCreatorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void SelectCategory(int32 CategoryIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void SelectSubOption(int32 CategoryIndex, int32 OptionIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void ConfirmSelection();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void UndoLastChange();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void RedoLastChange();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void RandomizeCharacter();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void SavePreset(FText PresetName);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void LoadPreset(FName PresetID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void SetLivePreview(class USkeletalMeshComponent* PreviewMesh);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void ToggleCompareMode();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    bool IsCompareModeActive() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    int32 GetCurrentCategory() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    int32 GetCurrentSubOption() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void SetPreviewLighting(FLinearColor Color, float Intensity);

    UPROPERTY(BlueprintAssignable, Category = "CharacterCreator")
    FOnCategoryChanged OnCategoryChanged;

    UPROPERTY(BlueprintAssignable, Category = "CharacterCreator")
    FOnCharacterConfirmed OnCharacterConfirmed;

protected:
    UPROPERTY()
    int32 CurrentCategoryIndex = -1;

    UPROPERTY()
    int32 CurrentSubOptionIndex = -1;

    UPROPERTY()
    TArray<FCategoryDef> Categories;

    UPROPERTY()
    TArray<FUndoRedoState> UndoStack;

    UPROPERTY()
    TArray<FUndoRedoState> RedoStack;

    UPROPERTY()
    bool bCompareMode = false;

    UPROPERTY()
    bool bLivePreviewActive = false;

    UPROPERTY()
    FName CurrentCharacterID;
};
