#include "Framework/Release/Core/LesFightReleaseConfigurator.h"
#include "Misc/FileHelper.h"

void ULesFightReleaseConfigurator::Initialize()
{
	ConfigSettings.Empty();
	LoadDefaultSettings();
}

void ULesFightReleaseConfigurator::Shutdown()
{
	ConfigSettings.Empty();
}

void ULesFightReleaseConfigurator::LoadDefaultSettings()
{
	auto Set = [this](const FString& Key, const FString& Value)
	{
		ConfigSettings.FindOrAdd(Key) = Value;
	};

	Set(TEXT("PackageGame"), TEXT("true"));
	Set(TEXT("PackageMods"), TEXT("false"));
	Set(TEXT("PackageBuild"), TEXT("true"));
	Set(TEXT("CookAll"), TEXT("true"));
	Set(TEXT("CompressTextures"), TEXT("true"));
	Set(TEXT("CompressAudio"), TEXT("true"));
	Set(TEXT("CompressMeshes"), TEXT("true"));
	Set(TEXT("TextureQuality"), TEXT("High"));
	Set(TEXT("SoundQuality"), TEXT("High"));
	Set(TEXT("IncludeEditor"), TEXT("false"));
	Set(TEXT("CrashReportClient"), TEXT("true"));
	Set(TEXT("TargetPlatform"), TEXT("Windows"));
}

void ULesFightReleaseConfigurator::ConfigurePackaging()
{
	ConfigSettings.FindOrAdd(TEXT("PackageGame")) = TEXT("true");
	ConfigSettings.FindOrAdd(TEXT("PackageBuild")) = TEXT("true");
	ConfigSettings.FindOrAdd(TEXT("IncludeEditor")) = TEXT("false");
	UE_LOG(LogTemp, Log, TEXT("[ReleaseConfig] Packaging configured"));
}

void ULesFightReleaseConfigurator::ConfigureCompression()
{
	ConfigSettings.FindOrAdd(TEXT("CompressTextures")) = TEXT("true");
	ConfigSettings.FindOrAdd(TEXT("CompressAudio")) = TEXT("true");
	ConfigSettings.FindOrAdd(TEXT("CompressMeshes")) = TEXT("true");
	UE_LOG(LogTemp, Log, TEXT("[ReleaseConfig] Compression configured"));
}

void ULesFightReleaseConfigurator::ConfigureCooking()
{
	ConfigSettings.FindOrAdd(TEXT("CookAll")) = TEXT("true");
	ConfigSettings.FindOrAdd(TEXT("TextureQuality")) = TEXT("High");
	ConfigSettings.FindOrAdd(TEXT("SoundQuality")) = TEXT("High");
	UE_LOG(LogTemp, Log, TEXT("[ReleaseConfig] Cooking configured"));
}

TArray<FString> ULesFightReleaseConfigurator::GetConfigurationSummary()
{
	TArray<FString> Summary;
	Summary.Add(TEXT("=== Release Configuration ==="));
	for (const auto& Setting : ConfigSettings)
	{
		Summary.Add(FString::Printf(TEXT("  %s: %s"), *Setting.Key, *Setting.Value));
	}
	return Summary;
}

bool ULesFightReleaseConfigurator::ExportConfig(const FString& FilePath)
{
	FString Output;
	for (const auto& Setting : ConfigSettings)
	{
		Output += FString::Printf(TEXT("%s=%s\n"), *Setting.Key, *Setting.Value);
	}
	return FFileHelper::SaveStringToFile(Output, *FilePath);
}

bool ULesFightReleaseConfigurator::ImportConfig(const FString& FilePath)
{
	FString Content;
	if (!FFileHelper::LoadFileToString(Content, *FilePath))
	{
		return false;
	}

	TArray<FString> Lines;
	Content.ParseIntoArrayLines(Lines);
	for (const FString& Line : Lines)
	{
		FString Key, Value;
		if (Line.Split(TEXT("="), &Key, &Value))
		{
			ConfigSettings.FindOrAdd(Key) = Value;
		}
	}
	return true;
}
