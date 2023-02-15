#include "../pch.h"
#include "GameMgr.h"
#include "../MinHook/MinHook.h"

//内联汇编跳转地址
DECLSPEC_NORETURN EXTERN_C  __int64 ComponentCallAddress = (__int64)0x00007FF78E1E3300;


GameHook::t_ProcessEvent pfProcessEvent = NULL;
VOID GameHook::HookedProcessEvent(uintptr_t* pObject, void* pFunction, void* params)
{
	return pfProcessEvent(pObject, pFunction, params);
}

void GameHook::StartHook()
{
	if (MH_Initialize() != MH_OK)
	{
		return;
	}
	printf("[MyHook]:MH_Initialize success\n");
	if (MH_CreateHook((LPVOID)Offsets::ProcessEvent, &HookedProcessEvent,
		reinterpret_cast<LPVOID*>(&pfProcessEvent)) != MH_OK)
	{
		printf("[MyHook]:MH_CreateHook faild\n");
		return;
	}
	if (MH_EnableHook((LPVOID)Offsets::ProcessEvent) != MH_OK)
	{
		printf("[MyHook]:MH_EnableHook faild\n");
		return;
	}
	printf("[MyHook]:begin hook\n");
}

VOID GameHook::StopHook()
{
	if (MH_DisableHook((LPVOID)Offsets::ProcessEvent) == MB_OK)
	{
		printf("[MyHook]:MH_Uninitialize success\n");
		MH_Uninitialize();
	}
}