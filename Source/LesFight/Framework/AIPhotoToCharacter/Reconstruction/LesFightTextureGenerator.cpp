#include "LesFightTextureGenerator.h"
#include "Pipeline/LesFightAIPipelineManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"

void ULesFightTextureGenerator::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bTexturesGenerated = false;
    OutputDirectory = FPaths::ProjectSavedDir() / TEXT("GeneratedTextures");

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*OutputDirectory))
    {
        PlatformFile.CreateDirectoryTree(*OutputDirectory);
    }
}

void ULesFightTextureGenerator::GenerateTextures(const FFaceFeatureData& Features, const FString& SourceImagePath)
{
    FString BaseName = FPaths::GetBaseFilename(SourceImagePath);
    if (BaseName.IsEmpty())
    {
        BaseName = TEXT("Character");
    }

    FString TexDir = OutputDirectory / BaseName;
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*TexDir))
    {
        PlatformFile.CreateDirectoryTree(*TexDir);
    }

    FGeneratedTextureData Textures;
    Textures.DiffuseMapPath = TexDir / TEXT("Diffuse.png");
    Textures.NormalMapPath = TexDir / TEXT("Normal.png");
    Textures.RoughnessMapPath = TexDir / TEXT("Roughness.png");
    Textures.SpecularMapPath = TexDir / TEXT("Specular.png");
    Textures.SubsurfaceMapPath = TexDir / TEXT("Subsurface.png");
    Textures.TextureResolution = TextureResolution;
    Textures.bHasScars = false;
    Textures.bHasMarks = false;

    GeneratedTextures = Textures;
    bTexturesGenerated = true;
}

void ULesFightTextureGenerator::SetTextureResolution(int32 Resolution)
{
    TextureResolution = FMath::Clamp(Resolution, 256, 8192);
}

void ULesFightTextureGenerator::GenerateNormalMap(const FString& DiffusePath)
{
    FString BaseDir = FPaths::GetPath(DiffusePath);
    FString NormalPath = BaseDir / TEXT("Normal.png");

    GeneratedTextures.NormalMapPath = NormalPath;
}

void ULesFightTextureGenerator::GenerateRoughnessMap(const FString& DiffusePath)
{
    FString BaseDir = FPaths::GetPath(DiffusePath);
    FString RoughnessPath = BaseDir / TEXT("Roughness.png");

    GeneratedTextures.RoughnessMapPath = RoughnessPath;
}

void ULesFightTextureGenerator::GenerateSubsurfaceMap(const FString& DiffusePath)
{
    FString BaseDir = FPaths::GetPath(DiffusePath);
    FString SubsurfacePath = BaseDir / TEXT("Subsurface.png");

    GeneratedTextures.SubsurfaceMapPath = SubsurfacePath;
}

void ULesFightTextureGenerator::ApplySkinDetail(ESkinDetailLevel Detail)
{
    switch (Detail)
    {
    case ESkinDetailLevel::Low:
        TextureResolution = 1024;
        break;
    case ESkinDetailLevel::Medium:
        TextureResolution = 2048;
        break;
    case ESkinDetailLevel::High:
        TextureResolution = 4096;
        break;
    case ESkinDetailLevel::Ultra:
        TextureResolution = 8192;
        break;
    }
    GeneratedTextures.TextureResolution = TextureResolution;
}

void ULesFightTextureGenerator::GenerateTattooTexture(const FTattooEntry& Tattoo)
{
    GeneratedTextures.bHasMarks = true;
}

void ULesFightTextureGenerator::GenerateScarTexture(const FVector2D& Position, float Intensity)
{
    GeneratedTextures.bHasScars = true;
    if (Intensity > 0.0f)
    {
        GeneratedTextures.BlemishPositions.Add(Position);
    }
}
