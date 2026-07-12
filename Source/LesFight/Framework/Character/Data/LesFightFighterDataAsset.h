#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LesFightCharacterData.h"
#include "LesFightFighterDataAsset.generated.h"

UCLASS(BlueprintType)
class ULesFightFighterDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    FCharacterTableRow FighterData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    TSubclassOf<class ALesFightBaseFighter> FighterClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    TArray<FName> Tags;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(TEXT("FighterData"), FighterData.Identity.CharacterID);
    }
};
