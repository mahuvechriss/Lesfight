#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharacterData.h"
#include "LesFightCharacterSelectionManager.generated.h"

class ULesFightFighterDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelectionChanged, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterLockedChanged, FName, CharacterID, bool, bNowLocked);

USTRUCT(BlueprintType)
struct FCharacterSelectionEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSelected;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SelectedByPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Portrait;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString UnlockCondition;

    FCharacterSelectionEntry()
        : bIsUnlocked(true)
        , bIsSelected(false)
        , SelectedByPlayer(-1)
    {}
};

UCLASS(Blueprintable, Config = Game)
class ULesFightCharacterSelectionManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterSelectionManager();

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void PopulateCharacterList(const TArray<FCharacterTableRow>& CharacterDataList);

    UFUNCTION(BlueprintCallable, Category = "Selection")
    bool SelectCharacter(int32 PlayerIndex, FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void DeselectCharacter(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void ConfirmSelection(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void UnlockCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void LockCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Selection")
    void ResetSelections();

    UFUNCTION(BlueprintPure, Category = "Selection")
    TArray<FCharacterSelectionEntry> GetAvailableCharacters() const { return AvailableCharacters; }

    UFUNCTION(BlueprintPure, Category = "Selection")
    TArray<FCharacterSelectionEntry> GetUnlockedCharacters() const;

    UFUNCTION(BlueprintPure, Category = "Selection")
    FCharacterSelectionEntry GetCharacterEntry(FName CharacterID) const;

    UFUNCTION(BlueprintPure, Category = "Selection")
    FName GetSelectedCharacter(int32 PlayerIndex) const;

    UFUNCTION(BlueprintPure, Category = "Selection")
    bool IsCharacterUnlocked(FName CharacterID) const;

    UFUNCTION(BlueprintPure, Category = "Selection")
    bool AreAllPlayersReady() const;

    UFUNCTION(BlueprintPure, Category = "Selection")
    int32 GetNumPlayersReady() const { return PlayersReady.Num(); }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Selection")
    TArray<FCharacterSelectionEntry> AvailableCharacters;

    UPROPERTY(BlueprintReadOnly, Category = "Selection")
    TSet<int32> PlayersReady;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCharacterSelectionChanged OnCharacterSelectionChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCharacterLockedChanged OnCharacterLockedChanged;

private:
    TMap<int32, FName> PlayerSelections;
    TSet<FName> LockedCharacters;
};
