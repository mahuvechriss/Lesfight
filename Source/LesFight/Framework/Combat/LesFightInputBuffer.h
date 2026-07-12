#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightInputBuffer.generated.h"

USTRUCT(BlueprintType)
struct FBufferedInput
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName InputID;

    UPROPERTY(BlueprintReadOnly)
    float Timestamp;

    UPROPERTY(BlueprintReadOnly)
    bool bConsumed;

    UPROPERTY(BlueprintReadOnly)
    EAttackType AttackType;

    FBufferedInput()
        : InputID(NAME_None)
        , Timestamp(0.0f)
        , bConsumed(false)
        , AttackType(EAttackType::LightPunch)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputBuffered, FName, InputID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputConsumed, FName, InputID);

UCLASS(Blueprintable)
class ULesFightInputBuffer : public UObject
{
    GENERATED_BODY()

public:
    ULesFightInputBuffer();

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void BufferInput(FName InputID, EAttackType AttackType);

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    FBufferedInput ConsumeNextInput();

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    FBufferedInput PeekNextInput() const;

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void ClearBuffer();

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void SetBufferWindow(float Window) { BufferWindow = Window; }

    UFUNCTION(BlueprintPure, Category = "InputBuffer")
    bool HasPendingInput() const;

    UFUNCTION(BlueprintPure, Category = "InputBuffer")
    int32 GetBufferSize() const { return InputBuffer.Num(); }

    UFUNCTION(BlueprintPure, Category = "InputBuffer")
    float GetBufferWindow() const { return BufferWindow; }

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void SetMaxBufferSize(int32 MaxSize) { MaxBufferSize = MaxSize; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputBuffer")
    float BufferWindow;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputBuffer")
    int32 MaxBufferSize;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInputBuffered OnInputBuffered;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInputConsumed OnInputConsumed;

private:
    UPROPERTY()
    TArray<FBufferedInput> InputBuffer;

    void FlushExpiredInputs();
};
