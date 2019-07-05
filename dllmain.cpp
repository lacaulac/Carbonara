// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Carbonara.h"
#include "WindowsHWID.h"

#define PROTECTE

#ifdef PROTECTED
const char* UserHWID = "{bbed3e02-0b41-11e3-8249-806e6f6e6963}";
char buffer[42];
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		#ifdef PROTECTED
		getHWID(buffer);
		if (strcmp(buffer, UserHWID))
		{
			MessageBoxA(NULL, "Contact the developer.", "Wrong PC.", NULL);
			exit(404);
		}
		#endif
		CreateThread(0, 0x1000, (LPTHREAD_START_ROUTINE)&MainThread, 0, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

