// ChangePasswordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "ChangePasswordDlg.h"
#include "afxdialogex.h"


// CChangePasswordDlg 对话框

IMPLEMENT_DYNAMIC(CChangePasswordDlg, CMFCDialog)

CChangePasswordDlg::CChangePasswordDlg(CWnd* pParent /*=NULL*/)
	: CMFCDialog(CChangePasswordDlg::IDD, pParent)
{

}

CChangePasswordDlg::~CChangePasswordDlg()
{
}

void CChangePasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_AGAIN, m_editAgain);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnChange);
}


BEGIN_MESSAGE_MAP(CChangePasswordDlg, CMFCDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CChangePasswordDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CChangePasswordDlg 消息处理程序


void CChangePasswordDlg::OnBnClickedButtonUpdate()
{
	CString strPassword, strEncrypt, strAgain;
	m_editPassword.GetWindowText(strPassword);
	m_editAgain.GetWindowText(strAgain);
	if (strPassword != strAgain)
	{
		AfxMessageBox("两次输入不同，请重新输入!");
		m_editPassword.SetFocus();
		return;
	}
	if (strPassword.IsEmpty() == FALSE)
	{
		EncryptString(strPassword, strEncrypt, ENCRYPT_STRING_USERPWD_KEY);
	}
	CString strSQL;
	strSQL.Format("update userlogin set userpassword='%s' where username='%s'", strEncrypt, theApp.m_strUser);
	if (ExecuteDBSQL(strSQL))
		AfxMessageBox("修改密码成功！");
	else
		AfxMessageBox("修改密码失败！");
}


BOOL CChangePasswordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //回车
			{
			}
			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	} 
	return CMFCDialog::PreTranslateMessage(pMsg);
}


BOOL CChangePasswordDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
