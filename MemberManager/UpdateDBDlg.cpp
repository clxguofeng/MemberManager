// UpdateDBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateDBDlg.h"
#include "afxdialogex.h"


// CUpdateDBDlg 对话框

IMPLEMENT_DYNAMIC(CUpdateDBDlg, CMFCDialog)

CUpdateDBDlg::CUpdateDBDlg(CWnd* pParent /*=NULL*/)
	// : CDialogEx(CUpdateDBDlg::IDD, pParent)
	: CMFCDialog(IDD, pParent)
{

}

CUpdateDBDlg::~CUpdateDBDlg()
{
}

void CUpdateDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BUTTON_FILE_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, m_btnClearRepeat);
}


BEGIN_MESSAGE_MAP(CUpdateDBDlg, CMFCDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUpdateDBDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SELECT, &CUpdateDBDlg::OnBnClickedButtonFileSelect)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CUpdateDBDlg::OnBnClickedButtonClean)
END_MESSAGE_MAP()


// CUpdateDBDlg 消息处理程序
BOOL CUpdateDBDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //回车
			if (pMsg->hwnd == m_editData.m_hWnd)
				return CDialogEx::PreTranslateMessage(pMsg);

			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUpdateDBDlg::OnBnClickedButtonUpdate()
{
	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");
	CString strFileName, strSQLData, strWhere, strUpdate;
	GetDlgItemText(IDC_EDIT_FILE_SELECT, strFileName);
	GetDlgItemText(IDC_EDIT_DATA, strSQLData);
	GetDlgItemText(IDC_EDIT_TIAOJIANZIDUAN, strWhere);
	GetDlgItemText(IDC_EDIT_UPDATEZIDUAN, strUpdate);
	strFileName.TrimLeft();
	strFileName.TrimRight();
	strSQLData.TrimLeft();
	strSQLData.TrimRight();
	strWhere.TrimLeft();
	strWhere.TrimRight();
	strUpdate.TrimLeft();
	strUpdate.TrimRight();
	if (strFileName.IsEmpty())
	{
		AfxMessageBox("请选择文件!");
		return;
	}
	if (strSQLData.IsEmpty())
	{
		AfxMessageBox("请输入数据集!");
		return;
	}
	if (strWhere.IsEmpty())
	{
		AfxMessageBox("请输入条件字段!");
		return;
	}
	if (strUpdate.IsEmpty())
	{
		AfxMessageBox("请输入更新字段!");
		return;
	}
	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Open(strFileName.GetBuffer(0));
	SheetsPtr worksheets = pBook->GetWorksheets();
	// 目标文件的第一个sheet指针
	_WorksheetPtr worksheet = worksheets->GetItem((_variant_t)(LONG)1);
	UpdateDB(worksheet, strSQLData, strWhere, strUpdate);
	AfxMessageBox("完成!");
	pBook->Close();
	pBooks->Close();
}


void CUpdateDBDlg::OnBnClickedButtonFileSelect()
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
		SetDlgItemText(IDC_EDIT_FILE_SELECT, cFileDlg.GetPathName());
		return;
	}
}


