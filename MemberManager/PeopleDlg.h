#pragma once
#include "afxvslistbox.h"
#include "afxwin.h"
#include "afxcmn.h"
// #include "MFCDialog.h"

// CPeopleDlg 对话框

class CPeopleDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CPeopleDlg)

public:
	CPeopleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeopleDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PEOPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	CComboBox m_comboBox;
	CEdit m_editFile;
	CEdit m_editSelect;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CMFCListCtrl m_List;
	void InitCombo();
	void InitList(CString strSQL);
	void GetHouseInfo(_WorksheetPtr worksheet, vector<GroupInfo>& vecGroup);
	void GetPeopleInfo(_WorksheetPtr worksheet, vector<GroupInfo>& vecGroup);
	vector<CString> m_vecCombo;
	vector<GroupInfo>::iterator FindGroupIter(CString strGroupID, vector<GroupInfo>& vecGroup);
	void GetHouseInfo(_WorksheetPtr worksheet, HouseInfo& info, int iRow);
	void GetPeople(_WorksheetPtr worksheet, PeopleInfo& peopleinfo, int iRow);
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonImport();
	void ImportDB(vector<GroupInfo>& vecGroup);
	afx_msg void OnBnClickedButtonFind();
	
	void SelectPeople(CString strKey, CString strSelect);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuPeopleFamily();
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	// afx_msg void OnPaint();
	CMFCButton m_btnSelect;
	CMFCButton m_btnBrowser;
	CMFCButton m_btnImport;
};
