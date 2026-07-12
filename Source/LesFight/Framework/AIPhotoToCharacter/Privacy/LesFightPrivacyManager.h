#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightPrivacyManager.generated.h"

class ULesFightAIManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPrivacyManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void Initialize(ULesFightAIManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void RequestUserConsent();

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    bool HasUserConsent() const;

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void RevokeConsent();

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void SetAutoDeleteImages(bool bAutoDelete);

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    bool GetAutoDeleteImages() const;

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void SetRetentionPeriod(int32 Minutes);

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    int32 GetRetentionPeriod() const;

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void SetLocalProcessingOnly(bool bLocalOnly);

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    bool IsLocalProcessingOnly() const;

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void PurgeAllUserData();

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    const FPrivacySettings& GetPrivacySettings() const;

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void ApplyPrivacySettings(const FPrivacySettings& Settings);

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    void LogPrivacyEvent(const FString& Event);

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    TArray<FString> GetPrivacyLog() const;

    UFUNCTION(BlueprintCallable, Category = "Privacy")
    bool IsDataAnonymized() const;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Privacy")
    FPrivacySettings CurrentSettings;

    UPROPERTY()
    TArray<FString> PrivacyEventLog;

    UPROPERTY(Config)
    int32 MaxLogEntries = 100;

    UPROPERTY()
    bool bPrivacyInitialized = false;

private:
    TWeakObjectPtr<ULesFightAIManager> OwnerManager;
};
