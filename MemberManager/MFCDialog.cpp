// MFCDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
// #include "MFCDialog.h"
#include "afxdialogex.h"


// CMFCDialog 对话框

IMPLEMENT_DYNAMIC(CMFCDialog, CDialogEx)

CMFCDialog::CMFCDialog(UINT uID, CWnd* pParent /*=NULL*/)
	// : CDialogEx(CMFCDialog::IDD, pParent)
	: CDialogEx(uID, pParent)
{

}

CMFCDialog::~CMFCDialog()
{
}

void CMFCDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMFCDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCDialog 消息处理程序


void CMFCDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(&rect, &afxGlobalData.brBarFace);
}


HBRUSH CMFCDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(afxGlobalData.clrBarFace);
		return afxGlobalData.brBarFace;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
