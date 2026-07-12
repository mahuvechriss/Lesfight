#include "LesFightSaveGame.h"

ULesFightSaveGame::ULesFightSaveGame()
    : SaveVersion(1)
    , SaveTimestamp(FDateTime::Now())
{
}
