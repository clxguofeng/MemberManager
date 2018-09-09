// MFCDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
// #include "MFCDialog.h"
#include "afxdialogex.h"


// CMFCDialog �Ի���

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


// CMFCDialog ��Ϣ�������


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

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(afxGlobalData.clrBarFace);
		return afxGlobalData.brBarFace;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
