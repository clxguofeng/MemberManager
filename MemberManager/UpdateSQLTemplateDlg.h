#pragma once
#include "afxwin.h"


// CUpdateSQLTemplateDlg �Ի���

class CUpdateSQLTemplateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateSQLTemplateDlg)

public:
	CUpdateSQLTemplateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateSQLTemplateDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATE_SQL_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTitle;
	CEdit m_editSQL;
	CEdit m_editZiduan;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_strID, m_strTitle, m_strSQL, m_strZiduan, m_strZiduanWidth;
	CEdit m_editWidth;
};
