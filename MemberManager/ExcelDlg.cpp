// ExcelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "ExcelDlg.h"
#include "afxdialogex.h"


// CExcelDlg 对话框

IMPLEMENT_DYNAMIC(CExcelDlg, CMFCDialog)

CExcelDlg::CExcelDlg(CWnd* pParent /*=NULL*/)
	// : CDialogEx(CExcelDlg::IDD, pParent)
	:CMFCDialog(IDD, pParent)
{
}

CExcelDlg::~CExcelDlg()
{
}

void CExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_EXCEL, m_progress);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_BUTTON_CHECK, m_btnCheckFromDB);
	DDX_Control(pDX, IDC_BUTTON_CHECK_FORMAT, m_btnCheckFormat);
	DDX_Control(pDX, IDC_BUTTON_SOURCE, m_btnBrowserSource);
	DDX_Control(pDX, IDC_BUTTON_DES, m_btnBrowserDes);
	DDX_Control(pDX, IDC_STATIC_SOURCE, m_staticSource);
}


BEGIN_MESSAGE_MAP(CExcelDlg, CMFCDialog)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CExcelDlg::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, &CExcelDlg::OnBnClickedButtonSource)
	ON_BN_CLICKED(IDC_BUTTON_DES, &CExcelDlg::OnBnClickedButtonDes)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CExcelDlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_FORMAT, &CExcelDlg::OnBnClickedButtonCheckFormat)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CExcelDlg 消息处理程序


void CExcelDlg::OnBnClickedButtonImport()
{
	CString strSource, strDes;
	GetDlgItemText(IDC_EDIT_SOURCE, strSource);
	GetDlgItemText(IDC_EDIT_DES, strDes);
	strSource.TrimLeft();
	strSource.TrimRight();
	strDes.TrimLeft();
	strDes.TrimRight();

	if (strSource.IsEmpty() || strDes.IsEmpty())
	{
		AfxMessageBox("文件名不能为空");
		return;
	}
	ImportExcel(strSource, strDes);
}

// 获取楼的信息
void GetGroupInfo(_WorksheetPtr worksheet, vector<GroupInfo>& vecGroup, BOOL bState)
{
	GroupInfo info;

	for (int i = 2; ;++i)
	{
		info.strGroupID = GetRangeString(worksheet, 'A', i);
		if (info.strGroupID.IsEmpty())
			break;

		info.strSimpleName = GetRangeString(worksheet, 'B', i);

		info.strName = GetRangeString(worksheet, 'C', i);

		info.iUpFloor = atoi(GetRangeString(worksheet, 'D', i));

		info.iDownFloor = atoi(GetRangeString(worksheet, 'E', i));

		info.iUnit = atoi(GetRangeString(worksheet, 'F', i));

		info.strGrid = GetRangeString(worksheet, 'J', i);

		info.iState = atoi(GetRangeString(worksheet, 'K', i));

		info.iUnitQuantity = atoi(GetRangeString(worksheet, 'G', i));

		info.iPos = i;

		if (bState == FALSE)
			vecGroup.push_back(info);
		else if (info.iState == 1)
			vecGroup.push_back(info);
		
	}
}

int CExcelDlg::GetBeginPutInfoPos(_WorksheetPtr worksheet)
{
	RangePtr rangeName;
	CString strRange, strName;
	int i = 2;
	for (; ;++i)
	{
		strName = GetRangeString(worksheet, 'A', i);
		if (strName.IsEmpty())
		{
			break;
		}

	}
	return i;
}

CString GetRangeString(_WorksheetPtr worksheet, char cColumn, int iRow)
{
	CString strRange;
	strRange.Format("%c%d", cColumn, iRow);
	RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	strRange = (LPCTSTR)(_bstr_t)(rangeName->GetValue2());
	strRange.TrimLeft();
	strRange.TrimRight();
	return strRange;
}

