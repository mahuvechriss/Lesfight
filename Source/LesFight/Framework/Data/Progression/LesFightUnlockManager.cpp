#include "Framework/Data/Progression/LesFightUnlockManager.h"

void ULesFightUnlockManager::Initialize()
{
	UnlockedItems.Empty();
	UnlockableRegistry.Empty();

	auto Register = [&](FName ItemID, EUnlockType Type, FText DisplayName, FText Description, FName RequiredAchievement, int32 RequiredLevel)
	{
		RegisterUnlockable(ItemID, Type, DisplayName, Description, RequiredAchievement, RequiredLevel);
	};

	Register(FName("Fighter_Karate"), EUnlockType::Fighter, FText::FromString("Karate Fighter"), FText::FromString("A disciplined karate practitioner"), FName(), 1);
	Register(FName("Fighter_KungFu"), EUnlockType::Fighter, FText::FromString("Kung Fu Fighter"), FText::FromString("A graceful kung fu master"), FName(), 1);
	Register(FName("Fighter_Boxing"), EUnlockType::Fighter, FText::FromString("Boxing Fighter"), FText::FromString("A powerful boxer"), FName(), 1);
	Register(FName("Fighter_MuayThai"), EUnlockType::Fighter, FText::FromString("Muay Thai Fighter"), FText::FromString("A fierce Muay Thai warrior"), FName(), 3);
	Register(FName("Fighter_JiuJitsu"), EUnlockType::Fighter, FText::FromString("Jiu Jitsu Fighter"), FText::FromString("A grappling Jiu Jitsu expert"), FName(), 3);
	Register(FName("Fighter_Capoeira"), EUnlockType::Fighter, FText::FromString("Capoeira Fighter"), FText::FromString("An acrobatic Capoeira dancer"), FName(), 5);
	Register(FName("Fighter_Taekwondo"), EUnlockType::Fighter, FText::FromString("Taekwondo Fighter"), FText::FromString("A swift Taekwondo kicker"), FName(), 5);
	Register(FName("Fighter_Wrestling"), EUnlockType::Fighter, FText::FromString("Wrestling Fighter"), FText::FromString("A dominant wrestler"), FName(), 7);
	Register(FName("Fighter_Fencing"), EUnlockType::Fighter, FText::FromString("Fencing Fighter"), FText::FromString("A precise fencer"), FName(), 10);
	Register(FName("Fighter_KravMaga"), EUnlockType::Fighter, FText::FromString("Krav Maga Fighter"), FText::FromString("A brutal Krav Maga specialist"), FName(), 10);
	Register(FName("Fighter_Shadow"), EUnlockType::Fighter, FText::FromString("Shadow Fighter"), FText::FromString("A mysterious shadow warrior"), FName(), 15);
	Register(FName("Fighter_Champion"), EUnlockType::Fighter, FText::FromString("Champion"), FText::FromString("The ultimate champion"), FName("ReachLevel50"), 50);

	Register(FName("Clothing_Street"), EUnlockType::Clothing, FText::FromString("Street Wear"), FText::FromString("Casual street clothing"), FName(), 1);
	Register(FName("Clothing_Classic"), EUnlockType::Clothing, FText::FromString("Classic Gi"), FText::FromString("Traditional martial arts gi"), FName(), 2);
	Register(FName("Clothing_Armored"), EUnlockType::Clothing, FText::FromString("Armored Gear"), FText::FromString("Light combat armor"), FName(), 8);

	Register(FName("Arena_Dojo"), EUnlockType::Arena, FText::FromString("Ancient Dojo"), FText::FromString("A traditional Japanese dojo"), FName(), 1);
	Register(FName("Arena_Ring"), EUnlockType::Arena, FText::FromString("Boxing Ring"), FText::FromString("A professional boxing ring"), FName(), 1);
	Register(FName("Arena_Street"), EUnlockType::Arena, FText::FromString("Urban Street"), FText::FromString("A neon-lit city street"), FName(), 3);
	Register(FName("Arena_Colosseum"), EUnlockType::Arena, FText::FromString("Colosseum"), FText::FromString("An ancient Roman colosseum"), FName(), 10);
	Register(FName("Arena_Volcano"), EUnlockType::Arena, FText::FromString("Volcano Arena"), FText::FromString("A fiery volcano summit"), FName(), 20);

	Register(FName("Music_Theme1"), EUnlockType::Music, FText::FromString("Main Theme"), FText::FromString("The main theme of Les Fight"), FName(), 1);
	Register(FName("Music_Theme2"), EUnlockType::Music, FText::FromString("Battle Hymn"), FText::FromString("An intense battle track"), FName(), 2);
	Register(FName("Music_Theme3"), EUnlockType::Music, FText::FromString("Night City"), FText::FromString("A moody night city track"), FName(), 5);
	Register(FName("Music_Theme4"), EUnlockType::Music, FText::FromString("Epic Finale"), FText::FromString("A grand finale theme"), FName(), 15);
	Register(FName("Music_Theme5"), EUnlockType::Music, FText::FromString("Champion Anthem"), FText::FromString("A victory anthem"), FName(), 25);

	Register(FName("Tech_DragonPunch"), EUnlockType::SpecialTechnique, FText::FromString("Dragon Punch"), FText::FromString("A powerful rising uppercut"), FName(), 5);
	Register(FName("Tech_SpinningKick"), EUnlockType::SpecialTechnique, FText::FromString("Spinning Kick"), FText::FromString("A devastating spinning roundhouse"), FName(), 10);
	Register(FName("Tech_ShadowStep"), EUnlockType::SpecialTechnique, FText::FromString("Shadow Step"), FText::FromString("A teleporting dodge maneuver"), FName(), 20);

	Register(FName("Creator_Hairstyle1"), EUnlockType::CharacterCreatorOption, FText::FromString("Spiky Hair"), FText::FromString("A spiky hairstyle option"), FName(), 1);
	Register(FName("Creator_Hairstyle2"), EUnlockType::CharacterCreatorOption, FText::FromString("Long Hair"), FText::FromString("A long flowing hairstyle"), FName(), 3);
	Register(FName("Creator_Tattoo"), EUnlockType::CharacterCreatorOption, FText::FromString("Body Tattoos"), FText::FromString("Tribal tattoo patterns"), FName(), 8);
	Register(FName("Creator_Scar"), EUnlockType::CharacterCreatorOption, FText::FromString("Facial Scars"), FText::FromString("Battle scar options"), FName(), 15);

	Register(FName("Palette_Red"), EUnlockType::ColorPalette, FText::FromString("Crimson"), FText::FromString("A red color palette"), FName(), 1);
	Register(FName("Palette_Blue"), EUnlockType::ColorPalette, FText::FromString("Ocean"), FText::FromString("A blue color palette"), FName(), 1);
	Register(FName("Palette_Green"), EUnlockType::ColorPalette, FText::FromString("Forest"), FText::FromString("A green color palette"), FName(), 2);
	Register(FName("Palette_Gold"), EUnlockType::ColorPalette, FText::FromString("Royal Gold"), FText::FromString("A gold color palette"), FName(), 10);
	Register(FName("Palette_Purple"), EUnlockType::ColorPalette, FText::FromString("Shadow"), FText::FromString("A purple color palette"), FName(), 15);
	Register(FName("Palette_Black"), EUnlockType::ColorPalette, FText::FromString("Midnight"), FText::FromString("A black color palette"), FName(), 25);
}

