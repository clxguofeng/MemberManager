#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// CChangePasswordDlg �Ի���

class CChangePasswordDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CChangePasswordDlg)

public:
	CChangePasswordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangePasswordDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHANGEPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editPassword;
	CEdit m_editAgain;
	CMFCButton m_btnChange;
	afx_msg void OnBnClickedButtonUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