void PutRangeString(_WorksheetPtr worksheet, CString strValue, char cColumn, int iRow)
{
	CString strRange;
	strRange.Format("%c%d", cColumn, iRow);
	RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->PutValue2(strValue.GetBuffer(0));
}
void CExcelDlg::GetPeopleinfo(_WorksheetPtr worksourcesheet, int iRow, PeopleInfo& peopleinfo)
{
	peopleinfo.strName = GetRangeString(worksourcesheet, 'C', iRow);

	peopleinfo.strRole = GetRangeString(worksourcesheet, 'D', iRow);

	peopleinfo.strSex = GetRangeString(worksourcesheet, 'E', iRow);

	peopleinfo.strNumber = GetRangeString(worksourcesheet, 'F', iRow);

	peopleinfo.strPhone = GetRangeString(worksourcesheet, 'O', iRow);
}

RangePtr CExcelDlg::GetMergerAreaRange(_WorksheetPtr worksheet, char cColumn, int iRow)
{
	CString strRange;
	strRange.Format("%c%d", cColumn, iRow);
	RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	return rangeName->GetMergeArea();
}

void CExcelDlg::GetHouseInfo(_WorksheetPtr worksheet, RangePtr rangeName, HouseInfo& houseinfo, GroupInfo& GroupInfo, int iHouseNumber)
{
	houseinfo.strHouseID.Format("%s-%d", GroupInfo.strGroupID, iHouseNumber);
	houseinfo.iHouseNumber = iHouseNumber;
	houseinfo.strHouse = GetRangeString(worksheet, 'B', rangeName->Row);
}

CString CExcelDlg::GetNumber(CString strValue, int iMin)
{
	int iFirst, iLast, iLen, iLoop;
	CString strTemp;
	iLen = strValue.GetLength();
	BOOL bFind = FALSE;
	while ((iFirst = strValue.FindOneOf("0123456789")) != -1)
	{
		iLast = iFirst;
		iLoop = iFirst + 1;
		for (; iLoop < iLen; ++iLoop)
		{
			if ((strValue[iLoop] >= '0') && (strValue[iLoop] <= '9'))
			{
				iLast = iLoop;
			}
			else
				break;
		}
		strTemp = strValue.Mid(iFirst, iLast-iFirst+1);
		if (strTemp.GetLength() >= iMin)
		{
			strValue = strTemp;
			bFind = TRUE;
			break;
		}
		else
		{
			if (iLoop == (iLen-1))
				break;
			iFirst = iLoop;
			strValue = strValue.Mid(iFirst);
			// strValue = strValue.Right(iLen-iFirst);
		}
	}
	if (bFind == FALSE)
	{
		strValue.Empty();
	}
	return strValue;
}

void CExcelDlg::OperHouseName(vector<GroupInfo>::iterator it)
{
	BOOL bNull = TRUE;
	vector<HouseInfo>::iterator itInfo = it->vecHouseInfo.begin();
	for (; itInfo != it->vecHouseInfo.end(); ++itInfo)
	{
		if (itInfo->strHouse.IsEmpty() == FALSE)
		{
			bNull = FALSE;
			break;
		}
	}

	if (bNull == FALSE)
	{
		int iMaxFloor = 1;
		for (itInfo = it->vecHouseInfo.begin(); itInfo != it->vecHouseInfo.end(); ++itInfo)
		{
			itInfo->strHouse = GetNumber(itInfo->strHouse, 3);
			int iLen = itInfo->strHouse.GetLength();
			if (iLen > 0)
			{
				if (iLen == 3)
					itInfo->iFloor = atoi(itInfo->strHouse.Mid(0, 1));
				else if (iLen == 4)
					itInfo->iFloor = atoi(itInfo->strHouse.Mid(0, 2));
				else
					itInfo->iFloor = 1;

				if (iMaxFloor < itInfo->iFloor)
					iMaxFloor = itInfo->iFloor;
				
				itInfo->strHouse += "室";
			}
			else
				itInfo->iFloor = 1;
			// 房间所在的单元需要以后更新
			itInfo->iUnit = 1;
		}
		it->iUpFloor = iMaxFloor;
	}
	else
	{
		for (itInfo = it->vecHouseInfo.begin(); itInfo != it->vecHouseInfo.end(); ++itInfo)
		{
			itInfo->strHouse.Format("%d号", itInfo->iHouseNumber);
			itInfo->iUnit = 1;
			itInfo->iFloor = 1;
		}
		it->iUpFloor = 1;
	}
}

