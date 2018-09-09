#pragma once
#include "afxcmn.h"
#include "afxbutton.h"


// CUserRightDlg 对话框

class CUserRightDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CUserRightDlg)

public:
	CUserRightDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserRightDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERRIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CFont m_font;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_List;
	void Init();
	CTreeCtrl m_Tree;
	void InitList();
	void InitTree();
	map<int, HTREEITEM> m_mapTree;
	void SetCheckUserTree(int iUserid);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	void GetModelId(int iUserid);
	set<int> m_setModelid;
	afx_msg void OnBnClickedButtonSave();
	CMFCButton m_btnSave;
	BOOL UpdateUserModel(int iUserid);
	void SetCheckAllTree(BOOL bState);
	void SetCheckChildNodeState(HTREEITEM hItem, BOOL bState);
	afx_msg void OnNMClickTreeModel(NMHDR *pNMHDR, LRESULT *pResult);
};
