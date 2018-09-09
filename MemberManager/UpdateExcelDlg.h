#pragma once
#include "afxwin.h"
// #include "MFCDialog.h"
#include "afxbutton.h"

// CUpdateExcelDlg �Ի���

class CUpdateExcelDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUpdateExcelDlg)

public:
	CUpdateExcelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateExcelDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATEEXCEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
