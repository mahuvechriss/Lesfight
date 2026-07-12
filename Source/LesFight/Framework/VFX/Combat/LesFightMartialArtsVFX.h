#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "Framework/MartialArts/Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsVFX.generated.h"

class ULesFightVFXWorldManager;

UCLASS(Blueprintable)
class ULesFightMartialArtsVFX : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsVFX();

    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void SetStyle(EFightingStyle Style);

    UFUNCTION(BlueprintCallable)
    EFightingStyle GetStyle() const;

    UFUNCTION(BlueprintCallable)
    void PlayStyleImpact(EFightingStyle Style, EImpactVFXType Type, FVector Location);

    UFUNCTION(BlueprintCallable)
    void PlayStyleMotionTrail(EFightingStyle Style, EMotionVFXType Trail, FTransform Transform);

    UFUNCTION(BlueprintCallable)
    FLinearColor GetStyleAuraDef(EFightingStyle Style) const;

    UFUNCTION(BlueprintCallable)
    void SetVFXStyleMode(EVFXStyleMode Mode);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EFightingStyle CurrentStyle = EFightingStyle::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EVFXStyleMode StyleMode = EVFXStyleMode::Realistic;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<EFightingStyle, FLinearColor> StyleColors;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<EFightingStyle, TMap<EImpactVFXType, FString>> StyleImpactOverrides;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;
};
