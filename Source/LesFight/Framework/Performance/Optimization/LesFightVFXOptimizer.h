#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightVFXOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightVFXOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void SetMaxParticleCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	int32 GetMaxParticleCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void SetMaxNiagaraSystems(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	int32 GetMaxNiagaraSystems() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void EnableScreenEffects(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void EnableDistanceCulling(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void SetCullDistance(float Distance);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void SetDecalLimit(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	int32 GetDecalLimit() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	void OptimizeNiagaraEffects();

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	int32 GetActiveVFXCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	float GetVFXMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|VFX")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	int32 MaxParticleCount = 10000;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	int32 MaxNiagaraSystemCount = 50;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	int32 DecalLimit = 100;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	float CullDistance = 5000.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	bool bScreenEffects = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	bool bDistanceCulling = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|VFX")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};