void CUpdateDBDlg::UpdateDB(_WorksheetPtr worksheet, CString strSQL, CString strWhere, CString strUpdate)
{
	vector<CString> vecWhere;
	vector<CString> vecUpdate;
	vector<CString> vecZiDuan;
	CString strSQLTemp;
	int iRowBegin;
	CString strValue, strValue2;
	BOOL bBreak = FALSE;
	int i,j;
	int iSize;
	GetSplitString(strWhere, ",", vecWhere);
	GetSplitString(strUpdate, ",", vecUpdate);
	if ((vecUpdate.size() == 0) || (vecWhere.size() == 0))
	{
		AfxMessageBox("条件字段或更新字段内容设置错误!");
		return;
	}

	iRowBegin = atoi(vecWhere[0].Mid(1, 1));

	for (i = iRowBegin; ;++i)
	{
		strSQLTemp = strSQL;
		vecZiDuan.clear();
		iSize = vecWhere.size();
		for (j = 0; j < iSize; ++j)
		{
			strValue.Format("条件字段%d", j+1);
			strValue2 = GetRangeString(worksheet, vecWhere[j][0], i);
			strValue2.TrimLeft();
			strValue2.TrimRight();
			if (strValue2.IsEmpty())
				goto end;

			strValue2 = "'"+ strValue2;
			strValue2 += "'";
			strSQLTemp.Replace(strValue, strValue2);
		}
		iSize = vecUpdate.size();
		for (j = 0; j < iSize; ++j)
		{
			strValue.Format("更新字段%d", j+1);
			strValue2 = GetRangeString(worksheet, vecUpdate[j][0], i);
			strValue2.TrimLeft();
			strValue2.TrimRight();
			strValue2 = "'"+ strValue2;
			strValue2 += "'";
			strSQLTemp.Replace(strValue, strValue2);
		}
		ExecuteDBSQL(strSQLTemp);
	}
end:
	return;
}

BOOL ExecuteDBSQL(CString strSQL)
{
	mysql_init(&theApp.m_db);

	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		mysql_query(&theApp.m_db, "SET NAMES GBK");
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

BOOL CUpdateDBDlg::DeleteShortPhone(vector<CString>& vecPhone)
{
	BOOL bDelete = FALSE;
	for (vector<CString>::iterator it = vecPhone.begin(); it != vecPhone.end();)
	{
		if (it->GetLength() <= 6)
		{
			it = vecPhone.erase(it);
			bDelete = TRUE;
			continue;
		}
		++it;
	}
	return bDelete;
}

void CUpdateDBDlg::OnBnClickedButtonClean()
{
	vector<SimplePeopleInfo> vecMembers;
	if (GetMembers(vecMembers))
	{
		for (vector<SimplePeopleInfo>::iterator it = vecMembers.begin(); it != vecMembers.end(); ++it)
		{
			vector<CString> vecPhone;
			CString strCode;
			strCode = it->strNumber;
			strCode.TrimLeft();
			strCode.TrimRight();
			if (strCode.GetLength() < 10)
				continue;

			GetSplitString(it->strPhone, ",;", vecPhone);
			BOOL bDelete = DeleteShortPhone(vecPhone);
			vector<CString>::iterator iter = unique(vecPhone.begin(), vecPhone.end());
			if (iter != vecPhone.end())
			{
				vecPhone.erase(iter, vecPhone.end());
				bDelete = TRUE;
			}

			if (bDelete)
			{
				UpdateMember(it->strNumber, vecPhone);
			}
		}
		AfxMessageBox("去重成功!");
	}
}

void CUpdateDBDlg::UpdateMember(CString strCode, vector<CString>& vecPhone)
{
	CString strPhone;
	for (vector<CString>::iterator it = vecPhone.begin(); it != vecPhone.end(); ++it)
	{
		strPhone += *it;
		strPhone += ";";
	}

	CString strSQL;
	strSQL.Format("update memberinfo set phone='%s' where membercode='%s'", strPhone, strCode);
	ExecuteDBSQL(strSQL);
}

BOOL CUpdateDBDlg::GetMembers(vector<SimplePeopleInfo>& vecMembers)
{
	BOOL bRet = FALSE;
	mysql_init(&theApp.m_db);
	SimplePeopleInfo people;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select membercode,phone from memberinfo");

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				people.strNumber = sql_row[0];
				people.strPhone = sql_row[1];
				vecMembers.push_back(people);
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);

			bRet = TRUE;
		}
	}

	mysql_close(&theApp.m_db);
	return bRet;
}

BOOL CUpdateDBDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_editData.SetWindowText("update memberinfo set phone=更新字段1 where membercode=条件字段1");
	SetDlgItemText(IDC_EDIT_TIAOJIANZIDUAN, "a2");
	SetDlgItemText(IDC_EDIT_UPDATEZIDUAN, "d2");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
