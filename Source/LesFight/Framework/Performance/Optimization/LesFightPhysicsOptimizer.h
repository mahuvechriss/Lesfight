#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightPhysicsOptimizer.generated.h"

UENUM(BlueprintType)
enum class ECollisionComplexity : uint8
{
	Full		UMETA(DisplayName = "Full"),
	Reduced		UMETA(DisplayName = "Reduced"),
	Simplified	UMETA(DisplayName = "Simplified"),
	Disabled	UMETA(DisplayName = "Disabled")
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPhysicsOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void EnableClothPhysics(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void EnableHairPhysics(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void SetPhysicsSubstepCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	int32 GetPhysicsSubstepCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void SetMaxDestructibleObjects(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	int32 GetMaxDestructibleObjects() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void EnableAsyncPhysics(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	void SetCollisionComplexity(ECollisionComplexity Complexity);

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	int32 GetActivePhysicsBodies() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Physics")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	bool bClothEnabled = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	bool bHairEnabled = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	bool bAsyncPhysics = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	int32 PhysicsSubsteps = 2;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	int32 MaxDestructibles = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	ECollisionComplexity CollisionComplexity = ECollisionComplexity::Reduced;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Physics")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};