void CExcelDlg::CheckHouseinfo(vector<GroupInfo>::iterator it)
{
	OperHouseName(it);
	sort(it->vecHouseInfo.begin(), it->vecHouseInfo.end(), HouseNumberLess());
}

vector<GroupInfo>::iterator CExcelDlg::GetGroupInterator(vector<GroupInfo>& vecGroup, CString strValue)
{
	vector<GroupInfo>::iterator itFind = vecGroup.begin();
	for (; itFind != vecGroup.end(); ++itFind)
	{
		if (itFind->strSimpleName  == strValue)
			break;
	}
	return itFind;
}

void CExcelDlg::GetAllPeopleinfo(_WorksheetPtr worksourcesheet, vector<GroupInfo>& vecGroup)
{
	int iHouseNumber;
	PeopleInfo peopleinfo;
	HouseInfo houseinfo;
	BOOL bBegin = FALSE;
	RangePtr AreaRangeBegin;
	vector<GroupInfo>::iterator itGroup = vecGroup.end();
	for (int iRow = 4; ; ++iRow)
	{
		CString strName = GetRangeString(worksourcesheet, 'A', iRow);
		if (strName.IsEmpty())
		{
			break;
		}
		else
		{
			GetPeopleinfo(worksourcesheet, iRow, peopleinfo);
			if (peopleinfo.strName.IsEmpty())
				continue;

			if ((itGroup == vecGroup.end()) || (itGroup->strSimpleName != strName))
			{
				if (itGroup != vecGroup.end())
				{
					GetHouseInfo(worksourcesheet, AreaRangeBegin, houseinfo, *itGroup, iHouseNumber);
					itGroup->vecHouseInfo.push_back(houseinfo);
					houseinfo.vecPeoples.clear();
				}
				bBegin = FALSE;
				itGroup = GetGroupInterator(vecGroup, strName);
				if (itGroup == vecGroup.end())
					continue;
				iHouseNumber = 1;
			}

			if (bBegin == FALSE)
			{
				houseinfo.vecPeoples.push_back(peopleinfo);
				bBegin = TRUE;
				// 取得第一个B列的合并单元格的指针
				AreaRangeBegin = GetMergerAreaRange(worksourcesheet, 'B', iRow);
			}
			else 
			{
				RangePtr AreaRange = GetMergerAreaRange(worksourcesheet, 'B', iRow);
				if (AreaRangeBegin->Row == AreaRange->Row)
				{
					houseinfo.vecPeoples.push_back(peopleinfo);
				}
				else
				{
					// 将家庭房屋信息插入数组
					GetHouseInfo(worksourcesheet, AreaRangeBegin, houseinfo, *itGroup, iHouseNumber);
					itGroup->vecHouseInfo.push_back(houseinfo);
					houseinfo.vecPeoples.clear();
					houseinfo.vecPeoples.push_back(peopleinfo);
					AreaRangeBegin = AreaRange;
					++iHouseNumber;
				}
			}
		}
	}

	if (bBegin && (itGroup != vecGroup.end()))
	{
		GetHouseInfo(worksourcesheet, AreaRangeBegin, houseinfo, *itGroup, iHouseNumber);
		itGroup->vecHouseInfo.push_back(houseinfo);
	}
}

void CExcelDlg::PutGroupInfo(_WorksheetPtr worksheet, vector<GroupInfo>::iterator it)
{
	CString strValue;
	if (it->iUpFloor == 1)
	{
		strValue.Format("%d", it->vecHouseInfo.size());
		PutRangeString(worksheet, strValue, 'G', it->iPos);
	}
	else
	{
		PutRangeString(worksheet, "2", 'G', it->iPos);
	}
	strValue.Format("%d", it->iUpFloor);
	PutRangeString(worksheet, strValue, 'D', it->iPos);
}

