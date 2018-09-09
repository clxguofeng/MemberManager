#pragma once
#include "afxcmn.h"
#include "afxbutton.h"


// CUserInfoDlg �Ի���

class CUserInfoDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_List;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CFont m_font;
	void Init();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonDelete();
	CMFCButton m_btnAdd;
	CMFCButton m_btnUpdate;
	CMFCButton m_btnDel;
	CMFCButton m_btnReset;
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
