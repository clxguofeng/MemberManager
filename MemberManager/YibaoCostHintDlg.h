#pragma once
#include "afxwin.h"


// CYibaoCostHintDlg �Ի���

class CYibaoCostHintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYibaoCostHintDlg)

public:
	CYibaoCostHintDlg(CString strBtnName, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYibaoCostHintDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_YIBAO_COST_HINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_strMemberList;
	CStatic m_staticHint;
	CString m_strBtnName;
	CButton m_btnOK;
};
