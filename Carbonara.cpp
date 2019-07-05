// Carbonara.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include "Carbonara.h"
#include "InterfaceManager.hpp"
#include "VMTHook.h"
#include "SDK.h"
#include "Hooks.h"
#include "json.hpp"
#include <fstream>
#include "Utils.h"
#include <time.h>
#include "Offsets.h"


using json = nlohmann::json;

FindMDL_t oFindMDL;
FrameStageNotify_t oFrameStageNotify;
FireEventClientSide_t oFireEventClientSide;

MDLHandle_t __fastcall HK_FindMDL(void* ecx, void* edx, char* FilePath);
void __fastcall HK_FrameStageNotify(void* ecx, void* edx, ClientFrameStage_t stage);
void __fastcall HK_FireEventClientSide(void* ecx, void* edx, IGameEvent* gameEvent);

DWORD ClientDLL;
DWORD EngineDLL;
PlayerBasic* LocalPlayer;

IVEngineClient* Engie;

int killIndex = 0;

json j;

char* KillMessage[] = { "say You got killed <3", "say Rest in pieces", "say See you next round c:" };
char* HSMessage[] = { "say Is it a bird? Is it a plane? No, it's an headshot!", " say Need some aspirine?", "say Where's your brain game now?" };

void Reload();

void MainThread()
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	freopen("CONIN$", "rb", stdin);

	srand(time(NULL));

	ClientDLL = (DWORD)GetModuleHandleA("client.dll");
	EngineDLL = (DWORD)GetModuleHandleA("engine.dll");

	// read a JSON file
	Reload();
	Offsets::GetOffsets();

	InterfaceManager DataCacheMGR("datacache.dll");
	DWORD MDLCacheAdr = (DWORD)DataCacheMGR.getInterface("MDLCache004");
	VMTHook MDLCacheHook(MDLCacheAdr);

	InterfaceManager ClientMGR("client.dll");
	DWORD ClientAdr = (DWORD)ClientMGR.getInterface("VClient018");
	VMTHook ClientHook(ClientAdr);

	InterfaceManager EngineMGR("engine.dll");
	DWORD GEAdr = (DWORD)EngineMGR.getInterface("GAMEEVENTSMANAGER002");
	VMTHook GEHook(GEAdr);
	Engie = (IVEngineClient*)EngineMGR.getInterface("VEngineClient014");


	oFindMDL = (FindMDL_t)MDLCacheHook.HookMethod((DWORD)&HK_FindMDL, 10);
	oFrameStageNotify = (FrameStageNotify_t)ClientHook.HookMethod((DWORD)&HK_FrameStageNotify, 36);
	oFireEventClientSide = (FireEventClientSide_t)GEHook.HookMethod((DWORD)&HK_FireEventClientSide, 9);

	while (true)
	{
		if (GetAsyncKeyState(VK_F9)) //Force full update
		{
			//Engie->ClientCmd_Unrestricted("record x; stop"); //TODO Insert better force full update shite here
			*(int*)(*(DWORD*)((DWORD)GetModuleHandleA("engine.dll") + Offsets::ClientState) + 0x174) = -1; //SICK RELOAD
			Reload();
			while ((GetAsyncKeyState(VK_F9)))
			{
				Sleep(100);
			}
		}
		Sleep(100);
	}
}

#pragma region Hooks

MDLHandle_t __fastcall HK_FindMDL(void* ecx, void* edx, char* FilePath)
{

	if (strstr(FilePath, "knife_default_t.mdl"))
	{
		sprintf(FilePath, "models/weapons/v_knife_karam.mdl");
		printf("GAVE KARAMBIT\n");
	}
	else if (strstr(FilePath, "knife_default_ct.mdl"))
	{
		sprintf(FilePath, "models/weapons/v_knife_bayonet.mdl");
		printf("GAVE BAYONET\n");
	}
	else if (strstr(FilePath, "glove"))
	{
		sprintf(FilePath, "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl");
		printf("GAVE GLOVES\n");
	}
	else
	{
		printf("Requested %s\n", FilePath);
	}
	return oFindMDL(ecx, FilePath);
}

void __fastcall HK_FrameStageNotify(void* ecx, void* edx, ClientFrameStage_t stage)
{
	if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		PostDataUpdateStart();
	}
	oFrameStageNotify(ecx, stage);
}

void __fastcall HK_FireEventClientSide(void * ecx, void * edx, IGameEvent * gameEvent)
{
	if (!strcmp(gameEvent->GetName(), "player_death"))
	{
		if (Engie->GetLocalPlayer() == Engie->GetPlayerForUserID(gameEvent->GetInt("attacker")))
		{
			printf("WEAPON: %s\n", gameEvent->GetString("weapon"));
			if (strstr(gameEvent->GetString("weapon"), "knife"))
			{
				gameEvent->SetString("weapon", "knife_karambit");
				Engie->ClientCmd_Unrestricted("say HAHA! GOTCHA IDIOT <3", false);
			}
			else
			{
				if (gameEvent->GetBool("headshot"))
				{
					Engie->ClientCmd_Unrestricted(((std::string)(j["hsphrases"][Utils::getRandomIndex(j["hsphrases"].size())])).c_str(), false);
				}
				else
				{
					Engie->ClientCmd_Unrestricted(((std::string)(j["killphrases"][Utils::getRandomIndex(j["killphrases"].size())])).c_str(), false);
				}
			}
		}
	}
	oFireEventClientSide(ecx, gameEvent);
}

#pragma endregion Hooks

void Reload()
{
	std::ifstream i2("C:/SkinChanger/config.json");
	j.clear();
	i2 >> j;
	i2.close();
}
