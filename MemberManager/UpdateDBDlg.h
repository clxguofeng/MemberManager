#pragma once
#include "afxwin.h"
// #include "MFCDialog.h"
#include "afxbutton.h"

// CUpdateDBDlg 对话框

class CUpdateDBDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUpdateDBDlg)

public:
	CUpdateDBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateDBDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATEDB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editData;
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonFileSelect();
	void UpdateDB(_WorksheetPtr worksheet, CString strSQL, CString strWhere, CString strUpdate);
	CMFCButton m_btnUpdate;
	CMFCButton m_btnSelect;
	afx_msg void OnBnClickedButtonClean();
	BOOL GetMembers(vector<SimplePeopleInfo>& vecMembers);
	void UpdateMember(CString strCode, vector<CString>& vecPhone);
	BOOL DeleteShortPhone(vector<CString>& vecPhone);
	CMFCButton m_btnClearRepeat;
	virtual BOOL OnInitDialog();
};
