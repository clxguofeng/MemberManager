#pragma once


// CMFCDialog �Ի���

class CMFCDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCDialog)

public:
	CMFCDialog(UINT uID, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMFCDialog();

// �Ի�������
	// enum { IDD = IDD_MFCDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
