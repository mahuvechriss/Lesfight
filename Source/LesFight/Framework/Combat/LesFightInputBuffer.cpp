#include "LesFightInputBuffer.h"
#include "LesFight.h"
#include "Engine/World.h"

ULesFightInputBuffer::ULesFightInputBuffer()
    : BufferWindow(0.15f)
    , MaxBufferSize(10)
{
}

void ULesFightInputBuffer::Initialize()
{
}

void ULesFightInputBuffer::BufferInput(FName InputID, EAttackType AttackType)
{
    FBufferedInput NewInput;
    NewInput.InputID = InputID;
    NewInput.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    NewInput.bConsumed = false;
    NewInput.AttackType = AttackType;

    InputBuffer.Add(NewInput);

    if (InputBuffer.Num() > MaxBufferSize)
    {
        InputBuffer.RemoveAt(0);
    }

    OnInputBuffered.Broadcast(InputID);
}

FBufferedInput ULesFightInputBuffer::ConsumeNextInput()
{
    FlushExpiredInputs();

    for (int32 i = 0; i < InputBuffer.Num(); i++)
    {
        if (!InputBuffer[i].bConsumed)
        {
            InputBuffer[i].bConsumed = true;
            OnInputConsumed.Broadcast(InputBuffer[i].InputID);
            return InputBuffer[i];
        }
    }

    return FBufferedInput();
}

FBufferedInput ULesFightInputBuffer::PeekNextInput() const
{
    for (const FBufferedInput& Input : InputBuffer)
    {
        if (!Input.bConsumed)
            return Input;
    }
    return FBufferedInput();
}

void ULesFightInputBuffer::ClearBuffer()
{
    InputBuffer.Empty();
}

bool ULesFightInputBuffer::HasPendingInput() const
{
    for (const FBufferedInput& Input : InputBuffer)
    {
        if (!Input.bConsumed)
            return true;
    }
    return false;
}

void ULesFightInputBuffer::FlushExpiredInputs()
{
    if (!GetWorld()) return;

    float CurrentTime = GetWorld()->GetTimeSeconds();
    InputBuffer.RemoveAll([CurrentTime, this](const FBufferedInput& Input) {
        return (CurrentTime - Input.Timestamp) > BufferWindow;
    });
}
