#pragma once


// CUpdatePeopleDlg 对话框
// #include "MFCDialog.h"
#include "afxbutton.h"

class CUpdatePeopleDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUpdatePeopleDlg)

public:
	CUpdatePeopleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdatePeopleDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATEPEOPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
