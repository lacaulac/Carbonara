#include "stdafx.h"
#include "Offsets.h"
#include "json.hpp"
#include <fstream>

DWORD Offsets::ClientState;
DWORD Offsets::EntityList;
DWORD Offsets::LocalPlayer;
DWORD Offsets::m_nDeltaTick;
DWORD Offsets::m_hMyWeapons;

Offsets::Offsets()
{
}


Offsets::~Offsets()
{
}

void Offsets::GetOffsets()
{
	nlohmann::json tmp;
	std::ifstream filez("C:/SkinChanger/offsets.json");
	tmp.clear();
	filez >> tmp;
	filez.close();

	LocalPlayer = tmp["signatures"]["dwLocalPlayer"];
	EntityList = tmp["signatures"]["dwEntityList"];
	ClientState = tmp["signatures"]["dwClientState"];

	m_nDeltaTick = 0x174;

	m_hMyWeapons = tmp["netvars"]["m_hMyWeapons"];
}
