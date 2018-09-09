#pragma once
#include "afxwin.h"


// CUpdateYibaoBiaozhunDlg 对话框

class CUpdateYibaoBiaozhunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateYibaoBiaozhunDlg)

public:
	CUpdateYibaoBiaozhunDlg(int iFlag = 0, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateYibaoBiaozhunDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATE_BIAOZHUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_iFlag;
public:
	virtual BOOL OnInitDialog();
	CComboBox m_combYear;
	CComboBox m_combStyle;
	CEdit m_editMoney;
	int m_iYear, m_iStyle;
	CString m_strMoney;
	CString m_strStyle;
	afx_msg void OnBnClickedOk();
};
