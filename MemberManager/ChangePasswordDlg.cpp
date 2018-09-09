// ChangePasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "ChangePasswordDlg.h"
#include "afxdialogex.h"


// CChangePasswordDlg �Ի���

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


// CChangePasswordDlg ��Ϣ�������


void CChangePasswordDlg::OnBnClickedButtonUpdate()
{
	CString strPassword, strEncrypt, strAgain;
	m_editPassword.GetWindowText(strPassword);
	m_editAgain.GetWindowText(strAgain);
	if (strPassword != strAgain)
	{
		AfxMessageBox("�������벻ͬ������������!");
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
		AfxMessageBox("�޸�����ɹ���");
	else
		AfxMessageBox("�޸�����ʧ�ܣ�");
}


BOOL CChangePasswordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //�س�
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