void CExcelDlg::PutHousePeopleInfo(vector<GroupInfo>& vecGroup, _WorksheetPtr workbuildsheet, _WorksheetPtr workhousesheet, _WorksheetPtr workpeoplesheet, _WorksheetPtr worksourcesheet)
{
	int iPeoplePos = GetBeginPutInfoPos(workpeoplesheet);
	int iHousePos = GetBeginPutInfoPos(workhousesheet);
	int iOrignPeoplePos = iPeoplePos;
	int iOrignHousePos = iHousePos;

	RangePtr rangeName;
	CString strRange;
	CString strName;
	PeopleInfo peopleinfo;
	m_progress.ShowWindow(SW_NORMAL);

	int iSize = vecGroup.size();
	m_progress.SetRange(1, 10000);
	m_progress.SetPos(0);
	int iProgress = 0;
	GetAllPeopleinfo(worksourcesheet, vecGroup);

	for (vector<GroupInfo>::iterator it = vecGroup.begin(); it != vecGroup.end(); ++it)
	{
		CheckHouseinfo(it);
		PutPeopleInfo(workpeoplesheet, it, iPeoplePos);
		PutHouseInfo(workhousesheet, it, iHousePos);
		PutGroupInfo(workbuildsheet, it);
		++iProgress;
		m_progress.SetPos(10000*iProgress/iSize);
	}

	SetBorderProperty(workpeoplesheet, 20, 'P', iOrignPeoplePos, iPeoplePos-1);
	SetBorderProperty(workhousesheet, 20, 'F', iOrignHousePos, iHousePos-1);
	AfxMessageBox("完成！");
}

void CExcelDlg::SetSourceState(_WorksheetPtr workhousesheet, vector<GroupInfo>& vecGroup)
{
	for (vector<GroupInfo>::iterator it = vecGroup.begin(); it != vecGroup.end(); ++it)
	{
		PutRangeString(workhousesheet, "2", 'K', it->iPos);
	}
}

void CExcelDlg::SetBorderProperty(_WorksheetPtr worksheet, int iHeight, char cEndColumn, int iBeginPos, int iEndPos)
{
	CString strRange;
	strRange.Format("%d:%d", iBeginPos, iEndPos);
	RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->RowHeight = 20;

	strRange.Format("A%d:%C%d", iBeginPos, cEndColumn, iEndPos);
	rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->Borders->PutColor(RGB(0, 0, 0));

}

void CExcelDlg::PutPeopleInfo(_WorksheetPtr worksheet, vector<GroupInfo>::iterator itGroup, /*vector<HouseInfo>& vecInfo,*/ int& iPos)
{
	CString strAddress;
	// for (vector<HouseInfo>::iterator it = vecInfo.begin(); it != vecInfo.end(); ++it)
	for (vector<HouseInfo>::iterator it = itGroup->vecHouseInfo.begin(); it != itGroup->vecHouseInfo.end(); ++it)
	{
		for (vector<PeopleInfo>::iterator itPeople = it->vecPeoples.begin(); itPeople != it->vecPeoples.end(); ++itPeople)
		{
			PutRangeString(worksheet, "城西社区居委会", 'A', iPos);
			PutRangeString(worksheet, itGroup->strGrid, 'B', iPos);
			PutRangeString(worksheet, it->strHouseID, 'C', iPos);
			strAddress = "岳西县天堂镇城西社区";
			strAddress += itGroup->strSimpleName;
			strAddress += it->strHouse;
			PutRangeString(worksheet, strAddress, 'D', iPos);
			PutRangeString(worksheet, itGroup->strSimpleName, 'E', iPos);
			PutRangeString(worksheet, it->strHouse, 'F', iPos);
			PutRangeString(worksheet, itPeople->strNumber, 'G', iPos);
			PutRangeString(worksheet, itPeople->strName, 'H', iPos);
			PutRangeString(worksheet, itPeople->strSex, 'I', iPos);
			PutRangeString(worksheet, "汉族", 'J', iPos);
			PutRangeString(worksheet, strAddress, 'L', iPos);
			PutRangeString(worksheet, itPeople->strPhone, 'M', iPos);
			if (itPeople->strRole == "户主")
				PutRangeString(worksheet, "是", 'N', iPos);
			else
				PutRangeString(worksheet, "否", 'N', iPos);
			PutRangeString(worksheet, itPeople->strRole, 'O', iPos);
			PutRangeString(worksheet, "常住人口", 'P', iPos);
			++iPos;
		}
	}
}

