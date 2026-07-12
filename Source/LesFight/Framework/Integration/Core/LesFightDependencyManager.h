#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightDependencyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModuleReady, ESystemModule, Module);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightDependencyManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    void RegisterModule(ESystemModule Module, const TArray<ESystemModule>& Dependencies);

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    TArray<ESystemModule> ResolveInitOrder();

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    bool IsModuleReady(ESystemModule Module) const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    void SetModuleReady(ESystemModule Module);

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    TArray<ESystemModule> GetUnresolvedDependencies(ESystemModule Module) const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    bool ValidateDependencyGraph();

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    float GetInitProgress() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    FSystemModuleInfo GetModuleInfo(ESystemModule Module) const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    TArray<FString> GetModuleStatus() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DependencyManager")
    void ResetAllModules();

    UPROPERTY(BlueprintAssignable, Category = "Integration|DependencyManager")
    FOnModuleReady OnModuleReady;

protected:
    UPROPERTY()
    TMap<ESystemModule, FSystemModuleInfo> ModuleRegistry;

    UPROPERTY()
    TSet<ESystemModule> ReadyModules;

    UPROPERTY()
    TArray<ESystemModule> InitOrder;
};
