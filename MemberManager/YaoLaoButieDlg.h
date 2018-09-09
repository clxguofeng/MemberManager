#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CYaoLaoButieDlg 对话框

class CYaoLaoButieDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYaoLaoButieDlg)

public:
	CYaoLaoButieDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYaoLaoButieDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_YANGLAOBUTIE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbStyle;
	virtual BOOL OnInitDialog();
	CComboBox m_cmbState;
	CComboBox m_cmbSelect;
	vector<CString> m_vecSelect;
	CString GetWhere();
	CDateTimeCtrl m_dtBegin;
	CDateTimeCtrl m_dtEnd;
	CEdit m_editSelect;
	CListCtrl m_List;
	CFont m_font;
	void Init();
};
