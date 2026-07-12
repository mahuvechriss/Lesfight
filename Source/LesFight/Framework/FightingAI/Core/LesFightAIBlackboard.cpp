#include "LesFightAIBlackboard.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"

void ULesFightAIBlackboard::SetValue(FName Key, float Value)
{
    FloatValues.Add(Key, Value);
}

void ULesFightAIBlackboard::SetVector(FName Key, FVector Value)
{
    VectorValues.Add(Key, Value);
}

void ULesFightAIBlackboard::SetObject(FName Key, UObject* Value)
{
    ObjectValues.Add(Key, TWeakObjectPtr<UObject>(Value));
}

float ULesFightAIBlackboard::GetValue(FName Key) const
{
    const float* Value = FloatValues.Find(Key);
    return Value ? *Value : 0.0f;
}

FVector ULesFightAIBlackboard::GetVector(FName Key) const
{
    const FVector* Value = VectorValues.Find(Key);
    return Value ? *Value : FVector::ZeroVector;
}

UObject* ULesFightAIBlackboard::GetObject(FName Key) const
{
    const TWeakObjectPtr<UObject>* WeakPtr = ObjectValues.Find(Key);
    return WeakPtr ? WeakPtr->Get() : nullptr;
}

bool ULesFightAIBlackboard::HasKey(FName Key) const
{
    return FloatValues.Contains(Key) || VectorValues.Contains(Key) || ObjectValues.Contains(Key);
}

void ULesFightAIBlackboard::ClearKey(FName Key)
{
    FloatValues.Remove(Key);
    VectorValues.Remove(Key);
    ObjectValues.Remove(Key);
}

void ULesFightAIBlackboard::ClearAll()
{
    FloatValues.Empty();
    VectorValues.Empty();
    ObjectValues.Empty();
}

TArray<FName> ULesFightAIBlackboard::GetAllKeys() const
{
    TSet<FName> KeySet;
    for (const auto& Entry : FloatValues) KeySet.Add(Entry.Key);
    for (const auto& Entry : VectorValues) KeySet.Add(Entry.Key);
    for (const auto& Entry : ObjectValues) KeySet.Add(Entry.Key);
    return KeySet.Array();
}
