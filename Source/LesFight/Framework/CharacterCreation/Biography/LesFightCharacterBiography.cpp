#include "LesFightCharacterBiography.h"
#include "LesFightCharCreationManager.h"

ULesFightCharacterBiography::ULesFightCharacterBiography()
    : MaxNameLength(32)
    , MaxBackstoryLength(500)
    , MinAge(16)
    , MaxAge(99)
{
    CurrentBio.CharacterName = TEXT("New Fighter");
    CurrentBio.Age = 25;
    CurrentBio.Weight = 70.0f;

    AvailableCountries = {
        TEXT("Japan"), TEXT("China"), TEXT("Korea"), TEXT("Thailand"),
        TEXT("Brazil"), TEXT("USA"), TEXT("France"), TEXT("Russia"),
        TEXT("UK"), TEXT("Germany"), TEXT("Italy"), TEXT("Spain")
    };
}

void ULesFightCharacterBiography::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightCharacterBiography::SetCharacterName(const FString& Name)
{
    CurrentBio.CharacterName = Name.Left(MaxNameLength);
}

FString ULesFightCharacterBiography::GetCharacterName() const
{
    return CurrentBio.CharacterName;
}

void ULesFightCharacterBiography::SetNickname(const FString& Nickname)
{
    CurrentBio.Nickname = Nickname.Left(MaxNameLength);
}

FString ULesFightCharacterBiography::GetNickname() const
{
    return CurrentBio.Nickname;
}

void ULesFightCharacterBiography::SetAge(int32 Age)
{
    CurrentBio.Age = FMath::Clamp(Age, MinAge, MaxAge);
}

int32 ULesFightCharacterBiography::GetAge() const
{
    return CurrentBio.Age;
}

void ULesFightCharacterBiography::SetCountry(const FString& Country)
{
    if (AvailableCountries.Contains(Country) || Country.IsEmpty())
    {
        CurrentBio.Country = Country;
    }
}

FString ULesFightCharacterBiography::GetCountry() const
{
    return CurrentBio.Country;
}

void ULesFightCharacterBiography::SetBackstory(const FString& Backstory)
{
    CurrentBio.Backstory = Backstory.Left(MaxBackstoryLength);
}

FString ULesFightCharacterBiography::GetBackstory() const
{
    return CurrentBio.Backstory;
}

void ULesFightCharacterBiography::SetWeight(float Weight)
{
    CurrentBio.Weight = FMath::Clamp(Weight, 30.0f, 300.0f);
}

float ULesFightCharacterBiography::GetWeight() const
{
    return CurrentBio.Weight;
}

void ULesFightCharacterBiography::SetData(const FCharacterBiographyData& Data)
{
    CurrentBio = Data;
    SetCharacterName(Data.CharacterName);
    SetAge(Data.Age);
    SetWeight(Data.Weight);
}

FCharacterBiographyData ULesFightCharacterBiography::GetData() const
{
    return CurrentBio;
}

void ULesFightCharacterBiography::ResetToDefault()
{
    CurrentBio.CharacterName = TEXT("New Fighter");
    CurrentBio.Nickname.Empty();
    CurrentBio.Age = 25;
    CurrentBio.Country.Empty();
    CurrentBio.Backstory.Empty();
    CurrentBio.Weight = 70.0f;
}
