#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightPerformanceManager.generated.h"

class ULesFightFPSMonitor;
class ULesFightMemoryTracker;
class ULesFightPerformanceMonitor;
class ULesFightGraphicsQualityManager;
class ULesFightTextureOptimizer;
class ULesFightScalabilitySettings;
class ULesFightHardwareDetector;
class ULesFightCharacterOptimizer;
class ULesFightAnimationOptimizer;
class ULesFightVFXOptimizer;
class ULesFightAudioOptimizer;
class ULesFightAIOptimizer;
class ULesFightPhysicsOptimizer;
class ULesFightLoadingOptimizer;
class ULesFightMultiplayerOptimizer;
class ULesFightPerformanceDevTools;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQualityChanged, EPerformanceQualityLevel, NewQuality);

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightPerformanceManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightFPSMonitor* GetFPSMonitor() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightMemoryTracker* GetMemoryTracker() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightPerformanceMonitor* GetPerformanceMonitor() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightGraphicsQualityManager* GetGraphicsQualityManager() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightTextureOptimizer* GetTextureOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightScalabilitySettings* GetScalabilitySettings() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightHardwareDetector* GetHardwareDetector() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightCharacterOptimizer* GetCharacterOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightAnimationOptimizer* GetAnimationOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightVFXOptimizer* GetVFXOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightAudioOptimizer* GetAudioOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightAIOptimizer* GetAIOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightPhysicsOptimizer* GetPhysicsOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightLoadingOptimizer* GetLoadingOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightMultiplayerOptimizer* GetMultiplayerOptimizer() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	ULesFightPerformanceDevTools* GetPerformanceDevTools() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	EPerformanceQualityLevel GetQualityLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	FOptimizationMetrics GetOptimizationMetrics() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	void ApplyOptimizations();

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	TArray<FString> RunFullDiagnostic();

	UFUNCTION(BlueprintCallable, Category = "Performance|Manager")
	bool IsOptimized() const;

	UPROPERTY(BlueprintAssignable, Category = "Performance|Manager")
	FOnQualityChanged OnQualityChanged;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightFPSMonitor* FPSMonitor = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightMemoryTracker* MemoryTracker = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightPerformanceMonitor* PerformanceMonitor = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightGraphicsQualityManager* GraphicsQualityManager = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightTextureOptimizer* TextureOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightScalabilitySettings* ScalabilitySettings = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightHardwareDetector* HardwareDetector = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightCharacterOptimizer* CharacterOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightAnimationOptimizer* AnimationOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightVFXOptimizer* VFXOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightAudioOptimizer* AudioOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightAIOptimizer* AIOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightPhysicsOptimizer* PhysicsOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightLoadingOptimizer* LoadingOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightMultiplayerOptimizer* MultiplayerOptimizer = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	ULesFightPerformanceDevTools* PerformanceDevTools = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	bool bInitialized = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	bool bOptimized = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Manager")
	EPerformanceQualityLevel CurrentQuality = EPerformanceQualityLevel::High;

private:
	template<typename T>
	T* CreateSubsystem();
};
