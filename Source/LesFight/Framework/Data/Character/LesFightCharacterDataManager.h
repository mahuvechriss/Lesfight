#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightCharacterDataManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDataEvent, FName, CharacterID);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharacterDataManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	ESaveResult SaveCharacter(FCharacterSaveData CharacterData);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	FCharacterSaveData LoadCharacter(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	bool DeleteCharacter(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	TArray<FCharacterSaveData> GetAllSavedCharacters();

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	FCharacterSaveData GetCharacter(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	int32 GetCharacterCount();

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	bool CharacterExists(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	FName DuplicateCharacter(FName SourceCharacterID, FText NewName);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	TArray<FCharacterSaveData> GetCharactersByStyle(EFightingStyle Style);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	TArray<FCharacterSaveData> GetCharactersByType(bool bAIGenerated);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	bool UpdateCharacterAppearance(FName CharacterID, FCharacterAppearanceData Appearance);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	bool UpdateCharacterGameplay(FName CharacterID, FCharacterGameplayData Gameplay);

	UFUNCTION(BlueprintCallable, Category = "Character Data Manager")
	int32 GetMaxCharacters();

	UPROPERTY(BlueprintAssignable, Category = "Character Data Manager")
	FOnCharacterDataEvent OnCharacterSaved;

	UPROPERTY(BlueprintAssignable, Category = "Character Data Manager")
	FOnCharacterDataEvent OnCharacterDeleted;

	UPROPERTY(BlueprintAssignable, Category = "Character Data Manager")
	FOnCharacterDataEvent OnCharacterUpdated;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Character Data Manager")
	TArray<FCharacterSaveData> SavedCharacters;

	UPROPERTY(EditDefaultsOnly, Category = "Character Data Manager")
	int32 MaxCharacters = 100;

	UPROPERTY(VisibleAnywhere, Category = "Character Data Manager")
	bool bLoaded = false;
};
