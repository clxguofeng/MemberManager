// YibaoCostHintDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "YibaoCostHintDlg.h"
#include "afxdialogex.h"


// CYibaoCostHintDlg 对话框

IMPLEMENT_DYNAMIC(CYibaoCostHintDlg, CDialogEx)

CYibaoCostHintDlg::CYibaoCostHintDlg(CString strBtnName, CWnd* pParent /*=NULL*/)
	: CDialogEx(CYibaoCostHintDlg::IDD, pParent)
{
	m_strBtnName = strBtnName;
}

CYibaoCostHintDlg::~CYibaoCostHintDlg()
{
}

void CYibaoCostHintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_staticHint);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CYibaoCostHintDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CYibaoCostHintDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CYibaoCostHintDlg 消息处理程序


void CYibaoCostHintDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CYibaoCostHintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_staticHint.SetWindowText(m_strMemberList);
	m_btnOK.SetWindowText(m_strBtnName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
