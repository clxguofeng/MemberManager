#pragma once
#include "afxwin.h"


// CUpdateSQLTemplateDlg 对话框

class CUpdateSQLTemplateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateSQLTemplateDlg)

public:
	CUpdateSQLTemplateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateSQLTemplateDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATE_SQL_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTitle;
	CEdit m_editSQL;
	CEdit m_editZiduan;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_strID, m_strTitle, m_strSQL, m_strZiduan, m_strZiduanWidth;
	CEdit m_editWidth;
};
