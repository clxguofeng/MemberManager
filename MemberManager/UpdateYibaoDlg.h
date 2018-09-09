#pragma once
#include "afxwin.h"


// CUpdateYibaoDlg �Ի���

class CUpdateYibaoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateYibaoDlg)
public:
	CString m_strName, m_strCode, m_strPhone, m_strDibao;
	int m_iSel;
	vector<YibaoStyle> * m_pvecYibaoStyle;
public:
	CUpdateYibaoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateYibaoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATEYIBAO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editName;
	CEdit m_editCode;
	CEdit m_editPhone;
	CComboBox m_cmbStyle;
	virtual BOOL OnInitDialog();
	CEdit m_editDibao;
};
