#pragma once
#include "afxcmn.h"


// CYibaoSumReportDlg 对话框

class CYibaoSumReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYibaoSumReportDlg)

public:
	CYibaoSumReportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYibaoSumReportDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_YIBAO_SUM_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	void InitList();
	CFont m_font;
	CString m_strSQL;
};
