#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightEventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGenericEvent, const FString&, EventName, UObject*, EventData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchEvent, const FString&, MatchEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIAction, const FString&, ActionName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerAction, int32, PlayerIndex, const FString&, Action);

USTRUCT(BlueprintType)
struct FEventPayload
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EventType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UObject> DataObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 IntValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FloatValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StringValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector VectorValue;

    FEventPayload()
        : EventType(TEXT(""))
        , DataObject(nullptr)
        , IntValue(0)
        , FloatValue(0.0f)
        , StringValue(TEXT(""))
        , VectorValue(FVector::ZeroVector)
    {}
};

UCLASS(Blueprintable)
class ULesFightEventManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightEventManager();

    UFUNCTION(BlueprintCallable, Category = "Events")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Events")
    void BroadcastEvent(const FString& EventName, UObject* EventData = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void BroadcastEventWithPayload(const FEventPayload& Payload);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void BroadcastMatchEvent(const FString& MatchEvent);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void BroadcastUIAction(const FString& ActionName);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void BroadcastPlayerAction(int32 PlayerIndex, const FString& Action);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void AddEventListener(UObject* Listener, const FString& EventName);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void RemoveEventListener(UObject* Listener, const FString& EventName);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void ClearAllListeners();

    UFUNCTION(BlueprintCallable, Category = "Events")
    void EnableEventLogging(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void FlushPendingEvents();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGenericEvent OnGenericEvent;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchEvent OnMatchEvent;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnUIAction OnUIAction;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerAction OnPlayerAction;

private:
    UPROPERTY()
    TMap<FString, TArray<TObjectPtr<UObject>>> EventListeners;

    UPROPERTY()
    TArray<FEventPayload> PendingEvents;

    bool bEventLoggingEnabled;

    void ProcessEvent(const FString& EventName, UObject* EventData);
};
