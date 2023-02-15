// ALienUEDumper.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "ALienUEDumper.h"
#include "DumperDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CALienUEDumperApp

BEGIN_MESSAGE_MAP(CALienUEDumperApp, CWinApp)
END_MESSAGE_MAP()


// CALienUEDumperApp 构造

CALienUEDumperApp::CALienUEDumperApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CALienUEDumperApp 对象

CALienUEDumperApp theApp;
DumperDialog* pDumperDialog = NULL;
DWORD WINAPI ThreadCallBack(LPARAM lparam)
{
    pDumperDialog = new DumperDialog();
    pDumperDialog->DoModal();//创建模态窗口 然后堵塞 等待窗口关闭后继续往下执行  
    FreeLibraryAndExitThread(theApp.m_hInstance, 1);//释放 会触发ExitInstance();
    return TRUE;
}

//控制台
void startDebugWindow()
{
    HINSTANCE g_hInstance = 0;
    HANDLE g_hOutput = 0;
    HWND hwnd = NULL;
    HMENU hmenu = NULL;
    CHAR title[] = "控制台";
    HANDLE hdlWrite = NULL;

    AllocConsole();

    freopen("CONIN$", "r+t", stdin);
    freopen("CONOUT$", "w+t", stdout);
    g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    // 设置控制台窗口的属性
    SetConsoleTitleA(title);
    SetConsoleTextAttribute((HANDLE)g_hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    // 屏蔽掉控制台窗口的关闭按钮，以防窗口被误删除，会让游戏也关闭
    while (NULL == hwnd)
    {
        hwnd = FindWindowA("ConsoleWindowClass", title);
    }
    hmenu = ::GetSystemMenu(hwnd, FALSE);
    //DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
    hdlWrite = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(g_hOutput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(g_hOutput, mode);
    //SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    MoveWindow(hwnd, 50, 50, 550, 420, true);
    // 这里也可以使用STD_ERROR_HANDLE    TCHAR c[] = {"Hello world!"};WriteConsole(hdlWrite, c, sizeof(c), NULL, NULL);
}

// CALienUEDumperApp 初始化

BOOL CALienUEDumperApp::InitInstance()
{
	CWinApp::InitInstance();
    startDebugWindow();
    ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadCallBack, 0, 0, 0);//不会堵塞
	return TRUE;
}