#pragma once


// CUpdateMemberDlg �Ի���
// #include "MFCDialog.h"
#include "afxbutton.h"

class CUpdateMemberDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUpdateMemberDlg)

public:
	CUpdateMemberDlg(CWnd* pParent = NULL, int iMod = 0);   // ��׼���캯��
	virtual ~CUpdateMemberDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATEMEMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNum;
	CString m_strName;
	CString m_strCode;
	CString m_strPhone;
	CString m_strComment;
	CString m_strStyle;
	CString	m_strID;
	int		m_iMod;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CMFCButton m_btnSave;
	CMFCButton m_btnCancel;
};
