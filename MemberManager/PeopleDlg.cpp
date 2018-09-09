// PeopleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "PeopleDlg.h"
#include "afxdialogex.h"
#include "UpdatePeopleDlg.h"

// CPeopleDlg 对话框

IMPLEMENT_DYNAMIC(CPeopleDlg, CMFCDialog)

CPeopleDlg::CPeopleDlg(CWnd* pParent /*=NULL*/)
	// : CDialogEx(CPeopleDlg::IDD, pParent)
	: CMFCDialog(IDD, pParent)
{

}

CPeopleDlg::~CPeopleDlg()
{
}

void CPeopleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PEOPLE, m_comboBox);
	DDX_Control(pDX, IDC_EDIT_SELECT, m_editSelect);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_BUTTON_FIND, m_btnSelect);
	DDX_Control(pDX, IDC_BUTTON_FILE, m_btnBrowser);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btnImport);
}


BEGIN_MESSAGE_MAP(CPeopleDlg, CMFCDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CPeopleDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CPeopleDlg::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CPeopleDlg::OnBnClickedButtonFind)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CPeopleDlg::OnRclickList)
	ON_COMMAND(ID_MENU_PEOPLE_FAMILY, &CPeopleDlg::OnMenuPeopleFamily)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CPeopleDlg::OnDblclkList)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPeopleDlg 消息处理程序


