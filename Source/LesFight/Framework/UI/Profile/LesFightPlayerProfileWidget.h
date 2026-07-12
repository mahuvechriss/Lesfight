#pragma once

#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightPlayerProfileWidget.generated.h"

USTRUCT(BlueprintType)
struct FStatEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
    FText StatName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
    float Value = 0.0f;
};

USTRUCT(BlueprintType)
struct FMatchEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
    FText OpponentName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
    bool bWon = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
    float Duration = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
    int32 RoundCount = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileSaved, FName, ProfileID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileLoaded, FName, ProfileID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileCreated, FName, ProfileID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNavigateBack);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPlayerProfileWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void LoadProfile(FName ProfileID);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void SaveCurrentProfile();

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void CreateNewProfile(FText ProfileName);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void SetPlayerAvatar(UTexture2D* Avatar);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void SetPlayerName(FText Name);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void SetPlayerTitle(FText Title);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void AddStat(FText StatName, float Value);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void UpdateStat(FText StatName, float NewValue);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void AddMatchHistoryEntry(FText OpponentName, bool bWon, float Duration, int32 RoundCount);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void ClearMatchHistory();

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void SetAchievementProgress(int32 AchievementIndex, float Progress);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void DisplayProfileSelection(TArray<FName> AvailableProfiles);

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void NavigateToEdit();

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void NavigateToSelect();

    UFUNCTION(BlueprintCallable, Category = "Profile")
    void NavigateBack();

    UPROPERTY(BlueprintAssignable, Category = "Profile")
    FOnProfileSaved OnProfileSaved;

    UPROPERTY(BlueprintAssignable, Category = "Profile")
    FOnProfileLoaded OnProfileLoaded;

    UPROPERTY(BlueprintAssignable, Category = "Profile")
    FOnProfileCreated OnProfileCreated;

    UPROPERTY(BlueprintAssignable, Category = "Profile")
    FOnNavigateBack OnNavigateBack;

protected:
    UPROPERTY()
    FName CurrentProfileID;

    UPROPERTY()
    FText PlayerName;

    UPROPERTY()
    FText PlayerTitle;

    UPROPERTY()
    UTexture2D* PlayerAvatar = nullptr;

    UPROPERTY()
    TArray<FStatEntry> PlayerStats;

    UPROPERTY()
    TArray<FMatchEntry> MatchHistory;

    UPROPERTY()
    TArray<float> AchievementProgress;
};
