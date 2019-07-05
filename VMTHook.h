#pragma once
class VMTHook
{
public:
	VMTHook();
	~VMTHook();
	VMTHook(DWORD p_adr);
	void Init(DWORD p_adr);
	DWORD HookMethod(DWORD p_fn, int p_index);
	DWORD GetOldMethod(int p_index);
	void UnHook();
	void ReHook();
private:
	DWORD target;
	DWORD oldVMTAddress;
	DWORD newVMTAddress;
	int maxVMTIndex;
};

