#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightProfileManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileEvent, FName, ProfileID);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightProfileManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	FName CreateProfile(FText PlayerName);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	bool DeleteProfile(FName ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	bool SelectProfile(FName ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	bool RenameProfile(FName ProfileID, FText NewName);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	FPlayerProfileData GetProfile(FName ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	FPlayerProfileData GetCurrentProfile();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	TArray<FPlayerProfileData> GetAllProfiles();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	int32 GetProfileCount();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	void SetPlayerAvatar(FString AvatarPath);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	FString GetPlayerAvatar();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	bool AddCharacterToProfile(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	bool RemoveCharacterFromProfile(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	void IncrementPlayCount();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	void UpdateLastPlayed();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	bool IsProfileLoaded();

	UFUNCTION(BlueprintCallable, Category = "Profile Manager")
	int32 GetMaxProfiles();

	UPROPERTY(BlueprintAssignable, Category = "Profile Manager")
	FOnProfileEvent OnProfileCreated;

	UPROPERTY(BlueprintAssignable, Category = "Profile Manager")
	FOnProfileEvent OnProfileDeleted;

	UPROPERTY(BlueprintAssignable, Category = "Profile Manager")
	FOnProfileEvent OnProfileSelected;

	UPROPERTY(BlueprintAssignable, Category = "Profile Manager")
	FOnProfileEvent OnProfileUpdated;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Profile Manager")
	TArray<FPlayerProfileData> Profiles;

	UPROPERTY(VisibleAnywhere, Category = "Profile Manager")
	FPlayerProfileData CurrentProfile;

	UPROPERTY(VisibleAnywhere, Category = "Profile Manager")
	FName CurrentProfileID;

	UPROPERTY(EditDefaultsOnly, Category = "Profile Manager")
	int32 MaxProfiles = 8;

	UPROPERTY(VisibleAnywhere, Category = "Profile Manager")
	bool bProfileLoaded = false;
};
