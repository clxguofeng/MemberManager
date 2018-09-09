#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "YiliaoDlg.h"

// CAddYibaoDlg 对话框

class CAddYibaoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddYibaoDlg)

public:
	CAddYibaoDlg(CYiliaoDlg* pDlg, vector<YibaoStyle>* pVecYibaoStyle, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddYibaoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD_YIBAO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CYiliaoDlg* m_pDlg;
	CFont m_font;
	virtual BOOL OnInitDialog();
	void Init();
	vector<YibaoStyle>* m_pvecYibaoStyle;
	CComboBox m_cmbStyle;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL CheckValid();
	void AddMember();
	CEdit m_editName;
	CEdit m_editCode;
	CEdit m_editPhone;
	CString m_strName;
	CString m_strCode;
	CString m_strPhone;
	CString m_strDibao;
	CString m_strCost;
	int m_iSel;
	CButton m_btnAdd;
	CEdit m_editDibao;
	afx_msg void OnBnClickedButtonAdd();
	// BOOL CheckCurYearExistYibao(CString strSelect);
	BOOL CheckListExist();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult);
	void SumCost();
	afx_msg void OnYibaoDelete();
	afx_msg void OnYibaoUpdate();
	CStatic m_staticSum;
	afx_msg void OnBnClickedOk();
	void EmptyAllControl();
	BOOL InsertYibaoCost(int& iYibaodanju, int& iYibaoid);
	void GetYibaoMsg(int& iDanju, int& iYibaoid);
	void CheckYear();
	afx_msg void OnEnKillfocusEditCode();
};
