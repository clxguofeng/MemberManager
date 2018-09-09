#pragma once
#include "afxwin.h"


// CUserAddOrUpdateDlg �Ի���

class CUserAddOrUpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserAddOrUpdateDlg)

public:
	CUserAddOrUpdateDlg(BOOL bAdd, int iUserId = 0, CString strUser = "", CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserAddOrUpdateDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USER_ADD_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bAdd;
	int m_iUserid;
	CString m_strUser;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CEdit m_editName;
};
