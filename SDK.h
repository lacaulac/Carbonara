#pragma once
#include <cstdint>
#include "IVEngineClient.h"
#include "json.hpp"

using json = nlohmann::json;

class PlayerBasic
{
public:
	char pad_0x0000[0xF0]; //0x0000
	int Team; //0x00F0 
	char pad_0x00F4[0x8]; //0x00F4
	int Health; //0x00FC 
	char pad_0x0100[0x2D08]; //0x0100
	int m_hMyWeapons; //0x2E08 
	char pad_0x2E0C[0xDC]; //0x2E0C
	int h_ActiveWeapon; //0x2EE8 
	char pad_0x2EEC[0x614]; //0x2EEC
};

class CSWeapon
{
public:
	char pad_0x0000[0x2F88]; //0x0000
	int m_iItemDefinitionIndex; //0x2F88 
	int m_iEntityQuality; //0x2F8C 
	char pad_0x2F90[0x10]; //0x2F90
	int m_iItemIDHigh; //0x2FA0 
	char pad_0x2FA4[0x4]; //0x2FA4
	int m_iAccountID; //0x2FA8 
	char pad_0x2FAC[0x70]; //0x2FAC
	char* m_szCustomName; //0x301C 
	char pad_0x3020[0x148]; //0x3020
	int m_OriginalOwnerXuidLow; //0x3168 
	int m_OriginalOwnerXuidHigh; //0x316C 
	int m_nFallbackPaintKit; //0x3170 
	int m_nFallbackSeed; //0x3174 
	float m_nFallbackWear; //0x3178 
	int m_nFallbackStatTrak; //0x317C 
	char pad_0x3180[0x6C0]; //0x3180

};

enum ClientFrameStage_t : int
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum ItemDefinitionIndex : int {
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};

class IGameEvent
{
public:
	virtual					~IGameEvent() {};
	virtual const char*		GetName() const = 0;

	virtual bool			IsReliable() const = 0;
	virtual bool			IsLocal() const = 0;
	virtual bool			IsEmpty(const char* keyname = nullptr) = 0;

	virtual bool			GetBool(const char* keyname = nullptr, bool default_value = false) = 0;
	virtual int				GetInt(const char* keyname = nullptr, int default_value = 0) = 0;
	virtual uint64_t		GetUint64(const char* keyname = nullptr, uint64_t default_value = 0) = 0;
	virtual float			GetFloat(const char* keyname = nullptr, float default_value = 0.0f) = 0;
	virtual const char*		GetString(const char* keyname = nullptr, const char* default_value = "") = 0;
	virtual const wchar_t*	GetWString(const char* keyname = nullptr, const wchar_t* default_value = L"") = 0;
	virtual const void*		GetPtr(const char* keyname = nullptr, const void* default_values = nullptr) = 0;

	virtual void			SetBool(const char* keyname, bool value) = 0;
	virtual void			SetInt(const char* keyname, int value) = 0;
	virtual void			SetUint64(const char* keyname, uint64_t value) = 0;
	virtual void			SetFloat(const char* keyname, float value) = 0;
	virtual void			SetString(const char* keyname, const char* value) = 0;
	virtual void			SetWString(const char* keyname, const wchar_t* value) = 0;
	virtual void			SetPtr(const char* keyname, const void* value) = 0;
};

extern json j;