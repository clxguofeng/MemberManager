// UserLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UserLoginDlg.h"
#include "afxdialogex.h"


// CUserLoginDlg 对话框

IMPLEMENT_DYNAMIC(CUserLoginDlg, CMFCDialog)

CUserLoginDlg::CUserLoginDlg(BOOL bSave, CWnd* pParent /*=NULL*/)
	: CMFCDialog(CUserLoginDlg::IDD, pParent)
{
	m_bSave = bSave;
	CString strPassword = theApp.m_strPassword;
	if (theApp.m_strPassword.IsEmpty() == FALSE)
		DecryptString(strPassword, theApp.m_strPassword);
}

CUserLoginDlg::~CUserLoginDlg()
{
}

void CUserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IP, m_editIP);
	DDX_Control(pDX, IDC_EDIT_USER, m_editUser);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_CHECK_SAVE, m_btnSave);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CUserLoginDlg, CMFCDialog)
	ON_BN_CLICKED(IDOK, &CUserLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserLoginDlg 消息处理程序


BOOL CUserLoginDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_editIP.SetWindowText(theApp.m_strIP);
	m_editUser.SetWindowText(theApp.m_strUser);
	m_editPassword.SetWindowText(theApp.m_strPassword);
	if (m_bSave)
		m_btnSave.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CUserLoginDlg::CheckUserLogin(CString strSQL)
{
	BOOL bRet = FALSE;
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  
		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");

		// 查询
		int res = mysql_query(&theApp.m_db, strSQL);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				int iNum = atoi(sql_row[0]);
				if (iNum > 0)
					bRet = TRUE;
				else
				{
					AfxMessageBox("用户名或者密码不正确!");
					m_editUser.SetFocus();
				}
				break;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}
	else
	{
		AfxMessageBox("连接服务器失败!");
		m_editIP.SetFocus();
	}
		
	mysql_close(&theApp.m_db);
	return bRet;
}

void CUserLoginDlg::OnBnClickedOk()
{
	m_editIP.GetWindowText(theApp.m_strIP);
	m_editUser.GetWindowText(theApp.m_strUser);
	m_editPassword.GetWindowText(theApp.m_strPassword);

	theApp.m_strIP.Trim();
	theApp.m_strUser.Trim();
	theApp.m_strPassword.Trim();
	if (theApp.m_strIP.IsEmpty())
	{
		AfxMessageBox("IP地址不能为空!");
		m_editIP.SetFocus();
		return;
	}
	if (theApp.m_strUser.IsEmpty())
	{
		AfxMessageBox("用户名不能为空!");
		m_editUser.SetFocus();
		return;
	}

	CString strSQL;
	CString strDBPassword;
	EncryptString(theApp.m_strPassword, strDBPassword, ENCRYPT_STRING_USERPWD_KEY);
	strSQL.Format("select count(userid) FROM userlogin where username='%s' and userpassword='%s'", theApp.m_strUser, strDBPassword);

	if (CheckUserLogin(strSQL) == FALSE)
	{
		return;
	}
	/*
	if (CheckExistRecord(strSQL) == FALSE)
	{
		AfxMessageBox("用户名或者密码不正确!");
		return;
	}
	*/
	char szApp[256];
	GetModuleFileName(NULL, szApp, 256);
	char *pFind = strrchr(szApp, '\\');
	*pFind = 0;
	strcat_s(szApp, "\\config.ini");

	WritePrivateProfileString("server", "ip", theApp.m_strIP, szApp);
	WritePrivateProfileString("server", "user", theApp.m_strUser, szApp);

	if (m_btnSave.GetCheck())
	{
		CString strPassword;
		EncryptString(theApp.m_strPassword, strPassword);
		WritePrivateProfileString("server", "password", strPassword, szApp);
		WritePrivateProfileString("server", "save", "1", szApp);
	}
	else
	{
		WritePrivateProfileString("server", "password", "", szApp);
		WritePrivateProfileString("server", "save", "0", szApp);
	}


	CMFCDialog::OnOK();
}

BOOL CheckExistRecord(CString strSQL)
{
	BOOL bRet = FALSE;
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  
		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");

		// 查询
		int res = mysql_query(&theApp.m_db, strSQL);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				int iNum = atoi(sql_row[0]);
				if (iNum > 0)
					bRet = TRUE;

				break;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}
	mysql_close(&theApp.m_db);
	return bRet;
}
