#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightCharacterOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharacterOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void OptimizeCharacterMeshes();

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void SetLODBias(int32 Bias);

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	int32 GetLODBias() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void SetSkeletonOptimization(bool bOptimize);

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void EnableCullDistance(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void SetCullDistance(float Distance);

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	void OptimizeMaterials(bool bUseInstancedMaterials);

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	int32 GetMeshTriangleCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	int32 GetActiveCharacterCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Character")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Performance|Character")
	int32 LODBias = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Performance|Character")
	float CullDistance = 5000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Character")
	bool bSkeletonOptimized = false;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Character")
	bool bCullingEnabled = false;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Character")
	bool bInstancedMaterials = false;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Character")
	int32 MaxActiveCharacters = 2;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Character")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};