void ULesFightUnlockManager::Shutdown()
{
}

bool ULesFightUnlockManager::UnlockItem(FName ItemID, EUnlockType Type)
{
	if (IsItemUnlocked(ItemID))
	{
		return false;
	}

	UnlockedItems.Add(ItemID);

	if (FUnlockableInfo* Info = UnlockableRegistry.Find(ItemID))
	{
		Info->bIsUnlocked = true;
	}

	OnItemUnlocked.Broadcast(ItemID, Type);
	return true;
}

bool ULesFightUnlockManager::IsItemUnlocked(FName ItemID) const
{
	return UnlockedItems.Contains(ItemID);
}

TArray<FName> ULesFightUnlockManager::GetUnlockedItems(EUnlockType Type) const
{
	TArray<FName> Result;
	for (const FName& ItemID : UnlockedItems)
	{
		if (const FUnlockableInfo* Info = UnlockableRegistry.Find(ItemID))
		{
			if (Info->Type == Type)
			{
				Result.Add(ItemID);
			}
		}
	}
	return Result;
}

TArray<FName> ULesFightUnlockManager::GetAllUnlockedItems() const
{
	return UnlockedItems;
}

bool ULesFightUnlockManager::LockItem(FName ItemID)
{
	if (!IsItemUnlocked(ItemID))
	{
		return false;
	}

	UnlockedItems.Remove(ItemID);

	if (FUnlockableInfo* Info = UnlockableRegistry.Find(ItemID))
	{
		Info->bIsUnlocked = false;
	}

	return true;
}

