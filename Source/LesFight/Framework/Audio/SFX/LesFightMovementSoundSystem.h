#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightMovementSoundSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMovementSoundSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlayFootstep(ETerrainType Surface, FVector Location, float Speed);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlaySlide(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlayDodge(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlayLanding(FVector Location, float Height);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlayJump(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlayRun(FVector Location, float Speed);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void PlayDash(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    void SetMovementIntensity(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "MovementSFX")
    float GetMovementIntensity() const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "MovementSFX")
    float MovementIntensity = 0.5f;

    UPROPERTY(BlueprintReadWrite, Category = "MovementSFX")
    TMap<ETerrainType, FString> FootstepSoundPaths;

    UPROPERTY(BlueprintReadWrite, Category = "MovementSFX")
    TMap<float, FString> SpeedFootstepMap;

    UPROPERTY(BlueprintReadWrite, Category = "MovementSFX")
    float FootstepInterval = 0.5f;

private:
    TWeakObjectPtr<class ULesFightAudioWorldManager> OwnerManager;
};