void CExcelDlg::PutHouseInfo(_WorksheetPtr worksheet, vector<GroupInfo>::iterator itGroup, /*vector<HouseInfo>& vecInfo,*/int& iPos)
{
	CString strValue;
	for (vector<HouseInfo>::iterator it = itGroup->vecHouseInfo.begin(); it != itGroup->vecHouseInfo.end(); ++it)
	{
		PutRangeString(worksheet, it->strHouseID, 'A', iPos);
		PutRangeString(worksheet, itGroup->strGroupID, 'B', iPos);
		strValue.Format("%d", it->iUnit);
		PutRangeString(worksheet, strValue, 'C', iPos);
		strValue.Format("%d", it->iFloor);
		PutRangeString(worksheet, strValue, 'D', iPos);
		PutRangeString(worksheet, it->strHouse, 'E', iPos);
		PutRangeString(worksheet, itGroup->strSimpleName, 'F', iPos);
		++iPos;
	}
}

void CExcelDlg::ImportExcel(CString strSource, CString strDes)
{
	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");

	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBookSource = pBooks->Open(strSource.GetBuffer(0));
	_WorkbookPtr pBookDes = pBooks->Open(strDes.GetBuffer(0));
	SheetsPtr worksheetssource = pBookSource->GetWorksheets();
	SheetsPtr worksheetsdes = pBookDes->GetWorksheets();

	// 目标文件的第一个sheet指针
	_WorksheetPtr workbuildsheet = worksheetsdes->GetItem((_variant_t)(LONG)1);
	_WorksheetPtr workhousesheet = worksheetsdes->GetItem((_variant_t)(LONG)2);
	_WorksheetPtr workpeoplesheet = worksheetsdes->GetItem((_variant_t)(LONG)3);
	_WorksheetPtr worksourcesheet = worksheetssource->GetItem((_variant_t)(LONG)1);

	vector<GroupInfo> vecGroup;
	GetGroupInfo(workbuildsheet, vecGroup, TRUE);

	PutHousePeopleInfo(vecGroup, workbuildsheet, workhousesheet, workpeoplesheet, worksourcesheet);

	SetSourceState(workbuildsheet, vecGroup);

	m_progress.ShowWindow(SW_HIDE);

	pBookDes->Save();
	pBookSource->Close();
	pBookDes->Close();
	pBooks->Close();
}

void CExcelDlg::OnBnClickedButtonSource()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDOK)
	{
		// ImportFile(cFileDlg.GetPathName());
		SetDlgItemText(IDC_EDIT_SOURCE, cFileDlg.GetPathName());
		return;
	}
}


void CExcelDlg::OnBnClickedButtonDes()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDIT_DES, cFileDlg.GetPathName());
		return;
	}
}


BOOL CExcelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_progress.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CExcelDlg::ImportPeopleinfo(SimplePeopleInfo& peopleinfo, _WorksheetPtr worksheet, int i)
{
	peopleinfo.strName = GetRangeString(worksheet, 'H', i);
	peopleinfo.iRow = i;
	peopleinfo.strNumber = GetRangeString(worksheet, 'G', i);
	peopleinfo.strPhone = GetRangeString(worksheet, 'M', i);
}

void CExcelDlg::GetSimpleHouseinfo(_WorksheetPtr worksheet, vector<SimpleHouseInfo>& vecHouseInfo)
{
	CString strValue;
	SimplePeopleInfo peopleinfo;
	SimpleHouseInfo houseinfo;
	CString  strLastHouseid;

	BOOL bFirst = TRUE;
	CString strHouseid, strGroup;
	for (int i = 2; ;++i)
	{
		strHouseid = GetRangeString(worksheet, 'C', i);
		if (strHouseid.IsEmpty())
			break;

		strGroup = GetRangeString(worksheet, 'E', i);

		if (bFirst)
		{
			strLastHouseid = strHouseid;
			ImportPeopleinfo(peopleinfo, worksheet, i);
			houseinfo.strGroup = strGroup;
			houseinfo.strHouseID = strHouseid;
			houseinfo.vecPeoples.push_back(peopleinfo);
			bFirst = FALSE;
		}
		else
		{
			if (strHouseid == strLastHouseid)
			{
				ImportPeopleinfo(peopleinfo, worksheet, i);
				houseinfo.vecPeoples.push_back(peopleinfo);
			}
			else
			{
				vecHouseInfo.push_back(houseinfo);
				strLastHouseid = strHouseid;
				houseinfo.vecPeoples.clear();
				ImportPeopleinfo(peopleinfo, worksheet, i);
				houseinfo.strGroup = strGroup;
				houseinfo.strHouseID = strHouseid;
				houseinfo.vecPeoples.push_back(peopleinfo);		
			}
		}
	}

	if (bFirst == FALSE)
	{
		vecHouseInfo.push_back(houseinfo);
	}
}

