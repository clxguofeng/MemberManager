// UpdateSQLTemplateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateSQLTemplateDlg.h"
#include "afxdialogex.h"


// CUpdateSQLTemplateDlg 对话框

IMPLEMENT_DYNAMIC(CUpdateSQLTemplateDlg, CDialogEx)

CUpdateSQLTemplateDlg::CUpdateSQLTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateSQLTemplateDlg::IDD, pParent)
{

}

CUpdateSQLTemplateDlg::~CUpdateSQLTemplateDlg()
{
}

void CUpdateSQLTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editSQL);
	DDX_Control(pDX, IDC_EDIT_ZIDUAN, m_editZiduan);
	DDX_Control(pDX, IDC_EDIT_ZIDUAN2, m_editWidth);
}


BEGIN_MESSAGE_MAP(CUpdateSQLTemplateDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateSQLTemplateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdateSQLTemplateDlg 消息处理程序


BOOL CUpdateSQLTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_editTitle.SetWindowText(m_strTitle);
	m_editSQL.SetWindowText(m_strSQL);
	m_editZiduan.SetWindowText(m_strZiduan);
	m_editWidth.SetWindowText(m_strZiduanWidth);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUpdateSQLTemplateDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editTitle.GetWindowText(m_strTitle);
	m_editSQL.GetWindowText(m_strSQL);
	m_editZiduan.GetWindowText(m_strZiduan);
	m_editWidth.GetWindowText(m_strZiduanWidth);

	m_strTitle.Trim();
	m_strSQL.Trim();
	m_strZiduan.Trim();
	m_strSQL.Replace("'", "''");
	if (m_strTitle.IsEmpty() || m_strSQL.IsEmpty() || m_strZiduan.IsEmpty())
	{
		AfxMessageBox("信息不能为空!");
		return;
	}

	CString strSQL;
	if (m_strID.IsEmpty())
	{
		strSQL.Format("insert into exportsql(sqlname,sqlstring,fieldname,fieldwidth) values('%s','%s','%s','%s')", m_strTitle, m_strSQL, m_strZiduan, m_strZiduanWidth);
		if (ExecuteDBSQL(strSQL))
			CDialogEx::OnOK();
		else
			AfxMessageBox("新增失败!");
	}
	else
	{
		strSQL.Format("update exportsql set sqlname='%s',sqlstring='%s',fieldname='%s',fieldwidth='%s' where sqlid=%s", 
			m_strTitle, m_strSQL, m_strZiduan, m_strZiduanWidth, m_strID);

		if (ExecuteDBSQL(strSQL))
			CDialogEx::OnOK();
		else
			AfxMessageBox("修改失败!");
	}
}
