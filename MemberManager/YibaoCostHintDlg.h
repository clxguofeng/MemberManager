#pragma once
#include "afxwin.h"


// CYibaoCostHintDlg 对话框

class CYibaoCostHintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYibaoCostHintDlg)

public:
	CYibaoCostHintDlg(CString strBtnName, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYibaoCostHintDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_YIBAO_COST_HINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_strMemberList;
	CStatic m_staticHint;
	CString m_strBtnName;
	CButton m_btnOK;
};
