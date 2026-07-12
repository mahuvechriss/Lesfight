#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightCharacterMusicSystem.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightCharacterMusicSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void RegisterCharacterTheme(FName CharacterID, FName ThemeName);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void PlayEntranceMusic(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void PlayVictoryMusic(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void PlayDefeatMusic(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void PlayUltimateMusic(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void SetPlayerMusicRole(EFighterMusicRole Role);

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    FName GetCharacterTheme(FName CharacterID) const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void ClearCharacterThemes();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    TMap<FName, FName> CharacterThemes;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    TMap<FName, TArray<FString>> ThemeSongs;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    EFighterMusicRole CurrentRole;

private:
    void BuildDefaultThemes();

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
