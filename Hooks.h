#pragma once
#include "SDK.h"

typedef unsigned short MDLHandle_t;

typedef MDLHandle_t(__thiscall *FindMDL_t)(void*, char*);
typedef void(__thiscall *FrameStageNotify_t)(void*, ClientFrameStage_t);
typedef bool(__thiscall *FireEventClientSide_t)(void*, IGameEvent*);

void PostDataUpdateStart();