#pragma once


// CUpdatePeopleDlg �Ի���
// #include "MFCDialog.h"
#include "afxbutton.h"

class CUpdatePeopleDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUpdatePeopleDlg)

public:
	CUpdatePeopleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdatePeopleDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATEPEOPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strID;
	CString m_strName;
	CString m_strCode;
	CString m_strPhone;
	CString m_strDress;
	virtual BOOL OnInitDialog();
	BOOL UpdatePeople();
	afx_msg void OnBnClickedOk();
	CMFCButton m_btnSave;
	CMFCButton m_btnCancel;
};