void CExcelDlg::GetPeopleDBInfo(CString strName, vector<DBPeopleInfo>& vecDBPeople)
{
	mysql_init(&theApp.m_db);
	DBPeopleInfo dbinfo;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select membercode, phone from memberinfo where membername = '%s'", strName);

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				dbinfo.strNumber = sql_row[0];
				if (dbinfo.strNumber.IsEmpty())
					continue;

				dbinfo.strPhone = sql_row[1];
				vecDBPeople.push_back(dbinfo);
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

CString CExcelDlg::GetSinglePhone(CString strPhone)
{
	CString strValue;
	int iLen = strPhone.GetLength();
	BOOL bFind = FALSE;
	
	char *pFind = new char[iLen+1];
	char *pBegin = pFind;
	char *pBuff;
	strcpy_s(pFind, iLen+1, strPhone);
	pFind = strtok_s(pFind, ";", &pBuff);
	while (pFind)
	{
		if (strlen(pFind) == 11)
		{
			strValue = pFind;		
			break;
		}
		pFind = strtok_s(NULL, ";", &pBuff);
	}
	
	delete [] pBegin;
	return strValue;
}

BOOL CExcelDlg::MatchDBPeopleInfo(_WorksheetPtr worksheet, vector<DBPeopleInfo>& vecInfo, SimplePeopleInfo& info, const CString& strValue, CString& strPhone)
{
	vector<DBPeopleInfo>::iterator it = vecInfo.begin();
	int iSize = vecInfo.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (vecInfo[i].strNumber.Find(strValue) != -1)
		{
			PutRangeString(worksheet, vecInfo[i].strNumber, 'G', info.iRow);
			strPhone = GetSinglePhone(vecInfo[i].strPhone);
			if (strPhone.GetLength() == 11)
			{
				PutRangeString(worksheet, strPhone, 'M', info.iRow);
				return TRUE;
			}
			else
				return FALSE;
		}
	}
	return FALSE;
}

void CExcelDlg::CheckPhoneFormat(_WorksheetPtr worksheet, SimplePeopleInfo& info)
{
	int iLen;
	CString strPhone = GetNumber(info.strPhone, 11);
	if (strPhone.IsEmpty())
		strPhone = GetNumber(info.strPhone, 7);

	iLen = strPhone.GetLength();
	if ((iLen == 0) || (iLen == 11) || (iLen == 7))
		PutRangeString(worksheet, strPhone, 'M', info.iRow);
	else
		PutRangeString(worksheet, "", 'M', info.iRow);
}

void CExcelDlg::CheckPeopleFormat2(_WorksheetPtr worksheet, vector<SimpleHouseInfo>& vecInfo)
{
	int iSize = vecInfo.size();
	m_progress.SetRange(1, 10000);
	int iProgress = 0;
	for (vector<SimpleHouseInfo>::iterator it = vecInfo.begin(); it != vecInfo.end(); ++it)
	{
		for  (vector<SimplePeopleInfo>::iterator itPeople = it->vecPeoples.begin(); itPeople != it->vecPeoples.end(); ++itPeople)
		{
			CheckPhoneFormat(worksheet, *itPeople);
		}
		++iProgress;
		m_progress.SetPos(10000*iProgress/iSize);
	}
}

BOOL CExcelDlg::CheckPeopleFormat(_WorksheetPtr worksheet, SimplePeopleInfo& info, vector<DBPeopleInfo>& vecInfo, CString& strPhone)
{
	int iLen = info.strNumber.GetLength();
	int iYear, iMonth;
	CString strYear, strMonth, strValue;
	if (iLen != 18)
	{
		if ((iLen == 8) || (iLen == 6))
		{
			strYear = info.strNumber.Left(4);
			strMonth = info.strNumber.Mid(4, 2);
			iYear = atoi(strYear);
			iMonth = atoi(strMonth);
			// 校验身份证年月的正确性
			if ((iYear >= 1900) && (iYear <= 2017) && (iMonth > 0) && (iMonth <= 12))
			{
				return MatchDBPeopleInfo(worksheet, vecInfo, info, strYear+strMonth, strPhone);
			}
		}
	}
	else
	{
		return MatchDBPeopleInfo(worksheet, vecInfo, info, info.strNumber, strPhone);
	}
	return FALSE;
}

