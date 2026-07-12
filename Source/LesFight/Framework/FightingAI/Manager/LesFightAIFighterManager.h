#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIFighterManager.generated.h"

class ALesFightAIFighterController;
class ULesFightAIAnimationHandler;
class ULesFightAIAudioHandler;
class ULesFightAIPerformance;
class ULesFightAIDevTools;

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightAIFighterManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void RegisterAIController(ALesFightAIFighterController* Controller);

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void UnregisterAIController(ALesFightAIFighterController* Controller);

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    TArray<ALesFightAIFighterController*> GetActiveControllers() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void SetGlobalDifficulty(EAIDifficulty Difficulty);

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    EAIDifficulty GetGlobalDifficulty() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void SetGlobalPersonality(EAIPersonalityType Personality);

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    void EnableAllAI(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    int32 GetAICount() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    ULesFightAIAnimationHandler* GetAnimationHandler() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    ULesFightAIAudioHandler* GetAudioHandler() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    ULesFightAIPerformance* GetPerformance() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Manager")
    ULesFightAIDevTools* GetDevTools() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Manager")
    TArray<ALesFightAIFighterController*> ActiveControllers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Manager")
    EAIDifficulty GlobalDifficulty = EAIDifficulty::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Manager")
    EAIPersonalityType GlobalPersonality = EAIPersonalityType::Warrior;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Manager")
    bool bAllAIEnabled = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Manager")
    bool bInitialized = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Manager")
    ULesFightAIAnimationHandler* AnimationHandler;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Manager")
    ULesFightAIAudioHandler* AudioHandler;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Manager")
    ULesFightAIPerformance* Performance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Manager")
    ULesFightAIDevTools* DevTools;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Manager|Config")
    TSubclassOf<ULesFightAIAnimationHandler> AnimationHandlerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Manager|Config")
    TSubclassOf<ULesFightAIAudioHandler> AudioHandlerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Manager|Config")
    TSubclassOf<ULesFightAIPerformance> PerformanceClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Manager|Config")
    TSubclassOf<ULesFightAIDevTools> DevToolsClass;

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Subclass);
};
