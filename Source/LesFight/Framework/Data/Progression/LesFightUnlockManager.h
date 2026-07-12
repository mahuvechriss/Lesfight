#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightUnlockManager.generated.h"

USTRUCT(BlueprintType)
struct FUnlockableInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	EUnlockType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	FName RequiredAchievement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	int32 RequiredLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockable")
	bool bIsUnlocked = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUnlockedDelegate, FName, ItemID, EUnlockType, Type);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUnlockManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Unlock")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	bool UnlockItem(FName ItemID, EUnlockType Type);

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	bool IsItemUnlocked(FName ItemID) const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	TArray<FName> GetUnlockedItems(EUnlockType Type) const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	TArray<FName> GetAllUnlockedItems() const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	bool LockItem(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	void RegisterUnlockable(FName ItemID, EUnlockType Type, FText DisplayName, FText Description, FName RequiredAchievement, int32 RequiredLevel);

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	FUnlockableInfo GetUnlockableInfo(FName ItemID) const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	TArray<FUnlockableInfo> GetAvailableUnlockables(EUnlockType Type) const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	TArray<FUnlockableInfo> GetLockedUnlockables(EUnlockType Type) const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	TArray<FName> CheckAndUnlockByLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	TArray<FName> CheckAndUnlockByAchievement(FName AchievementID);

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	int32 GetTotalUnlocked() const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	int32 GetTotalUnlockables() const;

	UFUNCTION(BlueprintCallable, Category = "Unlock")
	void ResetAllUnlocks();

	UPROPERTY(BlueprintAssignable, Category = "Unlock")
	FOnItemUnlockedDelegate OnItemUnlocked;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unlock")
	TArray<FName> UnlockedItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unlock")
	TMap<FName, FUnlockableInfo> UnlockableRegistry;
};
