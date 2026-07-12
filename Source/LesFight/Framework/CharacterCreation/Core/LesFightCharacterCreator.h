#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterCreator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterCreated, FName, CharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDeleted, FName, CharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDuplicated, FName, NewCharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterUpdated, FName, CharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMorphUpdated, FName, MorphName);

UCLASS(Blueprintable)
class ULesFightCharacterCreator : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterCreator();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    FName CreateNewCharacter(const FCharacterBiographyData& BioData);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    bool EditCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    bool DuplicateCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    bool DeleteCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    FCharacterCustomizationPreset GetCharacterData(FName CharacterID) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    bool SetCharacterData(FName CharacterID, const FCharacterCustomizationPreset& Data);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void SetActiveCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    FName GetActiveCharacterID() const { return ActiveCharacterID; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    FCharacterCustomizationPreset GetActiveCharacterData() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    TArray<FName> GetAllCharacterIDs() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    int32 GetCharacterCount() const { return CharacterData.Num(); }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    FValidationResult ValidateCharacter(FName CharacterID) const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator")
    void ClearAllCharacters();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCharacterCreated OnCharacterCreated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCharacterDeleted OnCharacterDeleted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCharacterDuplicated OnCharacterDuplicated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCharacterUpdated OnCharacterUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMorphUpdated OnMorphUpdated;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<FName, FCharacterCustomizationPreset> CharacterData;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName ActiveCharacterID;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECharacterCreatorMode CurrentMode;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    int32 NextCharacterIndex;

    FName GenerateCharacterID();
};
