#pragma once
class Offsets
{
public:
	Offsets();
	~Offsets();
	static void GetOffsets();

	static DWORD LocalPlayer;
	static DWORD EntityList;
	static DWORD ClientState;

	//ClientState shite
	static DWORD m_nDeltaTick;

	//CPlayer shite
	static DWORD m_hMyWeapons;
};

