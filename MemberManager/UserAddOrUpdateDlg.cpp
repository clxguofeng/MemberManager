// UserAddOrUpdateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UserAddOrUpdateDlg.h"
#include "afxdialogex.h"


// CUserAddOrUpdateDlg 对话框

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


// CUserAddOrUpdateDlg 消息处理程序


BOOL CUserAddOrUpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_bAdd)
	{
		SetWindowText("添加用户");
	}
	else
	{	
		SetWindowText("修改用户");
		m_editName.SetWindowText(m_strUser);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUserAddOrUpdateDlg::OnBnClickedOk()
{
	CString strSQL;
	CString strName;
	m_editName.GetWindowText(strName);
	strName.Trim();
	if (strName.IsEmpty())
	{
		AfxMessageBox("用户名不能为空!");
		return;
	}
	if (m_bAdd)
	{
		strSQL.Format("select count(userid) FROM userlogin where username='%s'", strName);
		if (CheckExistRecord(strSQL))
		{
			AfxMessageBox("用户名已经存在!");
			return;
		}
		CString strDBPassword;
		EncryptString("123456", strDBPassword, ENCRYPT_STRING_USERPWD_KEY);

		strSQL.Format("insert into userlogin(username,userpassword,status) values('%s','%s',1)", strName, strDBPassword);
		if (ExecuteDBSQL(strSQL) == FALSE)
		{
			AfxMessageBox("添加失败!");
			return;
		}
		else
			AfxMessageBox("添加成功!");
	}
	else
	{
		strSQL.Format("update userlogin set username = '%s' where userid=%d", strName,m_iUserid);
		if (ExecuteDBSQL(strSQL) == FALSE)
		{
			AfxMessageBox("修改失败!");
			return;
		}
		else
			AfxMessageBox("修改成功!");
	}
	CDialogEx::OnOK();
}
