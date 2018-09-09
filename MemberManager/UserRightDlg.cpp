// UserRightDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UserRightDlg.h"
#include "afxdialogex.h"


// CUserRightDlg �Ի���

IMPLEMENT_DYNAMIC(CUserRightDlg, CMFCDialog)

CUserRightDlg::CUserRightDlg(CWnd* pParent /*=NULL*/)
	: CMFCDialog(CUserRightDlg::IDD, pParent)
{

}

CUserRightDlg::~CUserRightDlg()
{
}

void CUserRightDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_TREE_MODEL, m_Tree);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
}


BEGIN_MESSAGE_MAP(CUserRightDlg, CMFCDialog)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CUserRightDlg::OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUserRightDlg::OnBnClickedButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_TREE_MODEL, &CUserRightDlg::OnNMClickTreeModel)
END_MESSAGE_MAP()


// CUserRightDlg ��Ϣ�������


BOOL CUserRightDlg::PreTranslateMessage(MSG* pMsg)
{
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


BOOL CUserRightDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("�û���"), LVCFMT_LEFT, 200);

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
		_T("����"));

	m_List.SetFont(&m_font);

	m_Tree.ModifyStyle(TVS_CHECKBOXES, 0);
	m_Tree.ModifyStyle(0, TVS_CHECKBOXES);
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUserRightDlg::OnSize(UINT nType, int cx, int cy)
{
	CMFCDialog::OnSize(nType, cx, cy);

	if (m_List.m_hWnd)
		m_List.MoveWindow(10, 30, USERRIGHT_LIST_WIDTH, cy - 30 - 10);

	int iTreeX = 10 + USERRIGHT_LIST_WIDTH + 10;
	if (m_Tree.m_hWnd)
		m_Tree.MoveWindow(iTreeX, 80, cx - iTreeX - 10, cy - 80 - 10);

	if (m_btnSave.m_hWnd)
	{
		m_btnSave.MoveWindow(USERRIGHT_LIST_WIDTH + 20, 30, 100, 30);
	}
}

void CUserRightDlg::InitList()
{
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select userid,username from userlogin where username <> 'admin'");

		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// ��ȡ��������� 
			int iRow = 0;
			CString strRow;
			while (sql_row = mysql_fetch_row(result)) 
			{
				strRow = sql_row[0];
				m_List.InsertItem(iRow, sql_row[1]);
				m_List.SetItemData(iRow, atoi(strRow));
				++iRow;
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CUserRightDlg::Init()
{
	m_List.DeleteAllItems();
	InitList();
	InitTree();
}

void CUserRightDlg::InitTree()
{
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("SELECT modelid,modelname,modelparentid FROM systemmodel");

		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// ��ȡ��������� 
			int iRow = 0;
			CString strValue;
			while (sql_row = mysql_fetch_row(result)) 
			{
				strValue = sql_row[0];
				int iModelid = atoi(strValue);
				CString strModel = sql_row[1];
				strValue = sql_row[2];
				int iParentid = atoi(strValue);
				map<int, HTREEITEM>::iterator itTree = m_mapTree.find(iParentid);
				if (itTree != m_mapTree.end())
				{
					HTREEITEM hItem = m_Tree.InsertItem(strModel, itTree->second);
					m_mapTree.insert(map<int, HTREEITEM>::value_type(iModelid, hItem));
				}
				else
				{
					HTREEITEM hItem = m_Tree.InsertItem(strModel);
					m_mapTree.insert(map<int, HTREEITEM>::value_type(iModelid, hItem));
				}
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);

	map<int, HTREEITEM>::iterator it = m_mapTree.begin();
	for (; it != m_mapTree.end(); ++it)
	{
		m_Tree.Expand(it->second, TVE_EXPAND);
		if (m_setModelid.find(it->first) != m_setModelid.end())
		{
			m_Tree.SetCheck(it->second, TRUE);
		}
	}
}

void CUserRightDlg::SetCheckUserTree(int iUserid)
{
	m_setModelid.clear();
	GetModelId(iUserid);

	map<int, HTREEITEM>::iterator it = m_mapTree.begin();
	for (; it != m_mapTree.end(); ++it)
	{
		if (m_setModelid.find(it->first) != m_setModelid.end())
			m_Tree.SetCheck(it->second, TRUE);
		else
			m_Tree.SetCheck(it->second, FALSE);
	}
}

void CUserRightDlg::SetCheckAllTree(BOOL bState)
{
	map<int, HTREEITEM>::iterator it = m_mapTree.begin();
	for (; it != m_mapTree.end(); ++it)
	{
		m_Tree.SetCheck(it->second, bState);
	}
}

void CUserRightDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (LVIF_STATE == pNMLV->uChanged)
	// if ((LVIF_STATE == pNMLV->uChanged) && (pNMLV->uNewState & LVIS_SELECTED))
	{
		int iCount = m_List.GetSelectedCount();
		if (iCount == 1)
		{
			int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED);
			if (iSelect != -1)
				SetCheckUserTree(m_List.GetItemData(iSelect));
		}
		else
			SetCheckAllTree(FALSE);
	}
	*pResult = 0;
}

