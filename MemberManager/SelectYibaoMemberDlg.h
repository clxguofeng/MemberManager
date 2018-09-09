#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSelectYibaoMemberDlg �Ի���

class CSelectYibaoMemberDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CSelectYibaoMemberDlg)

public:
	CSelectYibaoMemberDlg(CString strName, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectYibaoMemberDlg();
	void Init();
	CFont m_font;
	CString m_strName;
	CString m_strCode;
	CString m_strPhone;
// �Ի�������
	enum { IDD = IDD_DIALOG_SELECT_YIBAO_MEMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	CEdit m_editName;
	CEdit m_editCode;
	afx_msg void OnBnClickedButtonSelect();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
