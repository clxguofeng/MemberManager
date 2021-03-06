#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxbutton.h"


// CYibaoJiaofeiBiaoZhunDlg 对话框

class CYibaoJiaofeiBiaoZhunDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CYibaoJiaofeiBiaoZhunDlg)

public:
	CYibaoJiaofeiBiaoZhunDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CYibaoJiaofeiBiaoZhunDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_YILIAO_JIAOFEIBIAOZHUN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	CMFCButton m_btnSelect;
	CMFCButton m_btnAdd;
	CMFCButton m_btnUpdate;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_List;
	CComboBox m_combYear;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonUpdate();
	CMFCButton m_btnDelete;
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