void CUserRightDlg::GetModelId(int iUserid)
{
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select modelid from memberroles where userid=%d",
			iUserid);

		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// ��ȡ��������� 
			while (sql_row = mysql_fetch_row(result)) 
			{
				CString strValue = sql_row[0];
				m_setModelid.insert(atoi(strValue));
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CUserRightDlg::OnBnClickedButtonSave()
{
	int iSelect = -1;
	int iCount = m_List.GetSelectedCount();
	if (iCount > 0)
	{
		if (AfxMessageBox("ȷ��������ѡ����û�Ȩ��?", MB_OKCANCEL) == IDCANCEL)
			return;
	}
	else
	{
		AfxMessageBox("��ѡ��һλ�û�����Ȩ��!");
		return;
	}

	while ((iSelect = m_List.GetNextItem(iSelect, LVIS_SELECTED)) != -1)
	{
		int iUserid = m_List.GetItemData(iSelect);
		if (UpdateUserModel(iUserid) == FALSE)
		{
			AfxMessageBox("����Ȩ��ʧ��!");
			break;
		}
	}
}

BOOL CUserRightDlg::UpdateUserModel(int iUserid)
{
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		CString strSQL;
		strSQL = "lock tables memberroles write";
		int res = mysql_query(&theApp.m_db, strSQL);
		if (res != 0)
		{
			mysql_close(&theApp.m_db);
			return FALSE;
		}

		strSQL.Format("delete from memberroles where userid=%d", iUserid);
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		res = mysql_query(&theApp.m_db, strSQL);
		if (res != 0)
		{
			mysql_close(&theApp.m_db);
			return FALSE;
		}
		map<int, HTREEITEM>::iterator it = m_mapTree.begin();
		for (; it != m_mapTree.end(); ++it)
		{
			if (m_Tree.GetCheck(it->second))
			{
				strSQL.Format("insert into memberroles(userid,modelid) values(%d,%d)", iUserid, it->first);
				int res = mysql_query(&theApp.m_db, strSQL);
				if (res != 0)
				{
					mysql_close(&theApp.m_db);
					return FALSE;
				}
			}
		}
		strSQL = "unlock tables";
		mysql_query(&theApp.m_db, strSQL);
	}
	mysql_close(&theApp.m_db);
	return TRUE;
}

void CUserRightDlg::SetCheckChildNodeState(HTREEITEM hItem, BOOL bState)
{
	HTREEITEM hNextItem = m_Tree.GetChildItem(hItem);
	while(hNextItem != NULL)
	{
		m_Tree.SetCheck(hNextItem, bState);
		hNextItem = m_Tree.GetNextSiblingItem(hNextItem);
	}
}

void CUserRightDlg::OnNMClickTreeModel(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	MapWindowPoints((CWnd*)&m_Tree, &pt, 1);

	UINT nflag = TVHT_ONITEM;
	HTREEITEM hItem = m_Tree.HitTest(pt, &nflag);
	if (hItem &&(nflag & TVHT_ONITEMSTATEICON))
	{        
		BOOL bChecked = !m_Tree.GetCheck(hItem);
		SetCheckChildNodeState(hItem, bChecked);
	}
	*pResult = 0;
}
