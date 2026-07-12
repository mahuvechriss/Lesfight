#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "LesFightCharacterCreationData.generated.h"

UENUM(BlueprintType)
enum class EFaceMorphType : uint8
{
    FaceShape, Jaw, Chin, Cheekbones, Forehead,
    NoseWidth, NoseHeight, NoseBridge,
    Lips, MouthWidth,
    EyeShape, EyeSize,
    Eyebrows, Eyelashes, Ears,
    FacialHair, Wrinkles, Freckles, Scars, BeautyMarks,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHairStyle : uint8
{
    Bald, Short, Long, Braided, Curly, Straight, Afro, Ponytail, Bun,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EBodyMorphType : uint8
{
    Height, Weight, BodyFat, MuscleDefinition,
    ShoulderWidth, ChestSize, WaistSize, HipWidth,
    ArmLength, ArmThickness, LegLength, LegThickness,
    NeckSize, HandSize, FootSize,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EClothingSlot : uint8
{
    Headwear, Mask, Glasses, NeckAccessory,
    UpperBody, Gloves, Belt,
    LowerBody, Shoes, BackAccessory,
    WristAccessory, LegAccessory,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMaterialProperty : uint8
{
    Color, Metallic, Roughness,
    FabricType, Pattern,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFabricType : uint8
{
    Cotton, Leather, Silk, CarbonFiber, Denim, Wool, Polyester,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAccessorySlot : uint8
{
    Earring, Necklace, Bracelet, Ring, Watch, Headband, Cape, Decorative,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ESkinDetail : uint8
{
    Smooth, Slight, Moderate, Rough, Aged,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EVoicePack : uint8
{
    Male1, Male2, Male3, Female1, Female2, Female3,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECharacterCreatorMode : uint8
{
    Create, Edit, Duplicate, Preview,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EPreviewBackground : uint8
{
    Default, Dojo, Arena, Outdoor, Studio,
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FFaceMorphData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFaceMorphType MorphType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MorphTargetName;

    FFaceMorphData()
        : MorphType(EFaceMorphType::FaceShape)
        , Value(0.5f), MinValue(0.0f), MaxValue(1.0f)
        , MorphTargetName(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FHairCustomizationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EHairStyle Style;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor HairColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Length;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Shine;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TextureVariation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPhysicsEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName HairMeshID;

    FHairCustomizationData()
        : Style(EHairStyle::Short)
        , HairColor(FLinearColor::Black)
        , Length(0.5f), Shine(0.3f), TextureVariation(0.5f)
        , bPhysicsEnabled(true)
        , HairMeshID(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FBodyMorphData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBodyMorphType MorphType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MorphTargetName;

    FBodyMorphData()
        : MorphType(EBodyMorphType::Height)
        , Value(0.5f), MinValue(0.0f), MaxValue(1.0f)
        , MorphTargetName(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FSkinCustomizationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SkinTone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESkinDetail SkinDetail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Glossiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ScarIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> TattooIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> BodyPaintIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SkinTextureID;

    FSkinCustomizationData()
        : SkinTone(FLinearColor(1.0f, 0.8f, 0.6f))
        , SkinDetail(ESkinDetail::Smooth)
        , Glossiness(0.3f)
        , SkinTextureID(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FClothingItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EClothingSlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MeshID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor PrimaryColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SecondaryColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Metallic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Roughness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFabricType FabricType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PatternID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEquipped;

    FClothingItemData()
        : Slot(EClothingSlot::UpperBody)
        , ItemID(NAME_None), MeshID(NAME_None)
        , PrimaryColor(FLinearColor::White)
        , SecondaryColor(FLinearColor::White)
        , Metallic(0.0f), Roughness(0.5f)
        , FabricType(EFabricType::Cotton)
        , PatternID(NAME_None), bEquipped(false)
    {}
};

USTRUCT(BlueprintType)
struct FAccessoryData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAccessorySlot Slot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AccessoryID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MeshID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Metallic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEquipped;

    FAccessoryData()
        : Slot(EAccessorySlot::Earring)
        , AccessoryID(NAME_None), MeshID(NAME_None)
        , Color(FLinearColor::White)
        , Metallic(0.5f), bEquipped(false)
    {}
};

USTRUCT(BlueprintType)
struct FVoiceSelectionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVoicePack VoicePack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Pitch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Tone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName VictoryVoiceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TauntVoiceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PainVoiceID;

    FVoiceSelectionData()
        : VoicePack(EVoicePack::Male1)
        , Pitch(1.0f), Tone(1.0f)
        , VictoryVoiceID(NAME_None)
        , TauntVoiceID(NAME_None)
        , PainVoiceID(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterBiographyData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Nickname;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Country;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Age;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Biography;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PreferredArena;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime CreatedDate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime LastModifiedDate;

    FCharacterBiographyData()
        : CharacterName(TEXT("New Fighter"))
        , Nickname(TEXT("")), Country(TEXT(""))
        , Age(25)
        , PreferredArena(TEXT("Default"))
        , CreatedDate(FDateTime::Now())
        , LastModifiedDate(FDateTime::Now())
    {}
};

USTRUCT(BlueprintType)
struct FCharacterCustomizationPreset
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PresetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCharacterBiographyData Biography;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EFaceMorphType, float> FaceMorphs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FHairCustomizationData Hair;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EBodyMorphType, float> BodyMorphs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSkinCustomizationData Skin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EClothingSlot, FClothingItemData> Clothing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EAccessorySlot, FAccessoryData> Accessories;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVoiceSelectionData Voice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFightingStyle AssignedStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PortraitIconID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ThumbnailPath;

    FCharacterCustomizationPreset()
        : PresetName(TEXT("Default"))
        , AssignedStyle(EFightingStyle::Karate)
        , PortraitIconID(NAME_None)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterSaveSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCharacterCustomizationPreset CharacterData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsValid;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SaveVersion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime SaveTimestamp;

    FCharacterSaveSlot()
        : SlotIndex(-1)
        , bIsValid(false)
        , SaveVersion(1)
        , SaveTimestamp(FDateTime::MinValue())
    {}
};

USTRUCT(BlueprintType)
struct FValidationResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bIsValid;

    UPROPERTY(BlueprintReadOnly)
    TArray<FString> Errors;

    UPROPERTY(BlueprintReadOnly)
    TArray<FString> Warnings;

    FValidationResult()
        : bIsValid(true)
    {}
};

UCLASS(BlueprintType)
class ULesFightCharacterCreationDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face")
    TMap<EFaceMorphType, float> FaceMorphRanges;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")
    TMap<EBodyMorphType, float> BodyMorphRanges;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hair")
    TMap<EHairStyle, FName> HairStyleMeshes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
    TArray<FLinearColor> SkinTonePalette;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clothing")
    TMap<EClothingSlot, TArray<FName>> AvailableClothing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessories")
    TMap<EAccessorySlot, TArray<FName>> AvailableAccessories;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice")
    TArray<EVoicePack> AvailableVoicePacks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors")
    TArray<FLinearColor> HairColorPalette;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors")
    TArray<FLinearColor> EyeColorPalette;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors")
    TArray<FLinearColor> ClothingColorPalette;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
    int32 MaxCharacterSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
    int32 CurrentSaveVersion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    int32 MaxMorphTargets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    int32 MaxClothingItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    int32 MaxAccessories;

    ULesFightCharacterCreationDataAsset()
        : MaxCharacterSlots(50)
        , CurrentSaveVersion(1)
        , MaxMorphTargets(64)
        , MaxClothingItems(12)
        , MaxAccessories(8)
    {
        SkinTonePalette = {
            FLinearColor(1.0f, 0.8f, 0.6f),
            FLinearColor(0.9f, 0.7f, 0.5f),
            FLinearColor(0.8f, 0.6f, 0.4f),
            FLinearColor(0.6f, 0.4f, 0.3f),
            FLinearColor(0.4f, 0.3f, 0.2f)
        };

        HairColorPalette = {
            FLinearColor::Black,
            FLinearColor(0.3f, 0.2f, 0.1f),
            FLinearColor(0.6f, 0.4f, 0.2f),
            FLinearColor(0.9f, 0.7f, 0.3f),
            FLinearColor(0.8f, 0.1f, 0.1f),
            FLinearColor::White
        };
    }
};
