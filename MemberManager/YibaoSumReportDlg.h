#pragma once
#include "afxcmn.h"


// CYibaoSumReportDlg �Ի���

class CYibaoSumReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYibaoSumReportDlg)

public:
	CYibaoSumReportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYibaoSumReportDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_YIBAO_SUM_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	void InitList();
	CFont m_font;
	CString m_strSQL;
};
