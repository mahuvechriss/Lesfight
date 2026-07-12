#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightHostGameUI.generated.h"

DECLARE_DELEGATE_TwoParams(FOnHostStarted, FName /*SessionName*/, FText /*GameMode*/)
DECLARE_MULTICAST_DELEGATE(FOnHostCancelled)

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightHostGameUI : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void SetSessionName(FText Name);

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    FText GetSessionName() const;

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void SetMaxPlayers(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    int32 GetMaxPlayers() const;

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void SelectArena(FName ArenaID);

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    FName GetSelectedArena() const;

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void SetGameMode(FText Mode);

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    FText GetGameMode() const;

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void SetPrivateMatch(bool bPrivate);

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    bool IsPrivateMatch() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HostGame")
    void SetAvailableArenas(TArray<FText> ArenaNames);
    virtual void SetAvailableArenas_Implementation(TArray<FText> ArenaNames);

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void StartHosting();

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void CancelHosting();

    UFUNCTION(BlueprintCallable, Category = "HostGame")
    void SetHostingStatus(FText Status, bool bSuccess);

    FOnHostStarted OnHostStarted;
    FOnHostCancelled OnHostCancelled;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "HostGame")
    FText SessionName;

    UPROPERTY(BlueprintReadOnly, Category = "HostGame")
    int32 MaxPlayers = 4;

    UPROPERTY(BlueprintReadOnly, Category = "HostGame")
    FName SelectedArenaID;

    UPROPERTY(BlueprintReadOnly, Category = "HostGame")
    FText GameModeText;

    UPROPERTY(BlueprintReadOnly, Category = "HostGame")
    bool bPrivateMatch = false;
};
