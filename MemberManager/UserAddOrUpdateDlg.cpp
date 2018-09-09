// UserAddOrUpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UserAddOrUpdateDlg.h"
#include "afxdialogex.h"


// CUserAddOrUpdateDlg �Ի���

IMPLEMENT_DYNAMIC(CUserAddOrUpdateDlg, CDialogEx)

CUserAddOrUpdateDlg::CUserAddOrUpdateDlg(BOOL bAdd, int iUserId, CString strUser, CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserAddOrUpdateDlg::IDD, pParent)
{
	m_bAdd = bAdd;
	m_strUser = strUser;
	m_iUserid = iUserId;
}

CUserAddOrUpdateDlg::~CUserAddOrUpdateDlg()
{
}

void CUserAddOrUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CUserAddOrUpdateDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserAddOrUpdateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserAddOrUpdateDlg ��Ϣ�������


BOOL CUserAddOrUpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_bAdd)
	{
		SetWindowText("����û�");
	}
	else
	{	
		SetWindowText("�޸��û�");
		m_editName.SetWindowText(m_strUser);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUserAddOrUpdateDlg::OnBnClickedOk()
{
	CString strSQL;
	CString strName;
	m_editName.GetWindowText(strName);
	strName.Trim();
	if (strName.IsEmpty())
	{
		AfxMessageBox("�û�������Ϊ��!");
		return;
	}
	if (m_bAdd)
	{
		strSQL.Format("select count(userid) FROM userlogin where username='%s'", strName);
		if (CheckExistRecord(strSQL))
		{
			AfxMessageBox("�û����Ѿ�����!");
			return;
		}
		CString strDBPassword;
		EncryptString("123456", strDBPassword, ENCRYPT_STRING_USERPWD_KEY);

		strSQL.Format("insert into userlogin(username,userpassword,status) values('%s','%s',1)", strName, strDBPassword);
		if (ExecuteDBSQL(strSQL) == FALSE)
		{
			AfxMessageBox("���ʧ��!");
			return;
		}
		else
			AfxMessageBox("��ӳɹ�!");
	}
	else
	{
		strSQL.Format("update userlogin set username = '%s' where userid=%d", strName,m_iUserid);
		if (ExecuteDBSQL(strSQL) == FALSE)
		{
			AfxMessageBox("�޸�ʧ��!");
			return;
		}
		else
			AfxMessageBox("�޸ĳɹ�!");
	}
	CDialogEx::OnOK();
}
