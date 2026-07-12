#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightDataSecurity.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightDataSecurity : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Data Security")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	FString GenerateChecksum(const TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	bool ValidateChecksum(const TArray<uint8>& Data, const FString& Checksum);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	bool ValidateSaveIntegrity(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	TArray<uint8> EncryptData(const TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	TArray<uint8> DecryptData(const TArray<uint8>& EncryptedData);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	bool IsDataCorrupted(const TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	FString SanitizePlayerName(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	bool ValidateProfileData(const FPlayerProfileData& Profile);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	bool ValidateCharacterData(const FCharacterSaveData& Character);

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	FString GetLastError() const { return LastError; }

	UFUNCTION(BlueprintCallable, Category = "Data Security")
	void SetEncryptionEnabled(bool bEnabled) { bEncryptionEnabled = bEnabled; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data Security")
	bool bEncryptionEnabled = false;

	UPROPERTY(VisibleAnywhere, Category = "Data Security")
	FString LastError;

	UPROPERTY(EditDefaultsOnly, Category = "Data Security")
	int32 ChecksumSeed = 1337;

private:
	uint32 ComputeFNV1a(const TArray<uint8>& Data) const;
};
