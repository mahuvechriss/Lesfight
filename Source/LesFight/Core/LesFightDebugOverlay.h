#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightDebugOverlay.generated.h"

USTRUCT(BlueprintType)
struct FDebugDisplayInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FrameRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FrameTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TriangleCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DrawCalls;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GameTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NetworkStatus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PacketLoss;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Ping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GameState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ActiveModules;

    FDebugDisplayInfo()
        : FrameRate(0.0f)
        , FrameTime(0.0f)
        , TriangleCount(0)
        , DrawCalls(0)
        , GameTime(0.0f)
        , NetworkStatus(TEXT("Offline"))
        , PacketLoss(0)
        , Ping(0)
        , GameState(TEXT("Menu"))
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebugInfoUpdated, const FDebugDisplayInfo&, DebugInfo);

UCLASS()
class ULesFightDebugOverlay : public UUserWidget
{
    GENERATED_BODY()

public:
    ULesFightDebugOverlay();

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Debug")
    void ToggleDebugOverlay();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Debug")
    void ShowDebugOverlay();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Debug")
    void HideDebugOverlay();

    UFUNCTION(BlueprintPure, Category = "LesFight|Debug")
    bool IsDebugVisible() const { return bIsVisible; }

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|Debug")
    void OnDebugDisplayUpdate(const FDebugDisplayInfo& Info);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "LesFight|Debug")
    bool bIsVisible;

    UPROPERTY(BlueprintReadOnly, Category = "LesFight|Debug")
    FDebugDisplayInfo CurrentDebugInfo;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnDebugInfoUpdated OnDebugInfoUpdated;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Debug")
    void CollectDebugInfo();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Debug")
    void ExecuteConsoleCommand(const FString& Command);
};
