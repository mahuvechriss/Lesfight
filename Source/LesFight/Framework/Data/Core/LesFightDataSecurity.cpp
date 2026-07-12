#include "Framework/Data/Core/LesFightDataSecurity.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"

void ULesFightDataSecurity::Initialize()
{
}

void ULesFightDataSecurity::Shutdown()
{
}

uint32 ULesFightDataSecurity::ComputeFNV1a(const TArray<uint8>& Data) const
{
	uint32 Hash = 0x811C9DC5 ^ (uint32)ChecksumSeed;
	for (uint8 Byte : Data)
	{
		Hash ^= Byte;
		Hash *= 0x01000193;
	}
	return Hash;
}

FString ULesFightDataSecurity::GenerateChecksum(const TArray<uint8>& Data)
{
	uint32 Hash = ComputeFNV1a(Data);
	return FString::Printf(TEXT("%08X"), Hash);
}

bool ULesFightDataSecurity::ValidateChecksum(const TArray<uint8>& Data, const FString& Checksum)
{
	FString Expected = GenerateChecksum(Data);
	return Expected.Equals(Checksum, ESearchCase::IgnoreCase);
}

bool ULesFightDataSecurity::ValidateSaveIntegrity(const FString& FilePath)
{
	if (!IFileManager::Get().FileExists(*FilePath))
	{
		LastError = TEXT("File does not exist");
		return false;
	}

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
	{
		LastError = TEXT("Failed to read file");
		return false;
	}

	if (FileData.Num() == 0)
	{
		LastError = TEXT("File is empty");
		return false;
	}

	if (FileData.Num() < 64)
	{
		LastError = TEXT("File too small to contain checksum");
		return false;
	}

	FString EmbeddedChecksum;
	{
		int32 DataLen = FileData.Num() - 64;
		TArray<uint8> DataPart;
		DataPart.Append(&FileData[0], DataLen);

		FString ChecksumStr;
		for (int32 i = DataLen; i < FileData.Num(); ++i)
		{
			ChecksumStr.AppendChar((TCHAR)FileData[i]);
		}
		EmbeddedChecksum = ChecksumStr;
	}

	bool bValid = ValidateChecksum(FileData, EmbeddedChecksum);
	if (!bValid)
	{
		LastError = TEXT("Checksum mismatch - data may be corrupted");
	}
	return bValid;
}

TArray<uint8> ULesFightDataSecurity::EncryptData(const TArray<uint8>& Data)
{
	if (!bEncryptionEnabled)
	{
		return Data;
	}

	TArray<uint8> Encrypted;
	Encrypted.SetNum(Data.Num());
	for (int32 i = 0; i < Data.Num(); ++i)
	{
		Encrypted[i] = Data[i] ^ (uint8)((ChecksumSeed + i) & 0xFF);
	}
	return Encrypted;
}

TArray<uint8> ULesFightDataSecurity::DecryptData(const TArray<uint8>& EncryptedData)
{
	if (!bEncryptionEnabled)
	{
		return EncryptedData;
	}

	TArray<uint8> Decrypted;
	Decrypted.SetNum(EncryptedData.Num());
	for (int32 i = 0; i < EncryptedData.Num(); ++i)
	{
		Decrypted[i] = EncryptedData[i] ^ (uint8)((ChecksumSeed + i) & 0xFF);
	}
	return Decrypted;
}

bool ULesFightDataSecurity::IsDataCorrupted(const TArray<uint8>& Data)
{
	if (Data.Num() == 0)
	{
		LastError = TEXT("Data is empty");
		return true;
	}

	return false;
}

FString ULesFightDataSecurity::SanitizePlayerName(const FString& Name)
{
	FString Sanitized;
	for (int32 i = 0; i < Name.Len(); ++i)
	{
		TCHAR Char = Name[i];
		if (FChar::IsAlnum(Char) || Char == TEXT(' ') || Char == TEXT('-'))
		{
			Sanitized.AppendChar(Char);
		}
	}
	return Sanitized;
}

bool ULesFightDataSecurity::ValidateProfileData(const FPlayerProfileData& Profile)
{
	if (Profile.PlayerName.IsEmpty())
	{
		LastError = TEXT("Player name is empty");
		return false;
	}

	if (Profile.ProfileID.IsNone())
	{
		LastError = TEXT("Profile ID is None");
		return false;
	}

	return true;
}

bool ULesFightDataSecurity::ValidateCharacterData(const FCharacterSaveData& Character)
{
	if (Character.CharacterID.IsNone())
	{
		LastError = TEXT("Character ID is None");
		return false;
	}

	if (Character.CharacterName.IsEmpty())
	{
		LastError = TEXT("Character name is empty");
		return false;
	}

	return true;
}
