#pragma once

// #include "MFCDialog.h"
#include "afxbutton.h"
#include "afxcmn.h"
#include "afxwin.h"
// CExportExcelDlg 对话框

class CExportExcelDlg : public CMFCDialog//CDialogEx
{
	DECLARE_DYNAMIC(CExportExcelDlg)

public:
	CExportExcelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExportExcelDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXPORTEXCEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExport();
	void static SetColumInfo(_WorksheetPtr worksheet, CString strTitle, char cBeginColum, char cEndColum, vector<CString>& vecZiDuan);
	void static SetColumInfo(_WorksheetPtr worksheet, CString strTitle, char cBeginColum, char cEndColum, vector<CString>& vecZiDuan, vector<CString>& vecWidth);
	CMFCButton m_btnExport;
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	CFont m_font;
	void InitList();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editSQL;
	CEdit m_editFieldName;
	CEdit m_editTitle;
	void static ExportExcel(CString strSQL, CString strZiDuan, CString strTitle, CString strSheetname="", CString strWidth = "");
	void static ExportExcel(vector<SQLEXPORTSTRUCT>& vecSQLStruct);
	BOOL static ExportExcelFromDB(_WorksheetPtr worksheet,CString strSQL, CString strZiDuan, CString strTitle, CString strWidth = "");
	// CString m_strSQLData, m_strZiDuan, m_strTitle;
	CMFCButton m_btnAdd;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCertifyUpdate();
	afx_msg void OnCertifyDelete();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editWidth;
};
