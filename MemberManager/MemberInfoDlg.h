#pragma once
#include "afxcmn.h"
#include "afxwin.h"
// #include "MFCDialog.h"

// CMemberInfoDlg 对话框
 
class CMemberInfoDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CMemberInfoDlg)

public:
	CMemberInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMemberInfoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEMBERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CMFCListCtrl m_List;
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void SelectMemberInfo(CString strKey, CString strSelect);
	afx_msg void OnBnClickedButtonSelect();
	CEdit m_editName;
	afx_msg void OnBnClickedButtonImport();
	BOOL ImportFile(CString strFileName);
	static BOOL CheckMemberExist(CString strCode, CString& strOldPhone);
	static BOOL CheckMemberNameExist(CString strName);
	static BOOL InsertMember(CString strName, CString strCode, CString strPhone, CString strComment, CString strStyle);
	BOOL UpdateMember(CString strName, CString strCode, CString strNewPhone, CString strOldPhone);
	BOOL UpdatePhoneString(CString& strNew, const CString& strOld);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void InitList(CString strSQL);
	void InitCombo();
	vector<CString> m_vecCombo;
private:
	CFont m_font;
public:
	afx_msg void OnDblclkListMemberinfo(NMHDR *pNMHDR, LRESULT *pResult);
	// afx_msg void OnPaint();
	// afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnRclickListMemberinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditCopy();

	CComboBox m_combo;
	CMFCButton m_btnSelect;
	CMFCButton m_btnImport;
	CMFCButton m_btnNew;
	afx_msg void OnEditDelete();
};
