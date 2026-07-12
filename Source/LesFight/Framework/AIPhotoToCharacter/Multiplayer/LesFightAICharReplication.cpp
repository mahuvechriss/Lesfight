#include "LesFightAICharReplication.h"
#include "Framework/AIPhotoToCharacter/Manager/LesFightAIManager.h"

ULesFightAICharReplication::ULesFightAICharReplication()
    : bReplicationEnabled(true)
    , CompressionLevel(3)
    , SyncInterval(2.0f)
{
}

void ULesFightAICharReplication::Initialize(ULesFightAIManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightAICharReplication::SendGeneratedCharacter(const FAICharacterGenerationResult& Result, int32 TargetPlayerID)
{
    if (!bReplicationEnabled)
    {
        return;
    }

    if (PendingData.Num() >= 50)
    {
        PendingData.RemoveAt(0, 1, false);
    }

    PendingData.Add(Result);
}

void ULesFightAICharReplication::RequestCharacterData(int32 FromPlayerID)
{
}

bool ULesFightAICharReplication::HasPendingData() const
{
    return PendingData.Num() > 0;
}

int32 ULesFightAICharReplication::GetPendingDataCount() const
{
    return PendingData.Num();
}

void ULesFightAICharReplication::ProcessPendingData()
{
    if (!bReplicationEnabled)
    {
        return;
    }

    for (const FAICharacterGenerationResult& Result : PendingData)
    {
        ReceivedData.Add(Result);
        OnAICharDataReceived.Broadcast(Result);
    }

    PendingData.Empty();
}

void ULesFightAICharReplication::ClearPendingData()
{
    PendingData.Empty();
}

void ULesFightAICharReplication::SetReplicationEnabled(bool bEnabled)
{
    bReplicationEnabled = bEnabled;

    if (!bEnabled)
    {
        ClearPendingData();
    }
}

bool ULesFightAICharReplication::IsReplicationEnabled() const
{
    return bReplicationEnabled;
}

FAICharacterGenerationResult ULesFightAICharReplication::OptimizeCharacterData(const FAICharacterGenerationResult& Result)
{
    FAICharacterGenerationResult Optimized = Result;

    Optimized.GeneratedMeshPaths.Empty();

    Optimized.Textures.DiffuseMapPath = Result.Textures.DiffuseMapPath;
    Optimized.Textures.NormalMapPath = Result.Textures.NormalMapPath;
    Optimized.Textures.RoughnessMapPath = Result.Textures.RoughnessMapPath;
    Optimized.Textures.SpecularMapPath = Result.Textures.SpecularMapPath;
    Optimized.Textures.SubsurfaceMapPath = Result.Textures.SubsurfaceMapPath;

    Optimized.FaceData.MeshDataReference = Result.FaceData.MeshDataReference;

    return Optimized;
}

FAICharacterGenerationResult ULesFightAICharReplication::ReconstructCharacterFromOptimized(const FAICharacterGenerationResult& Optimized)
{
    return Optimized;
}
