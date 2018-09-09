// UpdateCertifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateCertifyDlg.h"
#include "afxdialogex.h"


// UpdateCertifyDlg 对话框

IMPLEMENT_DYNAMIC(UpdateCertifyDlg, CDialogEx)

UpdateCertifyDlg::UpdateCertifyDlg(int iMode, CWnd* pParent /*=NULL*/)
	: CDialogEx(UpdateCertifyDlg::IDD, pParent)
{
	m_iMode = iMode;
}

UpdateCertifyDlg::~UpdateCertifyDlg()
{
}

void UpdateCertifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
}


BEGIN_MESSAGE_MAP(UpdateCertifyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UpdateCertifyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// UpdateCertifyDlg 消息处理程序


void UpdateCertifyDlg::OnBnClickedOk()
{
	m_editName.GetWindowText(m_strName);
	m_editTitle.GetWindowText(m_strTitle);
	m_editData.GetWindowText(m_strData);
	m_strName.Trim();
	m_strTitle.Trim();
	m_strData.Trim();
	if (m_strName.IsEmpty() || m_strTitle.IsEmpty() || m_strData.IsEmpty())
	{
		AfxMessageBox("内容不能为空!");
		return;
	}
	if (m_iMode == 0)
	{
		CString strSQL;
		strSQL.Format("insert into certifytemplate(certifyname,certifytitle,certifydata) values('%s','%s','%s')", m_strName, m_strTitle, m_strData);
		if (ExecuteDBSQL(strSQL))
			CDialogEx::OnOK();
		else
			AfxMessageBox("新增失败!");
	}
	else
	{
		CString strSQL;
		strSQL.Format("update certifytemplate set certifyname='%s',certifytitle='%s',certifydata='%s' where certifyid=%s", m_strName, m_strTitle, m_strData, m_strID);
		if (ExecuteDBSQL(strSQL))
			CDialogEx::OnOK();
		else
			AfxMessageBox("新增失败!");
	}
}


BOOL UpdateCertifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_iMode == 1)
	{
		m_editName.SetWindowText(m_strName);
		m_editTitle.SetWindowText(m_strTitle);
		m_editData.SetWindowText(m_strData);
	}
	return TRUE;
}
