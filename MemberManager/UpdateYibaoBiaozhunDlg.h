#pragma once
#include "afxwin.h"


// CUpdateYibaoBiaozhunDlg �Ի���

class CUpdateYibaoBiaozhunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateYibaoBiaozhunDlg)

public:
	CUpdateYibaoBiaozhunDlg(int iFlag = 0, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateYibaoBiaozhunDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATE_BIAOZHUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	int m_iFlag;
public:
	virtual BOOL OnInitDialog();
	CComboBox m_combYear;
	CComboBox m_combStyle;
	CEdit m_editMoney;
	int m_iYear, m_iStyle;
	CString m_strMoney;
	CString m_strStyle;
	afx_msg void OnBnClickedOk();
};
