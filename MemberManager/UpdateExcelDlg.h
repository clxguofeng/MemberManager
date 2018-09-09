#pragma once
#include "afxwin.h"
// #include "MFCDialog.h"
#include "afxbutton.h"

// CUpdateExcelDlg 对话框

class CUpdateExcelDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUpdateExcelDlg)

public:
	CUpdateExcelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateExcelDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATEEXCEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFileSelect();
	afx_msg void OnBnClickedButtonUpdate();
	void UpdateExcel(_WorksheetPtr worksheet, CString strSQL, CString strWhere, CString strUpdate);
	void GetZiDuanValue(CString strSQL, vector<CString>& vecZiDuan);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editData;
	CMFCButton m_btnUpdate;
	CMFCButton m_btnSelect;
	virtual BOOL OnInitDialog();
};
