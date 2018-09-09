// UpdateYibaoBiaozhunDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateYibaoBiaozhunDlg.h"
#include "afxdialogex.h"


// CUpdateYibaoBiaozhunDlg 对话框

IMPLEMENT_DYNAMIC(CUpdateYibaoBiaozhunDlg, CDialogEx)

CUpdateYibaoBiaozhunDlg::CUpdateYibaoBiaozhunDlg(int iFlag, CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateYibaoBiaozhunDlg::IDD, pParent)
{
	m_iFlag = iFlag;
}

CUpdateYibaoBiaozhunDlg::~CUpdateYibaoBiaozhunDlg()
{
}

void CUpdateYibaoBiaozhunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_YEAR, m_combYear);
	DDX_Control(pDX, IDC_COMBO_STYLE2, m_combStyle);
	DDX_Control(pDX, IDC_EDIT_DIBAO, m_editMoney);
}


BEGIN_MESSAGE_MAP(CUpdateYibaoBiaozhunDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateYibaoBiaozhunDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdateYibaoBiaozhunDlg 消息处理程序


BOOL CUpdateYibaoBiaozhunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int iYear = 2010;
	CTime curTime = CTime::GetCurrentTime();
	for (int i = 0; i < 100; ++i)
	{
		CString strYear;
		strYear.Format("%d年", iYear+i);
		m_combYear.AddString(strYear);
	}

	int iCursel = curTime.GetYear() - iYear;
	m_combYear.SetCurSel(iCursel);
	m_combStyle.InsertString(0, "普通");
	m_combStyle.InsertString(1, "60岁以上");
	m_combStyle.InsertString(2, "A类低保");
	m_combStyle.InsertString(3, "B类低保");
	m_combStyle.InsertString(4, "C类低保");
	m_combStyle.InsertString(5, "C残疾");
	m_combStyle.InsertString(6, "已故离休配偶");
	m_combStyle.InsertString(7, "退伍军人");
	m_combStyle.SetCurSel(0);

	if (m_iFlag == 1)
	{
		SetWindowText("新增交费标准");
	}
	else
	{
		m_combStyle.EnableWindow(0);
		m_combYear.EnableWindow(0);
		m_combYear.SetCurSel(m_iYear-2010);
		m_combStyle.SetCurSel(m_iStyle-1);
		m_editMoney.SetWindowText(m_strMoney);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUpdateYibaoBiaozhunDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	m_editMoney.GetWindowText(m_strMoney);
	m_iYear = m_combYear.GetCurSel() + 2010;
	m_iStyle = m_combStyle.GetCurSel()+1;
	m_combStyle.GetWindowText(m_strStyle);
}
