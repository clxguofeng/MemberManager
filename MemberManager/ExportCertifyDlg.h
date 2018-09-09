#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxbutton.h"


// CExportCertifyDlg 对话框

class CExportCertifyDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CExportCertifyDlg)

public:
	CExportCertifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExportCertifyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXPORTCERTIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editName1;
	CEdit m_editCode1;
	CEdit m_editName2;
	CEdit m_editName3;
	CEdit m_editCode2;
	CEdit m_editCode3;
	virtual BOOL OnInitDialog();
	CEdit m_editTitle;
	CListCtrl m_List;
	CEdit m_editData;
	CFont m_font;
	void InitList(CString strSQL);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAssign();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnCertifyUpdate();
	afx_msg void OnCertifyDelete();
	afx_msg void OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult);
	CMFCButton m_btnAssign;
	CEdit m_editSelect;
	CMFCButton m_btnSelect;
	afx_msg void OnBnClickedButtonSelect();
	CMFCButton m_btnExport;
	CMFCButton m_btnAdd;
	CButton m_CertifyCheck;
	CDateTimeCtrl m_date1;
	CDateTimeCtrl m_date2;
	CDateTimeCtrl m_date3;
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
