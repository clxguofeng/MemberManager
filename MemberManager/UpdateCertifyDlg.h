#pragma once
#include "afxwin.h"


// UpdateCertifyDlg 对话框

class UpdateCertifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateCertifyDlg)

public:
	UpdateCertifyDlg(int iMode, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UpdateCertifyDlg();
	CString m_strID, m_strName, m_strTitle, m_strData;

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATECERTIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editName;
	CEdit m_editTitle;
	CEdit m_editData;
	int m_iMode;
	virtual BOOL OnInitDialog();
};
