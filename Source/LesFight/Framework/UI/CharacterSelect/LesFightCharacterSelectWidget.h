#pragma once

#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightCharacterSelectWidget.generated.h"

UENUM(BlueprintType)
enum class EFightingStyle : uint8
{
    Balanced,
    Rushdown,
    Grappler,
    Zoner,
    Trickster
};

USTRUCT(BlueprintType)
struct FFighterEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    FName FighterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    UTexture2D* Portrait = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    TSoftObjectPtr<USkeletalMesh> Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    EFightingStyle Style = EFightingStyle::Balanced;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    bool bIsCustom = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    bool bIsAI = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFighterSelected, FName, FighterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReadyChanged, bool, bReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNavigateToCreator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNavigateToAI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNavigateBackCS);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharacterSelectWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void AddFighter(FName FighterID, FText DisplayName, UTexture2D* Portrait, class USkeletalMesh* Mesh, EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void RemoveFighter(FName FighterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void ClearFighters();

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void SelectFighter(int32 GridIndex);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    FName GetSelectedFighter() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void SetFighterPreviewRotation(float Yaw);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void ZoomPreview(float Delta);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void ToggleFighterInfo();

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void SetReady(bool bNewReady);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    bool IsReady() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void SetCharacterInfo(FText Name, FText Style, FText Stats, FText Biography);

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void NavigateToCreator();

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void NavigateToAIGeneration();

    UFUNCTION(BlueprintCallable, Category = "CharacterSelect")
    void NavigateBack();

    UPROPERTY(BlueprintAssignable, Category = "CharacterSelect")
    FOnFighterSelected OnSelectionConfirmed;

    UPROPERTY(BlueprintAssignable, Category = "CharacterSelect")
    FOnReadyChanged OnReadyChanged;

    UPROPERTY(BlueprintAssignable, Category = "CharacterSelect")
    FOnNavigateToCreator OnNavigateToCreator;

    UPROPERTY(BlueprintAssignable, Category = "CharacterSelect")
    FOnNavigateToAI OnNavigateToAI;

    UPROPERTY(BlueprintAssignable, Category = "CharacterSelect")
    FOnNavigateBackCS OnNavigateBack;

protected:
    UPROPERTY()
    TArray<FFighterEntry> AvailableFighters;

    UPROPERTY()
    int32 SelectedIndex = -1;

    UPROPERTY()
    bool bReady = false;

    UPROPERTY()
    FName SelectedFighterID;

    UPROPERTY()
    float PreviewRotation = 0.0f;

    UPROPERTY()
    float PreviewZoom = 1.0f;

    UPROPERTY()
    bool bInfoVisible = false;
};
