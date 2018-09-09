// UpdatePeopleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdatePeopleDlg.h"
#include "afxdialogex.h"


// CUpdatePeopleDlg 对话框

IMPLEMENT_DYNAMIC(CUpdatePeopleDlg, CMFCDialog)

CUpdatePeopleDlg::CUpdatePeopleDlg(CWnd* pParent /*=NULL*/)
	// : CDialogEx(CUpdatePeopleDlg::IDD, pParent)
	: CMFCDialog(IDD, pParent)
{

}

CUpdatePeopleDlg::~CUpdatePeopleDlg()
{
}

void CUpdatePeopleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnSave);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CUpdatePeopleDlg, CMFCDialog)
	ON_BN_CLICKED(IDOK, &CUpdatePeopleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdatePeopleDlg 消息处理程序


BOOL CUpdatePeopleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_NAME, m_strName);
	SetDlgItemText(IDC_EDIT_CODE, m_strCode);
	SetDlgItemText(IDC_EDIT_PHONE, m_strPhone);
	SetDlgItemText(IDC_EDIT_DRESS, m_strDress);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUpdatePeopleDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_NAME, m_strName);
	GetDlgItemText(IDC_EDIT_CODE, m_strCode);
	GetDlgItemText(IDC_EDIT_PHONE, m_strPhone);
	GetDlgItemText(IDC_EDIT_DRESS, m_strDress);
	if (UpdatePeople())
		CDialogEx::OnOK();
	else
		AfxMessageBox("保存失败!");
}

BOOL CUpdatePeopleDlg::UpdatePeople()
{
	CString strSQL;
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		m_strName.TrimLeft();
		m_strName.TrimRight();
		m_strCode.TrimLeft();
		m_strCode.TrimRight();
		m_strPhone.TrimLeft();
		m_strPhone.TrimRight();
		m_strDress.TrimLeft();
		m_strDress.TrimRight();
		strSQL.Format("update peopleinfo set peoplename='%s',dress='%s',code='%s',phone='%s' where peopleid=%s",
			m_strName, m_strDress, m_strCode, m_strPhone, m_strID);
		// (membername,membercode,phone) values('%s','%s','%s')", strName, strCode, strPhone);
		// 查询
		int res = mysql_query(&theApp.m_db, strSQL);
		if (res == 0)
		{
			mysql_close(&theApp.m_db);
			return TRUE;
		}
	}
	mysql_close(&theApp.m_db);
	return FALSE;
}