#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// CChangePasswordDlg 对话框

class CChangePasswordDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CChangePasswordDlg)

public:
	CChangePasswordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangePasswordDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHANGEPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editPassword;
	CEdit m_editAgain;
	CMFCButton m_btnChange;
	afx_msg void OnBnClickedButtonUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
