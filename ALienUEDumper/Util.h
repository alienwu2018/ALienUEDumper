#pragma once


namespace Util {
	extern inline HHOOK g_hhkGame = 0;
	extern inline DWORD HijackCode = 0;
	extern inline HWND hwnd = 0;
	extern LRESULT CALLBACK GameWndProc(int nCode, WPARAM wParam, LPARAM lParam);
	extern BOOLEAN StartHijackMainThread();
	extern BOOLEAN StopHijackMainThread();
	extern DWORD CallFuncByMainThread();
	extern void init();
}