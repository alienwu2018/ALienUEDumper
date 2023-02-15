// DumperDialog.cpp: 实现文件
//

#include "pch.h"
#include "ALienUEDumper.h"
#include "DumperDialog.h"
#include "afxdialogex.h"

// DumperDialog 对话框

IMPLEMENT_DYNAMIC(DumperDialog, CDialogEx)

DumperDialog::DumperDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DUMPER, pParent)
{

}

DumperDialog::~DumperDialog()
{
}

void DumperDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_StaticFindObjectOffset, edit_StaticFindObjectOffset);
}


BEGIN_MESSAGE_MAP(DumperDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BtnStaticFindObjectOffset, &DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset)
	ON_BN_CLICKED(IDC_BUTTON_BtnStaticFindObjectOffset2, &DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset2)
	ON_BN_CLICKED(IDC_BUTTON_BtnStaticFindObjectOffset3, &DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset3)
	ON_BN_CLICKED(IDC_BUTTON_BtnStaticFindObjectOffset4, &DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset4)
END_MESSAGE_MAP()


void DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset()
{
	CString cs;
	edit_StaticFindObjectOffset.GetWindowTextW(cs);
	int nOffset =0;
	if (StrToIntExW(cs.GetString(), STIF_SUPPORT_HEX, &nOffset))
	{
		uintptr_t pdwBaseAddress = (uintptr_t)GetModuleHandle(NULL);
		Offsets::StaticFindObject = pdwBaseAddress + nOffset;

		bool b = OffsetsFinder::FindAll();
		if (!b)
		{
			printf("初始化失败\n");
			return;
		}
		Util::CallFuncByMainThread();
	}
}

//Illegal call to StaticFindObject() while serializing object data!
BOOL DumperDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString cs(L"0x229B910");//0x111DDA0  Inf0x4C041B0  overprime 0x1D0EF20 undec 0x1D781B0 DKO 0x229B910
	edit_StaticFindObjectOffset.SetWindowTextW(cs);
	Util::init();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset2()
{
	// TODO: 在此添加控件通知处理程序代码
	GameHook::StopHook();
}


void DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset3()
{
	// TODO: 在此添加控件通知处理程序代码
	Util::StartHijackMainThread();
	printf("hook 主线程\n");
}


void DumperDialog::OnBnClickedButtonBtnstaticfindobjectoffset4()
{
	// TODO: 在此添加控件通知处理程序代码
	Util::StopHijackMainThread();
	printf("卸载 主线程\n");
}
