#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightSystemCommunicationManager.generated.h"

USTRUCT(BlueprintType)
struct FQueuedMessage
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    ESystemModule Target;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FName Message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    UObject* Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    float Delay;

    FQueuedMessage()
        : Target(ESystemModule::CoreFramework)
        , Data(nullptr)
        , Delay(0.0f)
    {
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSystemEvent, FName, EventName, UObject*, Data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSystemMessage, FName, Message, UObject*, Data);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSystemCommunicationManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void BroadcastEvent(FName EventName, UObject* Data);

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void SubscribeToEvent(FName EventName, FOnSystemEvent Callback);

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void UnsubscribeFromEvent(FName EventName, FOnSystemEvent Callback);

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void SendMessageToSystem(ESystemModule Target, FName Message, UObject* Data);

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void RegisterSystemHandler(ESystemModule Module, FOnSystemMessage Handler);

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    TArray<FSystemEvent> GetEventHistory() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void ClearEventHistory();

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    int32 GetSubscriberCount(FName EventName) const;

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    bool IsEventRegistered(FName EventName) const;

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void SetHistoryEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Integration|Communication")
    void Tick(float DeltaTime);

protected:
    UPROPERTY()
    TMap<FName, FOnSystemEvent> EventSubscriptions;

    UPROPERTY()
    TMap<ESystemModule, FOnSystemMessage> SystemHandlers;

    UPROPERTY()
    TArray<FSystemEvent> EventHistory;

    UPROPERTY()
    TArray<FQueuedMessage> MessageQueue;

    UPROPERTY()
    bool bHistoryEnabled = true;

    UPROPERTY()
    int32 MaxHistory = 100;
};
