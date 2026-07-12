#include "LesFightProfileManager.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "Misc/DateTime.h"

class ULesFightSaveManager;

void ULesFightProfileManager::Initialize()
{
	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			// SaveManager would load profiles here
			bProfileLoaded = true;
		}
	}
}

void ULesFightProfileManager::Shutdown()
{
	CurrentProfile = FPlayerProfileData();
	CurrentProfileID = NAME_None;
	Profiles.Empty();
	bProfileLoaded = false;
}

FName ULesFightProfileManager::CreateProfile(FText PlayerName)
{
	if (Profiles.Num() >= MaxProfiles)
	{
		return NAME_None;
	}

	FName ProfileID = FName(*FString::Printf(TEXT("Profile_%lld"), FDateTime::Now().Ticks()));

	FPlayerProfileData NewProfile;
	NewProfile.ProfileID = ProfileID;
	NewProfile.PlayerName = PlayerName;
	NewProfile.Created = FDateTime::Now();
	NewProfile.LastPlayed = FDateTime::Now();

	Profiles.Add(NewProfile);
	OnProfileCreated.Broadcast(ProfileID);

	return ProfileID;
}

bool ULesFightProfileManager::DeleteProfile(FName ProfileID)
{
	for (int32 i = 0; i < Profiles.Num(); i++)
	{
		if (Profiles[i].ProfileID == ProfileID)
		{
			Profiles.RemoveAt(i);
			OnProfileDeleted.Broadcast(ProfileID);

			if (CurrentProfileID == ProfileID)
			{
				CurrentProfile = FPlayerProfileData();
				CurrentProfileID = NAME_None;
				bProfileLoaded = false;
			}

			return true;
		}
	}
	return false;
}

bool ULesFightProfileManager::SelectProfile(FName ProfileID)
{
	for (const FPlayerProfileData& Profile : Profiles)
	{
		if (Profile.ProfileID == ProfileID)
		{
			CurrentProfile = Profile;
			CurrentProfileID = ProfileID;
			bProfileLoaded = true;
			OnProfileSelected.Broadcast(ProfileID);
			return true;
		}
	}
	return false;
}

bool ULesFightProfileManager::RenameProfile(FName ProfileID, FText NewName)
{
	for (FPlayerProfileData& Profile : Profiles)
	{
		if (Profile.ProfileID == ProfileID)
		{
			Profile.PlayerName = NewName;

			if (CurrentProfileID == ProfileID)
			{
				CurrentProfile.PlayerName = NewName;
			}

			OnProfileUpdated.Broadcast(ProfileID);
			return true;
		}
	}
	return false;
}

FPlayerProfileData ULesFightProfileManager::GetProfile(FName ProfileID)
{
	for (const FPlayerProfileData& Profile : Profiles)
	{
		if (Profile.ProfileID == ProfileID)
		{
			return Profile;
		}
	}
	return FPlayerProfileData();
}

FPlayerProfileData ULesFightProfileManager::GetCurrentProfile()
{
	return CurrentProfile;
}

TArray<FPlayerProfileData> ULesFightProfileManager::GetAllProfiles()
{
	return Profiles;
}

int32 ULesFightProfileManager::GetProfileCount()
{
	return Profiles.Num();
}

void ULesFightProfileManager::SetPlayerAvatar(FString AvatarPath)
{
	if (bProfileLoaded)
	{
		CurrentProfile.AvatarPath = AvatarPath;

		for (FPlayerProfileData& Profile : Profiles)
		{
			if (Profile.ProfileID == CurrentProfileID)
			{
				Profile.AvatarPath = AvatarPath;
				break;
			}
		}
	}
}

FString ULesFightProfileManager::GetPlayerAvatar()
{
	return CurrentProfile.AvatarPath;
}

bool ULesFightProfileManager::AddCharacterToProfile(FName CharacterID)
{
	if (!bProfileLoaded)
	{
		return false;
	}

	if (CurrentProfile.SavedCharacterIDs.Contains(CharacterID))
	{
		return false;
	}

	CurrentProfile.SavedCharacterIDs.Add(CharacterID);

	for (FPlayerProfileData& Profile : Profiles)
	{
		if (Profile.ProfileID == CurrentProfileID)
		{
			Profile.SavedCharacterIDs.Add(CharacterID);
			OnProfileUpdated.Broadcast(CurrentProfileID);
			return true;
		}
	}

	return false;
}

bool ULesFightProfileManager::RemoveCharacterFromProfile(FName CharacterID)
{
	if (!bProfileLoaded)
	{
		return false;
	}

	CurrentProfile.SavedCharacterIDs.Remove(CharacterID);

	for (FPlayerProfileData& Profile : Profiles)
	{
		if (Profile.ProfileID == CurrentProfileID)
		{
			Profile.SavedCharacterIDs.Remove(CharacterID);
			OnProfileUpdated.Broadcast(CurrentProfileID);
			return true;
		}
	}

	return false;
}

void ULesFightProfileManager::IncrementPlayCount()
{
	if (bProfileLoaded)
	{
		CurrentProfile.PlayCount++;
	}
}

void ULesFightProfileManager::UpdateLastPlayed()
{
	if (bProfileLoaded)
	{
		CurrentProfile.LastPlayed = FDateTime::Now();
	}
}

bool ULesFightProfileManager::IsProfileLoaded()
{
	return bProfileLoaded;
}

int32 ULesFightProfileManager::GetMaxProfiles()
{
	return MaxProfiles;
}
