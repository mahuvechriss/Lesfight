#include "LesFightCharCreationManager.h"
#include "Core/LesFightCharacterCreator.h"
#include "Core/LesFightCharacterPreset.h"
#include "Core/LesFightCharacterRandomizer.h"
#include "Core/LesFightCharacterPreview.h"
#include "Face/LesFightFaceCustomization.h"
#include "Hair/LesFightHairSystem.h"
#include "Body/LesFightBodyCustomization.h"
#include "Skin/LesFightSkinSystem.h"
#include "Clothing/LesFightClothingSystem.h"
#include "Materials/LesFightMaterialCustomization.h"
#include "Accessories/LesFightAccessorySystem.h"
#include "Voice/LesFightVoiceSelection.h"
#include "Biography/LesFightCharacterBiography.h"
#include "Save/LesFightCharacterSaveSystem.h"
#include "UI/LesFightCustomizationUI.h"
#include "Multiplayer/LesFightCharacterReplication.h"
#include "Performance/LesFightCharCreationPerformance.h"
#include "Testing/LesFightCharCreationDevTools.h"

ULesFightCharCreationManager::ULesFightCharCreationManager()
    : Creator(nullptr)
    , PresetSystem(nullptr)
    , Randomizer(nullptr)
    , Preview(nullptr)
    , FaceSystem(nullptr)
    , HairSystem(nullptr)
    , BodySystem(nullptr)
    , SkinSystem(nullptr)
    , ClothingSystem(nullptr)
    , MaterialSystem(nullptr)
    , AccessorySystem(nullptr)
    , VoiceSystem(nullptr)
    , BiographySystem(nullptr)
    , SaveSystem(nullptr)
    , UISystem(nullptr)
    , ReplicationSystem(nullptr)
    , PerformanceSystem(nullptr)
    , DevTools(nullptr)
    , ActiveCharacterID(NAME_None)
    , bInitialized(false)
{
}

void ULesFightCharCreationManager::Initialize()
{
    if (bInitialized) return;

    Creator = CreateSubsystem(CreatorClass, Creator);
    PresetSystem = CreateSubsystem(PresetClass, PresetSystem);
    Randomizer = CreateSubsystem(RandomizerClass, Randomizer);
    Preview = CreateSubsystem(PreviewClass, Preview);
    FaceSystem = CreateSubsystem(FaceClass, FaceSystem);
    HairSystem = CreateSubsystem(HairClass, HairSystem);
    BodySystem = CreateSubsystem(BodyClass, BodySystem);
    SkinSystem = CreateSubsystem(SkinClass, SkinSystem);
    ClothingSystem = CreateSubsystem(ClothingClass, ClothingSystem);
    MaterialSystem = CreateSubsystem(MaterialClass, MaterialSystem);
    AccessorySystem = CreateSubsystem(AccessoryClass, AccessorySystem);
    VoiceSystem = CreateSubsystem(VoiceClass, VoiceSystem);
    BiographySystem = CreateSubsystem(BioClass, BiographySystem);
    SaveSystem = CreateSubsystem(SaveClass, SaveSystem);
    UISystem = CreateSubsystem(UIClass, UISystem);
    ReplicationSystem = CreateSubsystem(ReplicationClass, ReplicationSystem);
    PerformanceSystem = CreateSubsystem(PerformanceClass, PerformanceSystem);
    DevTools = CreateSubsystem(DevToolsClass, DevTools);

    if (Creator) Creator->Initialize(this);
    if (PresetSystem) PresetSystem->Initialize(this);
    if (Randomizer) Randomizer->Initialize(this);
    if (Preview) Preview->Initialize(this);
    if (FaceSystem) FaceSystem->Initialize(this);
    if (HairSystem) HairSystem->Initialize(this);
    if (BodySystem) BodySystem->Initialize(this);
    if (SkinSystem) SkinSystem->Initialize(this);
    if (ClothingSystem) ClothingSystem->Initialize(this);
    if (MaterialSystem) MaterialSystem->Initialize(this);
    if (AccessorySystem) AccessorySystem->Initialize(this);
    if (VoiceSystem) VoiceSystem->Initialize(this);
    if (BiographySystem) BiographySystem->Initialize(this);
    if (SaveSystem) SaveSystem->Initialize(this);
    if (UISystem) UISystem->Initialize(this);
    if (ReplicationSystem) ReplicationSystem->Initialize(this);
    if (PerformanceSystem) PerformanceSystem->Initialize(this);
    if (DevTools) DevTools->Initialize(this);

    bInitialized = true;
}

