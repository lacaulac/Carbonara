#pragma once

#include "VMTHook.h"
#include <cstdint>
#include "virtuals.h"

constexpr auto MAX_PLAYER_NAME_LENGTH = 128;
constexpr auto SIGNED_GUID_LEN = 32;

typedef struct player_info_s
{
private:
	int64_t unknown;
public:
	union
	{
		int64_t xuid;

		struct
		{
			int xuid_low;
			int xuid_high;
		};
	};

	char name[MAX_PLAYER_NAME_LENGTH];
	int userid;
	int m_nUserID;
	char guid[SIGNED_GUID_LEN + 1];
	unsigned int friendsid;
	char friendsname[MAX_PLAYER_NAME_LENGTH];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
} player_info_t;

class IVEngineClient
{
private:
public:
	int GetLocalPlayer()
	{
		return GetVirtualFunction<int(__thiscall *)(IVEngineClient*)>(this, 12)(this);
	}
	int GetPlayerForUserID(int userid)
	{
		return GetVirtualFunction<bool(__thiscall *)(IVEngineClient*, int)>(this, 9)(this, userid);
	}
	void ClientCmd_Unrestricted(const char* command, bool delayed = false)
	{
		return GetVirtualFunction<void(__thiscall *)(IVEngineClient*, const char*, bool)>(this, 114)(this, command, delayed);
	}
	bool GetPlayerInfo(int index, player_info_t* player_info)
	{
		return GetVirtualFunction<bool(__thiscall *)(IVEngineClient*, int, player_info_t*)>(this, 8)(this, index, player_info);
	}
};

extern IVEngineClient* Engie;