BOOL CPeopleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);  
	m_List.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, _T("性别"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(3, _T("身份证"), LVCFMT_LEFT, 180);
	m_List.InsertColumn(4, _T("地址"), LVCFMT_LEFT, 200);
	m_List.InsertColumn(5, _T("电话"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(6, _T("关系"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(7, _T("房间ID"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(8, _T("房间号"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(9, _T("楼栋ID"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(10, _T("楼栋名称"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(11, _T("网格名称"), LVCFMT_LEFT, 100);
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
	InitCombo();
	return TRUE;
}

void CPeopleDlg::InitCombo()
{
	m_comboBox.InsertString(0, "姓名");
	m_comboBox.InsertString(1, "身份证");
	m_comboBox.InsertString(2, "地址");
	m_comboBox.InsertString(3, "电话");
	m_comboBox.InsertString(4, "楼栋名称");
	m_comboBox.InsertString(5, "网格名称");
	m_vecCombo.push_back("peoplename");
	m_vecCombo.push_back("code");
	m_vecCombo.push_back("dress");
	m_vecCombo.push_back("phone");
	m_vecCombo.push_back("groupsimplename");
	m_vecCombo.push_back("grid");
	m_comboBox.SetCurSel(0);
}

void CPeopleDlg::InitList(CString strSQL)
{
	mysql_init(&theApp.m_db);
	DBPeopleInfo dbinfo;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		// 查询
		int res = mysql_query(&theApp.m_db, strSQL);
		int iLine = 0;
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				// dbinfo.strNumber = sql_row[0];
				m_List.InsertItem(iLine, sql_row[0]);
				m_List.SetItemText(iLine, 1, sql_row[1]);
				m_List.SetItemText(iLine, 2, sql_row[2]);
				m_List.SetItemText(iLine, 3, sql_row[4]);
				m_List.SetItemText(iLine, 4, sql_row[3]);
				m_List.SetItemText(iLine, 5, sql_row[5]);
				m_List.SetItemText(iLine, 6, sql_row[6]);
				m_List.SetItemText(iLine, 7, sql_row[9]);
				m_List.SetItemText(iLine, 8, sql_row[8]);
				m_List.SetItemText(iLine, 9, sql_row[7]);
				m_List.SetItemText(iLine, 10, sql_row[10]);
				m_List.SetItemText(iLine, 11, sql_row[11]);
				++iLine;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CPeopleDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_List.m_hWnd)
		m_List.MoveWindow(10, 50, cx - 20, cy - 50 - 10);
}


void CPeopleDlg::OnBnClickedButtonFile()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDIT_FILE, cFileDlg.GetPathName());
		return;
	}
}

void CPeopleDlg::ImportDB(vector<GroupInfo>& vecGroup)
{
	mysql_init(&theApp.m_db);
	CString strInsert;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		mysql_query(&theApp.m_db, "SET NAMES GBK");

		int iSize = vecGroup.size();
		int i;
		for (i = 0; i < iSize; ++i)
		{
			strInsert.Format("insert into groupinfo(groupid,groupsimplename,upfloor,downfloor,unitnumber,unithousenumber,grid) values('%s','%s',%d,%d,%d,%d,'%s')", 
				vecGroup[i].strGroupID, vecGroup[i].strSimpleName,vecGroup[i].iUpFloor,vecGroup[i].iDownFloor,vecGroup[i].iUnit,vecGroup[i].iUnitQuantity,vecGroup[i].strGrid);

			// 查询
			int res = mysql_query(&theApp.m_db, strInsert);
		}

		CString strDress = "岳西县天堂镇城西社区";
		CString strValue;
		HouseInfo* pHouseInfo;
		GroupInfo* pGroupInfo;
		PeopleInfo* pPeopleInfo;
		for (i = 0; i < iSize; ++i)
		{
			int iHouseSize = vecGroup[i].vecHouseInfo.size();

			for (int j = 0; j < iHouseSize; ++j)
			{
				int iPeopleSize = vecGroup[i].vecHouseInfo[j].vecPeoples.size();
				for (int k = 0; k < iPeopleSize; ++k)
				{
					pPeopleInfo = &vecGroup[i].vecHouseInfo[j].vecPeoples[k];
					pHouseInfo = &vecGroup[i].vecHouseInfo[j];
					pGroupInfo = &vecGroup[i];
					strValue.Format("%s%s%s", strDress,pGroupInfo->strSimpleName,pHouseInfo->strHouse);
					strInsert.Format("insert into peopleinfo(peoplename,sex,dress,code,phone,role,groupid,housename,houseid) values('%s','%s','%s','%s','%s','%s','%s','%s','%s')", 
						pPeopleInfo->strName,
						pPeopleInfo->strSex,
						strValue,
						pPeopleInfo->strNumber,
						pPeopleInfo->strPhone,
						pPeopleInfo->strRole,
						pGroupInfo->strGroupID,
						pHouseInfo->strHouse,
						pHouseInfo->strHouseID);
					
					// 查询
					int res = mysql_query(&theApp.m_db, strInsert);
				}
			}
		}
	}


	mysql_close(&theApp.m_db);

}

void CPeopleDlg::OnBnClickedButtonImport()
{
	CString strFileName;
	m_editFile.GetWindowText(strFileName);

	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");

	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Open(strFileName.GetBuffer(0));
	SheetsPtr worksheets = pBook->GetWorksheets();

	// 目标文件的第一个sheet指针
	_WorksheetPtr workgroupsheet = worksheets->GetItem((_variant_t)(LONG)1);
	_WorksheetPtr workhousesheet = worksheets->GetItem((_variant_t)(LONG)2);
	_WorksheetPtr workpeoplesheet = worksheets->GetItem((_variant_t)(LONG)3);

	vector<GroupInfo> vecGroup;
	GetGroupInfo(workgroupsheet, vecGroup, FALSE);
	// GetHouseInfo(workhousesheet, vecGroup);
	GetPeopleInfo(workpeoplesheet, vecGroup);
	ImportDB(vecGroup);
	AfxMessageBox("完成!");
	pBook->Close();
	pBooks->Close();
}

vector<GroupInfo>::iterator CPeopleDlg::FindGroupIter(CString strGroupID, vector<GroupInfo>& vecGroup)
{
	vector<GroupInfo>::iterator it = vecGroup.begin();
	for (; it != vecGroup.end(); ++it)
	{
		if (strGroupID == it->strSimpleName)
		{
			return it;
		}
	}
	return it;
}

void CPeopleDlg::GetHouseInfo(_WorksheetPtr worksheet, vector<GroupInfo>& vecGroup)
{
	HouseInfo info;
	vector<GroupInfo>::iterator it;
	CString strLastGroup;
	BOOL bBegin = TRUE;
	for (int i = 2; ;++i)
	{
		CString strGroup = GetRangeString(worksheet, 'F', i);
		if (strGroup.IsEmpty())
			break;

		if (bBegin)
		{
			it = FindGroupIter(strGroup, vecGroup);
			if (it == vecGroup.end())
				continue;
			strLastGroup = strGroup;
			bBegin = FALSE;
		}

		if (strGroup != strLastGroup)
		{
			it = FindGroupIter(strGroup, vecGroup);
			if (it == vecGroup.end())
				continue;

			strLastGroup = it->strName;
		}

		info.strHouseID = GetRangeString(worksheet, 'A', i);
		info.iUnit = atoi(GetRangeString(worksheet, 'C', i));
		info.iFloor = atoi(GetRangeString(worksheet, 'D', i));
		info.strHouse = GetRangeString(worksheet, 'E', i);
		it->vecHouseInfo.push_back(info);
	}
}

void CPeopleDlg::GetPeople(_WorksheetPtr worksheet, PeopleInfo& peopleinfo, int iRow)
{
	peopleinfo.strName = GetRangeString(worksheet, 'H', iRow);
	peopleinfo.strNumber = GetRangeString(worksheet, 'G', iRow);
	peopleinfo.strSex = GetRangeString(worksheet, 'I', iRow);
	peopleinfo.strPhone = GetRangeString(worksheet, 'M', iRow);
	peopleinfo.strRole = GetRangeString(worksheet, 'O', iRow);
}

void CPeopleDlg::GetPeopleInfo(_WorksheetPtr worksheet, vector<GroupInfo>& vecGroup)
{
	vector<GroupInfo>::iterator it;
	vector<HouseInfo>::iterator itHouse;
	PeopleInfo peopleinfo;
	HouseInfo houseinfo;
	CString strLastGroup;
	CString strHouseID, strLastHouseID;
	BOOL bBegin = TRUE;
	int i;
	for (i = 2; ;++i)
	{
		CString strGroup = GetRangeString(worksheet, 'E', i);
		if (strGroup.IsEmpty())
			break;

		if (bBegin)
		{
			it = FindGroupIter(strGroup, vecGroup);
			if (it == vecGroup.end())
				continue;
			strLastGroup = strGroup;
		}

		if (strGroup != strLastGroup)
		{
			if (it != vecGroup.end())
			{
				GetHouseInfo(worksheet, houseinfo, i-1);
				it->vecHouseInfo.push_back(houseinfo);
				houseinfo.vecPeoples.clear();
			}
			it = FindGroupIter(strGroup, vecGroup);
			if (it == vecGroup.end())
				continue;

			strLastGroup = strGroup;
			bBegin = TRUE;
		}

		strHouseID = GetRangeString(worksheet, 'C', i);
		if (bBegin)
		{
			GetPeople(worksheet, peopleinfo, i);
			houseinfo.vecPeoples.push_back(peopleinfo);
			strLastHouseID = strHouseID;
			bBegin = FALSE;
		}
		else
		{
			if (strHouseID == strLastHouseID)
			{
				GetPeople(worksheet, peopleinfo, i);
				houseinfo.vecPeoples.push_back(peopleinfo);
			}
			else
			{
				GetHouseInfo(worksheet, houseinfo, i-1);
				it->vecHouseInfo.push_back(houseinfo);
				houseinfo.vecPeoples.clear();
				strLastHouseID = strHouseID;
				GetPeople(worksheet, peopleinfo, i);
				houseinfo.vecPeoples.push_back(peopleinfo);
			}
		}
	}

	if ((bBegin == FALSE) && (it != vecGroup.end()))
	{
		GetHouseInfo(worksheet, houseinfo, i-1);
		it->vecHouseInfo.push_back(houseinfo);
	}
}

void CPeopleDlg::GetHouseInfo(_WorksheetPtr worksheet, HouseInfo& info, int iRow)
{
	info.strHouseID = GetRangeString(worksheet, 'C', iRow);
	info.strHouse = GetRangeString(worksheet, 'F', iRow);
}

void CPeopleDlg::OnBnClickedButtonFind()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_comboBox.GetCurSel();
	CString strSelect;
	m_editSelect.GetWindowText(strSelect);
	SelectPeople(m_vecCombo[iIndex], strSelect);
}

void CPeopleDlg::SelectPeople(CString strKey, CString strSelect)
{
	m_List.DeleteAllItems();
	CString strSQL;
	strSQL = "select peopleid,peoplename,sex,dress,code,phone,role,peopleinfo.groupid,housename,houseid,groupsimplename,grid from peopleinfo left join groupinfo on peopleinfo.groupid=groupinfo.groupid  where 1=1 ";
	strSelect.TrimLeft();
	strSelect.TrimRight();
	if (strSelect.IsEmpty() == FALSE)
	{
		CString strWhere;
		strWhere.Format(" and %s like '%%%s%%'", strKey, strSelect);
		strSQL += strWhere;
	}
	InitList(strSQL);
}

BOOL CPeopleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //回车
			{
				if (pMsg->hwnd == m_editSelect.m_hWnd)
				{
					OnBnClickedButtonFind();
				}
			}
			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPeopleDlg::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CPoint point;
		GetCursorPos(&point);
		CMenu menu;
		menu.LoadMenu(IDR_POPUP_PEOPLE);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y,this);
	}
}


void CPeopleDlg::OnMenuPeopleFamily()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	CString strTemp;
	if (iSelect == -1)
		return;

	CString strHouseid = m_List.GetItemText(iSelect, 7);

	m_List.DeleteAllItems();

	//////////////////////////////////////////////////////////////////////////
	CString strSQL;
	strSQL = "select peopleid,peoplename,sex,dress,code,phone,role,peopleinfo.groupid,housename,houseid,groupsimplename,grid from peopleinfo left join groupinfo on peopleinfo.groupid=groupinfo.groupid  where 1=1 ";
	CString strWhere;
	strWhere.Format(" and houseid = '%s'", strHouseid);
	strSQL += strWhere;
	InitList(strSQL);
	//////////////////////////////////////////////////////////////////////////
}


void CPeopleDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int iCode = pNMItemActivate->iItem;
	if (iCode >= 0)
	{
		CUpdatePeopleDlg dlg;
		dlg.m_strID = m_List.GetItemText(iCode, 0);
		dlg.m_strName = m_List.GetItemText(iCode, 1);
		dlg.m_strCode = m_List.GetItemText(iCode, 3);
		dlg.m_strPhone = m_List.GetItemText(iCode, 5);
		dlg.m_strDress = m_List.GetItemText(iCode, 4);
		if (dlg.DoModal() == IDOK)
		{
			m_List.SetItemText(iCode, 1, dlg.m_strName);
			m_List.SetItemText(iCode, 3, dlg.m_strCode);
			m_List.SetItemText(iCode, 5, dlg.m_strPhone);
			m_List.SetItemText(iCode, 4, dlg.m_strDress);
		}
	}
}

/*
void CPeopleDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(&rect, &afxGlobalData.brBarFace);
}
*/