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

// MemberManagerView.cpp: CMemberManagerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MemberManager.h"
#endif

#include "MemberManagerDoc.h"
#include "MemberManagerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMemberManagerView

IMPLEMENT_DYNCREATE(CMemberManagerView, CView)

BEGIN_MESSAGE_MAP(CMemberManagerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMemberManagerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMemberManagerView 构造/析构

CMemberManagerView::CMemberManagerView()
{
	ChildDlgInfo childdlginfo;
	childdlginfo.m_pDlg = 0;
	childdlginfo.m_uTemplate = IDD_DIALOG_MEMBERINFO;
	childdlginfo.m_strTitle = "居民信息";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_1_1;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_strTitle = "导入EXCEL";
	childdlginfo.m_uTemplate = IDD_DIALOG_EXCEL;
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_4_1;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_strTitle = "楼房人信息";
	childdlginfo.m_uTemplate = IDD_DIALOG_PEOPLE;
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_1_3;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_UPDATEEXCEL;
	childdlginfo.m_strTitle = "更新EXCEL";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_4_3;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_UPDATEDB;
	childdlginfo.m_strTitle = "更新数据库";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_4_4;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_EXPORTEXCEL;
	childdlginfo.m_strTitle = "导出EXCEL";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_4_2;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_YILIAO;
	childdlginfo.m_strTitle = "医疗保险登记";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_1_2;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_USERINFO;
	childdlginfo.m_strTitle = "用户";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_3_1;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_USERRIGHT;
	childdlginfo.m_strTitle = "权限";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_3_2;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_CHANGEPASSWORD;
	childdlginfo.m_strTitle = "修改密码";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_3_3;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_YANGLAOBUTIE;
	childdlginfo.m_strTitle = "养老保险补贴登记";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_1_4;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_EXPORTCERTIFY;
	childdlginfo.m_strTitle = "证明";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_1_5;
	m_vecDlg.push_back(childdlginfo);
	childdlginfo.m_uTemplate = IDD_DIALOG_YILIAO_JIAOFEIBIAOZHUN;
	childdlginfo.m_strTitle = "医疗保险收费标准";
	childdlginfo.m_iID = ID_SHORTCUTS_PANE_3_4;
	m_vecDlg.push_back(childdlginfo);
	iLastIndex = -1;

}

CMemberManagerView::~CMemberManagerView()
{
	int iSize = m_vecDlg.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (m_vecDlg[i].m_pDlg)
		{
			m_vecDlg[i].m_pDlg->DestroyWindow();
			delete m_vecDlg[i].m_pDlg;
			m_vecDlg[i].m_pDlg = NULL;
		}
	}
}

BOOL CMemberManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMemberManagerView 绘图

void CMemberManagerView::OnDraw(CDC* /*pDC*/)
{
	CMemberManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMemberManagerView 打印


void CMemberManagerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMemberManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMemberManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMemberManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMemberManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMemberManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMemberManagerView 诊断

#ifdef _DEBUG
void CMemberManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CMemberManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMemberManagerDoc* CMemberManagerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMemberManagerDoc)));
	return (CMemberManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMemberManagerView 消息处理程序
void CMemberManagerView::ActiveChildDlg(int iID)
{
	if (iLastIndex == iID)
		return;
	iLastIndex = iID;

	int iSize = m_vecDlg.size();
	CRect rc;
	GetClientRect(&rc);
	int iActiveIndex = 0;
	for (int i = 0; i < iSize; ++i)
	{
		if ((m_vecDlg[i].m_iID != iID))
		{
			if (m_vecDlg[i].m_pDlg)
			{
				m_vecDlg[i].m_pDlg->CloseWindow();
				m_vecDlg[i].m_pDlg->DestroyWindow();
				delete m_vecDlg[i].m_pDlg;
				m_vecDlg[i].m_pDlg = NULL;
			}
		}
		else
		{
			iActiveIndex = i;
		}
	}

	switch (iID)
	{
	case ID_SHORTCUTS_PANE_1_1:
		m_vecDlg[iActiveIndex].m_pDlg = new CMemberInfoDlg;
		break;
	case ID_SHORTCUTS_PANE_4_1:
		m_vecDlg[iActiveIndex].m_pDlg = new CExcelDlg;
		break;
	case ID_SHORTCUTS_PANE_1_3:
		m_vecDlg[iActiveIndex].m_pDlg = new CPeopleDlg;
		break;
	case ID_SHORTCUTS_PANE_4_3:
		m_vecDlg[iActiveIndex].m_pDlg = new CUpdateExcelDlg;
		break;
	case ID_SHORTCUTS_PANE_4_4:
		m_vecDlg[iActiveIndex].m_pDlg = new CUpdateDBDlg;
		break;
	case ID_SHORTCUTS_PANE_4_2:
		m_vecDlg[iActiveIndex].m_pDlg = new CExportExcelDlg;
		break;
	case ID_SHORTCUTS_PANE_1_2:
		m_vecDlg[iActiveIndex].m_pDlg = new CYiliaoDlg;
		break;
	case ID_SHORTCUTS_PANE_3_1:
		m_vecDlg[iActiveIndex].m_pDlg = new CUserInfoDlg;
		break;
	case ID_SHORTCUTS_PANE_3_2:
		m_vecDlg[iActiveIndex].m_pDlg = new CUserRightDlg;
		break;
	case ID_SHORTCUTS_PANE_3_3:
		m_vecDlg[iActiveIndex].m_pDlg = new CChangePasswordDlg;
		break;
	case ID_SHORTCUTS_PANE_1_4:
		m_vecDlg[iActiveIndex].m_pDlg = new CYaoLaoButieDlg;
		break;
	case ID_SHORTCUTS_PANE_1_5:
		m_vecDlg[iActiveIndex].m_pDlg = new CExportCertifyDlg;
		break;
	case ID_SHORTCUTS_PANE_3_4:
		m_vecDlg[iActiveIndex].m_pDlg = new CYibaoJiaofeiBiaoZhunDlg;
		break;
	default:
		m_vecDlg[iActiveIndex].m_pDlg = new CPeopleDlg;
		break;
	}

	CString strTitle = m_vecDlg[iActiveIndex].m_strTitle;
	CMainFrame* pframe = (CMainFrame*)AfxGetMainWnd();
	if (pframe)
	{
		pframe->SetTitle(strTitle);
		pframe->Invalidate(TRUE);
	}

	m_vecDlg[iActiveIndex].m_pDlg->Create(m_vecDlg[iActiveIndex].m_uTemplate, this);
	m_vecDlg[iActiveIndex].m_pDlg->MoveWindow(0, 0, rc.right, rc.bottom);
	m_vecDlg[iActiveIndex].m_pDlg->ShowWindow(SW_SHOW);
}

void CMemberManagerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	int iSize = m_vecDlg.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (m_vecDlg[i].m_pDlg)
		{
			m_vecDlg[i].m_pDlg->MoveWindow(0, 0, cx, cy);
			break;
		}
	}
}
