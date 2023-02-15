#pragma once
#include "pch.h"
#include <afxdialogex.h>
// DumperDialog 对话框

class DumperDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DumperDialog)

public:
	DumperDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DumperDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DUMPER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// StaticFindObjectOffset
	CEdit edit_StaticFindObjectOffset;
	afx_msg void OnBnClickedButtonBtnstaticfindobjectoffset();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBtnstaticfindobjectoffset2();
	afx_msg void OnBnClickedButtonBtnstaticfindobjectoffset3();
	afx_msg void OnBnClickedButtonBtnstaticfindobjectoffset4();
};