void CExcelDlg::UpdateOtherPeopleNumber(_WorksheetPtr worksheet, SimpleHouseInfo& houseinfo, int iIndex, const CString& strPhone)
{
	int iSize = houseinfo.vecPeoples.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (i != iIndex)
		{
			if (houseinfo.vecPeoples[i].strPhone.GetLength() != 11)
			{
				PutRangeString(worksheet, strPhone, 'M', houseinfo.vecPeoples[i].iRow);
			}
		}
	}
}

void CExcelDlg::UpdatePeopleInfo(_WorksheetPtr worksheet, vector<SimpleHouseInfo>& vecHouseInfo)
{
	int iSize = vecHouseInfo.size();
	m_progress.SetRange(1, 10000);
	int iProgress = 0;
	CString strPhone;
	for (int i = 0; i < iSize; ++i)
	{
		int iPeopleSize = vecHouseInfo[i].vecPeoples.size();
		for (int j = 0; j < iPeopleSize; ++j)
		{
			vector<DBPeopleInfo> vecDBPeople;
			GetPeopleDBInfo(vecHouseInfo[i].vecPeoples[j].strName, vecDBPeople);
			if (CheckPeopleFormat(worksheet, vecHouseInfo[i].vecPeoples[j], vecDBPeople, strPhone))
			{
				UpdateOtherPeopleNumber(worksheet, vecHouseInfo[i], j, strPhone);
				break;
			}
		}
		
		++iProgress;
		m_progress.SetPos(10000*iProgress/iSize);
	}
}

void CExcelDlg::CheckExcelFormat(CString strFileName)
{
	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");

	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Open(strFileName.GetBuffer(0));
	SheetsPtr worksheets = pBook->GetWorksheets();

	// 目标文件的第一个sheet指针
	_WorksheetPtr worksheet = worksheets->GetItem((_variant_t)(LONG)3);
	vector<SimpleHouseInfo> vecHouseInfo;
	m_progress.SetPos(0);
	m_progress.ShowWindow(SW_NORMAL);
	GetSimpleHouseinfo(worksheet, vecHouseInfo);
	UpdatePeopleInfo(worksheet, vecHouseInfo);
	AfxMessageBox("完成!");
	m_progress.ShowWindow(SW_HIDE);
	pBook->Save();
	pBook->Close();
	pBooks->Close();
}

void CExcelDlg::CheckExcelFormat2(CString strFileName)
{
	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");

	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Open(strFileName.GetBuffer(0));
	SheetsPtr worksheets = pBook->GetWorksheets();

	// 目标文件的第一个sheet指针
	_WorksheetPtr worksheet = worksheets->GetItem((_variant_t)(LONG)3);

	vector<SimpleHouseInfo> vecHouseInfo;
	m_progress.SetPos(0);
	m_progress.ShowWindow(SW_NORMAL);
	GetSimpleHouseinfo(worksheet, vecHouseInfo);
	
	CheckPeopleFormat2(worksheet, vecHouseInfo);
	AfxMessageBox("完成!");
	m_progress.ShowWindow(SW_HIDE);
	pBook->Save();
	pBook->Close();
	pBooks->Close();
}

void CExcelDlg::OnBnClickedButtonCheck()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDOK)
	{
		CheckExcelFormat(cFileDlg.GetPathName());
		return;
	}
}


void CExcelDlg::OnBnClickedButtonCheckFormat()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDOK)
	{
		CheckExcelFormat2(cFileDlg.GetPathName());
		return;
	}
}

/*
void CExcelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(&rect, &afxGlobalData.brBarFace);
}
*/
/*

HBRUSH CExcelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(afxGlobalData.clrBarFace);
		return afxGlobalData.brBarFace;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
*/

BOOL CExcelDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //回车
			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}
