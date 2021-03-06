// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MemberManagerView.h: CMemberManagerView 类的接口
//

#pragma once

#include "MemberManagerDoc.h"
#include "MemberInfoDlg.h"
#include "ExcelDlg.h"
#include "PeopleDlg.h"
#include "UpdateExcelDlg.h"
#include "UpdateDBDlg.h"
#include "ExportExcelDlg.h"
#include "YiliaoDlg.h"
#include "UserInfoDlg.h"
#include "UserRightDlg.h"
#include "ChangePasswordDlg.h"
#include "YaoLaoButieDlg.h"
#include "ExportCertifyDlg.h"
#include "CYibaoJiaofeiBiaoZhunDlg.h"

typedef struct CHILDDLGINFO
{
	int m_iID;
	UINT	m_uTemplate;
	CDialogEx* m_pDlg;
	CString m_strTitle;
} ChildDlgInfo;

class CMemberManagerView : public CView
{
protected: // 仅从序列化创建
	CMemberManagerView();
	DECLARE_DYNCREATE(CMemberManagerView)

// 特性
public:
	CMemberManagerDoc* GetDocument() const;

public:
	vector<ChildDlgInfo> m_vecDlg;
	void ActiveChildDlg(int iID);
	int iLastIndex;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMemberManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // MemberManagerView.cpp 中的调试版本
inline CMemberManagerDoc* CMemberManagerView::GetDocument() const
   { return reinterpret_cast<CMemberManagerDoc*>(m_pDocument); }
#endif

