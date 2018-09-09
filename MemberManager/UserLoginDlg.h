#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// CUserLoginDlg �Ի���

class CUserLoginDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(BOOL bSave, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLoginDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USER_LOGIN };
public:
	BOOL m_bSave;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