void ULesFightCharCreationManager::Shutdown()
{
    if (!bInitialized) return;
    bInitialized = false;
}

void ULesFightCharCreationManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (Preview) Preview->Tick(DeltaTime);
    if (PerformanceSystem) PerformanceSystem->Tick(DeltaTime);
    if (DevTools) DevTools->Tick(DeltaTime);
}

void ULesFightCharCreationManager::SetActiveCharacter(FName CharacterID)
{
    ActiveCharacterID = CharacterID;
    if (Creator) Creator->SetActiveCharacter(CharacterID);
}

FCharacterCustomizationPreset ULesFightCharCreationManager::GetActiveCharacterData() const
{
    return Creator ? Creator->GetActiveCharacterData() : FCharacterCustomizationPreset();
}

bool ULesFightCharCreationManager::SaveActiveCharacter()
{
    if (!Creator || ActiveCharacterID == NAME_None || !SaveSystem) return false;

    FCharacterCustomizationPreset Data = Creator->GetActiveCharacterData();

    if (FaceSystem) Data.FaceMorphs = FaceSystem->GetAllMorphs();
    if (HairSystem) Data.Hair = HairSystem->GetCustomizationData();
    if (BodySystem) Data.BodyMorphs = BodySystem->GetAllBodyMorphs();
    if (SkinSystem) Data.Skin = SkinSystem->GetCustomizationData();
    if (ClothingSystem) Data.Clothing = ClothingSystem->GetAllClothing();
    if (AccessorySystem) Data.Accessories = AccessorySystem->GetAllAccessories();
    if (VoiceSystem) Data.Voice = VoiceSystem->GetData();
    if (BiographySystem) Data.Biography = BiographySystem->GetData();

    Creator->SetCharacterData(ActiveCharacterID, Data);
    return SaveSystem->SaveCharacter(ActiveCharacterID, Data);
}

bool ULesFightCharCreationManager::LoadCharacter(FName CharacterID)
{
    if (!Creator || !SaveSystem) return false;

    FCharacterCustomizationPreset Data;
    if (!SaveSystem->LoadCharacter(CharacterID, Data)) return false;

    Creator->SetCharacterData(CharacterID, Data);
    Creator->SetActiveCharacter(CharacterID);
    ActiveCharacterID = CharacterID;

    if (FaceSystem) FaceSystem->SetAllMorphs(Data.FaceMorphs);
    if (HairSystem) HairSystem->SetCustomizationData(Data.Hair);
    if (BodySystem) BodySystem->SetAllBodyMorphs(Data.BodyMorphs);
    if (SkinSystem) SkinSystem->SetCustomizationData(Data.Skin);
    if (ClothingSystem) ClothingSystem->SetAllFromMap(Data.Clothing);
    if (AccessorySystem) AccessorySystem->SetAllFromMap(Data.Accessories);
    if (VoiceSystem) VoiceSystem->SetData(Data.Voice);
    if (BiographySystem) BiographySystem->SetData(Data.Biography);

    return true;
}

TArray<FName> ULesFightCharCreationManager::GetAllCharacterIDs() const
{
    return Creator ? Creator->GetAllCharacterIDs() : TArray<FName>();
}

void ULesFightCharCreationManager::OpenUI()
{
    if (UISystem) UISystem->OpenScreen(ECustomizationScreen::MainMenu);
}

void ULesFightCharCreationManager::CloseUI()
{
}

bool ULesFightCharCreationManager::IsUIOpen() const
{
    return false;
}

template<typename T>
T* ULesFightCharCreationManager::CreateSubsystem(TSubclassOf<T> Class, T*& OutPtr)
{
    if (!Class)
    {
        Class = T::StaticClass();
    }
    OutPtr = NewObject<T>(this, Class);
    return OutPtr;
}
