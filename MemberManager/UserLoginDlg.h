#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// CUserLoginDlg 对话框

class CUserLoginDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(BOOL bSave, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserLoginDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_USER_LOGIN };
public:
	BOOL m_bSave;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editIP;
	CEdit m_editUser;
	CEdit m_editPassword;
	afx_msg void OnBnClickedOk();
	CButton m_btnSave;
	CMFCButton m_btnOK;
	CMFCButton m_btnCancel;
	BOOL CheckUserLogin(CString strSQL);
};
