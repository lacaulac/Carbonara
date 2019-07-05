#pragma once

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <stdio.h>
#include <clocale>
#include <cstdlib>

void getHWID(char* bufferino)
{
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfile(&hwProfileInfo) != NULL) {
		wcstombs(bufferino, (wchar_t*)hwProfileInfo.szHwProfileGuid, 100);
	}
}