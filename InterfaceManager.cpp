#include "stdafx.h"
#include "InterfaceManager.hpp"
#include <windows.h>

InterfaceManager::InterfaceManager()
{
}

InterfaceManager::InterfaceManager(char* p_dllName)
{
	Init(p_dllName);
}

void InterfaceManager::Init(char* p_dllName)
{
	InterfaceFactory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress((HMODULE)GetModuleHandleA(p_dllName), "CreateInterface"));
}

void* InterfaceManager::getInterface(char* p_interfaceName)
{
	return InterfaceFactory(p_interfaceName, NULL);
}