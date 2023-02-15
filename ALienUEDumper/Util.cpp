#include "pch.h"
#include "Util.h"

void Util::init()
{
	HWND hGame = ::FindWindowA("UnrealWindow", "Divine Knockout  ");
	Util::hwnd = hGame;
	Util::HijackCode = RegisterWindowMessageA("HijackCode");
}

LRESULT CALLBACK Util::GameWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* lpArg = (CWPSTRUCT*)lParam;
	if (nCode == HC_ACTION)
	{
		if (lpArg->hwnd == Util::hwnd && lpArg->message == Util::HijackCode)
		{
			uintptr_t* QAHelperObject = SDKMgr::SDK_StaticFindObject(0, 0, L"/Script/Brawler.BLCheatComponent", false);
			uintptr_t* ConfigMenuFunc = SDKMgr::SDK_StaticFindObject(0, 0, L"/Script/Brawler.BLCheatComponent:ServerSuicide", false);
			/*struct {
				PVOID  BLCheatComponentObj;
			} params;*/
			SDKMgr::SDK_ProcessEvent(QAHelperObject, ConfigMenuFunc, NULL);
			printf("ProcessEvnet Call\n");
			return TRUE;
		}
	}
	return CallNextHookEx(g_hhkGame, nCode, wParam, lParam);
}

BOOLEAN Util::StartHijackMainThread()
{
	DWORD dwThreadId = GetWindowThreadProcessId(Util::hwnd, NULL);
	if (dwThreadId != 0)
	{
		Util::g_hhkGame = SetWindowsHookExA(WH_CALLWNDPROC, GameWndProc, NULL, dwThreadId);
	}
	return TRUE;
}

BOOLEAN Util::StopHijackMainThread()
{
	UnhookWindowsHookEx(Util::g_hhkGame);
	return TRUE;
}

DWORD Util::CallFuncByMainThread()
{
	SendMessageA(Util::hwnd, Util::HijackCode, 0, 0);
	return TRUE;
}