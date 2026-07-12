#include "LesFightHardwareDetector.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformMemory.h"
#include "HAL/PlatformProperties.h"
#include "GenericPlatform/GenericPlatformDriver.h"

void ULesFightHardwareDetector::Initialize()
{
	CPUName = TEXT("Unknown");
	GPUName = TEXT("Unknown");
	OSVersion = TEXT("Unknown");
	CPUCores = 0;
	GPUMemoryMB = 0.0f;
	TotalRAMMB = 0.0f;
	AvailableRAMMB = 0.0f;
	StorageFreeGB = 0.0f;
	HardwareScore = 0.0f;
	DetectedQuality = EPerformanceQualityLevel::High;
}

void ULesFightHardwareDetector::Shutdown()
{
}

void ULesFightHardwareDetector::DetectHardware()
{
	CPUName = FPlatformMisc::GetCPUVendor();
	CPUCores = FPlatformMisc::NumberOfCoresIncludingHyperthreads();

	OSVersion = FPlatformProperties::PlatformName();

	FPlatformMemoryStats MemoryStats = FPlatformMemory::GetStats();
	TotalRAMMB = static_cast<float>(MemoryStats.TotalPhysicalGB) * 1024.0f;
	AvailableRAMMB = static_cast<float>(MemoryStats.AvailablePhysical) / (1024.0f * 1024.0f);

	FGPUDriverInfo GPUInfo = FPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);
	GPUName = GPUInfo.DeviceDescription;
	GPUMemoryMB = static_cast<float>(GPUInfo.TotalVideoMemoryMB);

	uint64 FreeBytes = 0;
	FPlatformMisc::GetDiskTotalAndFreeSpace(FPlatformProcess::BaseDir(), FreeBytes, FreeBytes);
	StorageFreeGB = static_cast<float>(FreeBytes) / (1024.0f * 1024.0f * 1024.0f);

	float Score = 0.0f;

	if (CPUCores >= 12) Score += 20.0f;
	else if (CPUCores >= 8) Score += 15.0f;
	else if (CPUCores >= 6) Score += 10.0f;
	else if (CPUCores >= 4) Score += 5.0f;

	if (TotalRAMMB >= 32768.0f) Score += 25.0f;
	else if (TotalRAMMB >= 16384.0f) Score += 20.0f;
	else if (TotalRAMMB >= 8192.0f) Score += 10.0f;
	else if (TotalRAMMB >= 4096.0f) Score += 5.0f;

	if (GPUMemoryMB >= 8192.0f) Score += 25.0f;
	else if (GPUMemoryMB >= 4096.0f) Score += 15.0f;
	else if (GPUMemoryMB >= 2048.0f) Score += 10.0f;

	if (StorageFreeGB >= 100.0f) Score += 10.0f;
	else if (StorageFreeGB >= 50.0f) Score += 5.0f;

	HardwareScore = FMath::Min(Score, 100.0f);

	if (HardwareScore >= 70.0f) DetectedQuality = EPerformanceQualityLevel::Ultra;
	else if (HardwareScore >= 50.0f) DetectedQuality = EPerformanceQualityLevel::High;
	else if (HardwareScore >= 30.0f) DetectedQuality = EPerformanceQualityLevel::Medium;
	else DetectedQuality = EPerformanceQualityLevel::Low;

	OnHardwareDetected.Broadcast(DetectedQuality);
}

EPerformanceQualityLevel ULesFightHardwareDetector::GetDetectedQualityLevel() const
{
	return DetectedQuality;
}

FString ULesFightHardwareDetector::GetCPUName() const
{
	return CPUName;
}

int32 ULesFightHardwareDetector::GetCPUCores() const
{
	return CPUCores;
}

FString ULesFightHardwareDetector::GetGPUName() const
{
	return GPUName;
}

float ULesFightHardwareDetector::GetGPUMemoryMB() const
{
	return GPUMemoryMB;
}

float ULesFightHardwareDetector::GetTotalRAMMB() const
{
	return TotalRAMMB;
}

float ULesFightHardwareDetector::GetAvailableRAMMB() const
{
	return AvailableRAMMB;
}

float ULesFightHardwareDetector::GetStorageFreeGB() const
{
	return StorageFreeGB;
}

FString ULesFightHardwareDetector::GetOSVersion() const
{
	return OSVersion;
}

bool ULesFightHardwareDetector::IsHighEndPC() const
{
	return DetectedQuality == EPerformanceQualityLevel::Ultra;
}

bool ULesFightHardwareDetector::IsMidRangePC() const
{
	return DetectedQuality == EPerformanceQualityLevel::High;
}

bool ULesFightHardwareDetector::IsLowEndPC() const
{
	return DetectedQuality == EPerformanceQualityLevel::Medium ||
		DetectedQuality == EPerformanceQualityLevel::Low;
}

float ULesFightHardwareDetector::GetHardwareScore() const
{
	return HardwareScore;
}

TArray<FString> ULesFightHardwareDetector::GetHardwareReport() const
{
	TArray<FString> Report;
	Report.Add(FString::Printf(TEXT("CPU: %s (%d cores)"), *CPUName, CPUCores));
	Report.Add(FString::Printf(TEXT("GPU: %s (%d MB)"), *GPUName, static_cast<int32>(GPUMemoryMB)));
	Report.Add(FString::Printf(TEXT("OS: %s"), *OSVersion));
	Report.Add(FString::Printf(TEXT("Total RAM: %.0f MB"), TotalRAMMB));
	Report.Add(FString::Printf(TEXT("Available RAM: %.0f MB"), AvailableRAMMB));
	Report.Add(FString::Printf(TEXT("Free Storage: %.0f GB"), StorageFreeGB));
	Report.Add(FString::Printf(TEXT("Hardware Score: %.1f / 100"), HardwareScore));

	FString QualityLabel;
	switch (DetectedQuality)
	{
	case EPerformanceQualityLevel::Ultra:  QualityLabel = TEXT("Ultra"); break;
	case EPerformanceQualityLevel::High:   QualityLabel = TEXT("High"); break;
	case EPerformanceQualityLevel::Medium: QualityLabel = TEXT("Medium"); break;
	case EPerformanceQualityLevel::Low:    QualityLabel = TEXT("Low"); break;
	default:                               QualityLabel = TEXT("Unknown"); break;
	}
	Report.Add(FString::Printf(TEXT("Recommended Quality: %s"), *QualityLabel));

	return Report;
}
