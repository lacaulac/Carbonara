#include "stdafx.h"
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include "Hooks.h"
#include "SDK.h"
#include "Offsets.h"

void PostDataUpdateStart()
{
	DWORD ClientDLL = (DWORD)GetModuleHandleA("client.dll");
	PlayerBasic* Player = (PlayerBasic*)(*(DWORD*)(ClientDLL + Offsets::LocalPlayer));
	if (Player)
	{
		CSWeapon* Weapon;
		DWORD hMyWeaponsBase = (DWORD)Player + Offsets::m_hMyWeapons;
		for (int i = 0; i < 8; i++)
		{
			int WeaponID = (*(int*)(hMyWeaponsBase + (i * 0x4))) & 0xFFF;

			// IL CONTINUE A Y AVOIR DES COUILLES DANS LE POTAGE <3
			//MEME SI JE VAIS SANS DOUTE PAS COMPRENDRE:
			/*	Il semble que le WeaponID soit toujours egal a 0, il faut mettre un coup de ReClass/CheatEngine
				pour verifier l'etat de la structure.
				Il est possible que les pointeurs ne pointent pas sur les bonnes adresses.
			*/
			DWORD WeaponAddress = *(DWORD*)(ClientDLL + Offsets::EntityList + ((WeaponID - 1) * 0x10));
			Weapon = (CSWeapon*)WeaponAddress;
			if (Weapon)
			{
				if (Weapon->m_iItemDefinitionIndex == ItemDefinitionIndex::WEAPON_KNIFE_T)
				{
					Weapon->m_iItemDefinitionIndex = ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT;
				}
				else if (Weapon->m_iItemDefinitionIndex == ItemDefinitionIndex::WEAPON_KNIFE)
				{
					Weapon->m_iItemDefinitionIndex = ItemDefinitionIndex::WEAPON_KNIFE_BAYONET;
				}
				for (int i = 0; i < j["skins"].size(); i++)
				{
					if (Weapon->m_iItemDefinitionIndex == j["skins"][i]["WeaponID"])
					{
						if (j["skins"][i]["Team"] == 0 || j["skins"][i]["Team"] == Player->Team)
						{
							Weapon->m_iItemIDHigh = -1;
							Weapon->m_nFallbackPaintKit = j["skins"][i]["SkinID"];
							Weapon->m_nFallbackWear = j["skins"][i]["Wear"];
							Weapon->m_nFallbackSeed = j["skins"][i]["Pattern"];
							Weapon->m_nFallbackStatTrak = j["skins"][i]["StatTrak"];
							Weapon->m_iEntityQuality = j["skins"][i]["Rarity"];
						}
					}
				}
			}
		}
	}
}
