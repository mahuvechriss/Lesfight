#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterBiography.generated.h"

UCLASS(Blueprintable)
class ULesFightCharacterBiography : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterBiography();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetCharacterName(const FString& Name);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    FString GetCharacterName() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetNickname(const FString& Nickname);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    FString GetNickname() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetAge(int32 Age);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    int32 GetAge() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetCountry(const FString& Country);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    FString GetCountry() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetBackstory(const FString& Backstory);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    FString GetBackstory() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetWeight(float Weight);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    float GetWeight() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void SetData(const FCharacterBiographyData& Data);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    FCharacterBiographyData GetData() const;

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Biography")
    void ResetToDefault();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FCharacterBiographyData CurrentBio;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxNameLength;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxBackstoryLength;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MinAge;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxAge;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TArray<FString> AvailableCountries;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
