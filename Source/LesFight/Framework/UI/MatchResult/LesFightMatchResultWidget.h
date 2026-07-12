#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "LesFightMatchResultWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRematchRequested)
DECLARE_MULTICAST_DELEGATE(FOnReturnToMainMenu)
DECLARE_MULTICAST_DELEGATE(FOnReturnToCharacterSelect)

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMatchResultWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetWinnerInfo(FText Name, UTexture2D* Portrait, FText Title);

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetLoserInfo(FText Name, UTexture2D* Portrait, FText Title);

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetMatchDuration(float Seconds);

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetComboStats(int32 MaxCombo, int32 TotalCombos, float ComboAccuracy);

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetDamageStats(float TotalDamage, float DamagePerSecond, int32 HitsLanded, int32 HitsReceived);

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetPerformanceRating(float Rating);

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void SetRewards(int32 XP, int32 Currency, TArray<FText> UnlockedItems);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MatchResult")
    void PlayVictoryAnimation();
    virtual void PlayVictoryAnimation_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MatchResult")
    void PlayDefeatAnimation();
    virtual void PlayDefeatAnimation_Implementation();

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void RequestRematch();

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void ReturnToMainMenu();

    UFUNCTION(BlueprintCallable, Category = "MatchResult")
    void ReturnToCharacterSelect();

    FOnRematchRequested OnRematchRequested;
    FOnReturnToMainMenu OnReturnToMainMenu;
    FOnReturnToCharacterSelect OnReturnToCharacterSelect;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    FText WinnerName;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    FText LoserName;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    FText WinnerTitle;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    FText LoserTitle;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    UTexture2D* WinnerPortrait = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    UTexture2D* LoserPortrait = nullptr;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    float MatchDuration = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    float PerformanceRating = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    int32 MaxCombo = 0;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    int32 TotalCombos = 0;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    float ComboAccuracy = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    float TotalDamage = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    float DamagePerSecond = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    int32 HitsLanded = 0;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    int32 HitsReceived = 0;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    int32 RewardXP = 0;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    int32 RewardCurrency = 0;

    UPROPERTY(BlueprintReadOnly, Category = "MatchResult")
    TArray<FText> UnlockedItems;
};
