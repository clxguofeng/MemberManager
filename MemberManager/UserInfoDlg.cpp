// UserInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UserInfoDlg.h"
#include "afxdialogex.h"
#include "UserAddOrUpdateDlg.h"

// CUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUserInfoDlg, CMFCDialog)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CMFCDialog(CUserInfoDlg::IDD, pParent)
{

}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btnReset);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CMFCDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CUserInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUserInfoDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CUserInfoDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CUserInfoDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CUserInfoDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CUserInfoDlg 消息处理程序


void CUserInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CMFCDialog::OnSize(nType, cx, cy);
	if (m_List.m_hWnd)
		m_List.MoveWindow(10, 80, cx - 20, cy - 80 - 10);
}


BOOL CUserInfoDlg::PreTranslateMessage(MSG* pMsg)
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


BOOL CUserInfoDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 200);

	m_font.CreateFont(
		16,                        // nHeight  
		0,                         // nWidth  
		0,                         // nEscapement  
		0,                         // nOrientation  
		FW_THIN,                 // nWeight  
		FALSE,                     // bItalic  
		FALSE,                     // bUnderline  
		0,                         // cStrikeOut  
		ANSI_CHARSET,              // nCharSet  
		OUT_DEFAULT_PRECIS,        // nOutPrecision  
		CLIP_DEFAULT_PRECIS,       // nClipPrecision  
		DEFAULT_QUALITY,           // nQuality  
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily  
		_T("宋体"));

	m_List.SetFont(&m_font);
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUserInfoDlg::Init()
{
	m_List.DeleteAllItems();
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select userid,username from userlogin where username <> 'admin'");

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			int iRow = 0;
			CString strRow;
			while (sql_row = mysql_fetch_row(result)) 
			{
				strRow = sql_row[0];
				m_List.InsertItem(iRow, sql_row[1]);
				m_List.SetItemData(iRow, atoi(strRow));
				++iRow;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CUserInfoDlg::OnBnClickedButtonAdd()
{
	CUserAddOrUpdateDlg dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		Init();
	}
}


void CUserInfoDlg::OnBnClickedButtonUpdate()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		int iUserid = m_List.GetItemData(iSelect);
		CString strName = m_List.GetItemText(iSelect, 0);
		CUserAddOrUpdateDlg dlg(FALSE, iUserid, strName);
		if (dlg.DoModal() == IDOK)
		{
			Init();
		}
	}
}


void CUserInfoDlg::OnBnClickedButtonReset()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		int iUserid = m_List.GetItemData(iSelect);
		CString strName = m_List.GetItemText(iSelect, 0);
		CString strMsg;
		strMsg.Format("你确定重置用户名：%s的密码?", strName);
		if (AfxMessageBox(strMsg, MB_OKCANCEL) == IDOK)
		{
			CString strSQL;
			CString strDBPassword;
			EncryptString("123456", strDBPassword, ENCRYPT_STRING_USERPWD_KEY);

			strSQL.Format("update userlogin set userpassword = '%s' where userid=%d", strDBPassword, iUserid);
			if (ExecuteDBSQL(strSQL) == FALSE)
			{
				AfxMessageBox("重置密码失败!");
				return;
			}
		}
	}
}


void CUserInfoDlg::OnBnClickedButtonDelete()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		int iUserid = m_List.GetItemData(iSelect);
		CString strName = m_List.GetItemText(iSelect, 0);
		CString strMsg;
		strMsg.Format("你确定删除用户：%s?", strName);
		if (AfxMessageBox(strMsg, MB_OKCANCEL) == IDOK)
		{
			CString strSQL;
			strSQL.Format("delete from userlogin where userid=%d", iUserid);
			if (ExecuteDBSQL(strSQL) == FALSE)
			{
				AfxMessageBox("删除失败!");
				return;
			}
			else
			{
				CString strSQL;
				strSQL.Format("delete from memberroles where userid=%d", iUserid);
				ExecuteDBSQL(strSQL);
				Init();
			}
		}
	}
}


void CUserInfoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedButtonUpdate();
}
