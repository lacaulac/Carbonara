#pragma once

typedef void*(*CreateInterfaceFn)(char*, int*);

class InterfaceManager
{
private:
	CreateInterfaceFn InterfaceFactory;
public:
	InterfaceManager();
	InterfaceManager(char* p_dllName);
	void Init(char* p_dllName);
	void* getInterface(char* p_interfaceName);
};