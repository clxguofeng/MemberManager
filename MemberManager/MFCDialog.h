#pragma once


// CMFCDialog 对话框

class CMFCDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCDialog)

public:
	CMFCDialog(UINT uID, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMFCDialog();

// 对话框数据
	// enum { IDD = IDD_MFCDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
