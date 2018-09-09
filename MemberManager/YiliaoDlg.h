#pragma once
#include "afxbutton.h"
// #include "MFCDialog.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "ExportExcelDlg.h"

// CYiliaoDlg 对话框

class CYiliaoDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CYiliaoDlg)

public:
	CYiliaoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYiliaoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_YILIAO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCButton m_SelectBtn;
	CMFCButton m_btnAdd;
	CListCtrl m_List;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonNew();
	virtual BOOL OnInitDialog();
	void InitCombo();
	CFont m_font;
	vector<YibaoStyle> m_vecYibaoStyle;
	vector<CString> m_vecUser;
	void Init();
	CComboBox m_cmbStyle;
	CEdit m_editSelect;
	CDateTimeCtrl m_dtEnd;
	CDateTimeCtrl m_dtBegin;
	CComboBox m_cmbDateStyle;
	vector<CString> m_vecComboStyle;
	CComboBox m_cmbYibaoStyle;
	afx_msg void OnBnClickedButtonSelect();
	void InitList();
	CString GetWhere(CString& strTitle);
	afx_msg void OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnYibaoUpdate();
	afx_msg void OnYibaoDelete();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMFCButton m_btnSelectExport;
	CMFCButton m_btnSumExport;
	afx_msg void OnBnClickedButtonSelectExport();
	afx_msg void OnBnClickedButtonSumExport();
	CComboBox m_cmbState;
	afx_msg void OnYibaoCancel();
	int m_iSel;
	CMFCButton m_btnExport;
	afx_msg void OnBnClickedButtonExport();
	CMFCButton m_btnSum;
	afx_msg void OnBnClickedButtonSum();
	afx_msg void OnBnClickedButtonRefresh();
	void InsertNewList(int iCount);
	CMFCButton m_btnRefresh;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void RefreshYibaoList();
	BOOL m_bChange;
	BOOL m_bRefresh;
	afx_msg void OnSelchangeComboDate();
	afx_msg void OnDatetimechangeDatetimeBegin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDatetimechangeDatetimeEnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeComboState();
	afx_msg void OnSelchangeComboYibaostyle();
	afx_msg void OnSelchangeComboStyle();
	afx_msg void OnChangeEditName();
	CButton m_checkUpdatetime;
	CComboBox m_cmbUser;
};