void ULesFightUnlockManager::RegisterUnlockable(FName ItemID, EUnlockType Type, FText DisplayName, FText Description, FName RequiredAchievement, int32 RequiredLevel)
{
	FUnlockableInfo Info;
	Info.ItemID = ItemID;
	Info.Type = Type;
	Info.DisplayName = DisplayName;
	Info.Description = Description;
	Info.RequiredAchievement = RequiredAchievement;
	Info.RequiredLevel = RequiredLevel;
	Info.bIsUnlocked = false;

	UnlockableRegistry.Add(ItemID, Info);
}

FUnlockableInfo ULesFightUnlockManager::GetUnlockableInfo(FName ItemID) const
{
	if (const FUnlockableInfo* Info = UnlockableRegistry.Find(ItemID))
	{
		return *Info;
	}
	return FUnlockableInfo();
}

TArray<FUnlockableInfo> ULesFightUnlockManager::GetAvailableUnlockables(EUnlockType Type) const
{
	TArray<FUnlockableInfo> Result;
	for (const auto& Pair : UnlockableRegistry)
	{
		if (Pair.Value.Type == Type && IsItemUnlocked(Pair.Key))
		{
			Result.Add(Pair.Value);
		}
	}
	return Result;
}

TArray<FUnlockableInfo> ULesFightUnlockManager::GetLockedUnlockables(EUnlockType Type) const
{
	TArray<FUnlockableInfo> Result;
	for (const auto& Pair : UnlockableRegistry)
	{
		if (Pair.Value.Type == Type && !IsItemUnlocked(Pair.Key))
		{
			Result.Add(Pair.Value);
		}
	}
	return Result;
}

TArray<FName> ULesFightUnlockManager::CheckAndUnlockByLevel(int32 NewLevel)
{
	TArray<FName> NewlyUnlocked;
	for (auto& Pair : UnlockableRegistry)
	{
		if (!Pair.Value.bIsUnlocked && Pair.Value.RequiredLevel <= NewLevel && Pair.Value.RequiredLevel > 0)
		{
			if (UnlockItem(Pair.Key, Pair.Value.Type))
			{
				NewlyUnlocked.Add(Pair.Key);
			}
		}
	}
	return NewlyUnlocked;
}

TArray<FName> ULesFightUnlockManager::CheckAndUnlockByAchievement(FName AchievementID)
{
	TArray<FName> NewlyUnlocked;
	for (auto& Pair : UnlockableRegistry)
	{
		if (!Pair.Value.bIsUnlocked && Pair.Value.RequiredAchievement == AchievementID)
		{
			if (UnlockItem(Pair.Key, Pair.Value.Type))
			{
				NewlyUnlocked.Add(Pair.Key);
			}
		}
	}
	return NewlyUnlocked;
}

int32 ULesFightUnlockManager::GetTotalUnlocked() const
{
	return UnlockedItems.Num();
}

int32 ULesFightUnlockManager::GetTotalUnlockables() const
{
	return UnlockableRegistry.Num();
}

void ULesFightUnlockManager::ResetAllUnlocks()
{
	UnlockedItems.Empty();
	for (auto& Pair : UnlockableRegistry)
	{
		Pair.Value.bIsUnlocked = false;
	}
}
