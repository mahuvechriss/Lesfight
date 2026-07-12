#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "Blueprint/UserWidget.h"
#include "LesFightWidgetManager.generated.h"

UCLASS(Blueprintable)
class ULesFightWidgetManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateWidget(FName ScreenID, TSubclassOf<UUserWidget> WidgetClass, UWorld* World);

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(FName ScreenID);

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetWidget(FName ScreenID) const;

	UFUNCTION(BlueprintCallable)
	TArray<UUserWidget*> GetAllWidgets() const;

	UFUNCTION(BlueprintCallable)
	void CacheWidget(FName ScreenID, UUserWidget* Widget);

	UFUNCTION(BlueprintCallable)
	void ClearCache();

	UFUNCTION(BlueprintCallable)
	void SetPoolingEnabled(bool bEnabled) { bPoolingEnabled = bEnabled; }

	UFUNCTION(BlueprintCallable)
	bool IsPoolingEnabled() const { return bPoolingEnabled; }

	UFUNCTION(BlueprintCallable)
	int32 GetPoolSize() const { return PoolSize; }

	UFUNCTION(BlueprintCallable)
	void SetPoolSize(int32 Size) { PoolSize = FMath::Max(1, Size); }

protected:
	UPROPERTY()
	TMap<FName, TObjectPtr<UUserWidget>> WidgetCache;

	UPROPERTY()
	TMap<FName, TArray<TObjectPtr<UUserWidget>>> WidgetPool;

	UPROPERTY()
	bool bPoolingEnabled = true;

	UPROPERTY()
	int32 PoolSize = 5;

	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> ActiveWidgets;
};
