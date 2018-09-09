// UpdateExcelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateExcelDlg.h"
#include "afxdialogex.h"


// CUpdateExcelDlg �Ի���

IMPLEMENT_DYNAMIC(CUpdateExcelDlg, CMFCDialog)

CUpdateExcelDlg::CUpdateExcelDlg(CWnd* pParent /*=NULL*/)
	// : CDialogEx(CUpdateExcelDlg::IDD, pParent)
	: CMFCDialog(IDD, pParent)
{

}

CUpdateExcelDlg::~CUpdateExcelDlg()
{
}

void CUpdateExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BUTTON_FILE_SELECT, m_btnSelect);
}


BEGIN_MESSAGE_MAP(CUpdateExcelDlg, CMFCDialog)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SELECT, &CUpdateExcelDlg::OnBnClickedButtonFileSelect)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUpdateExcelDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CUpdateExcelDlg ��Ϣ�������


void CUpdateExcelDlg::OnBnClickedButtonFileSelect()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//���Ҫ�򿪵��ļ�
	if (cFileDlg.DoModal() == IDOK)
	{
		// ImportFile(cFileDlg.GetPathName());
		SetDlgItemText(IDC_EDIT_FILE_SELECT, cFileDlg.GetPathName());
		return;
	}
}


void CUpdateExcelDlg::OnBnClickedButtonUpdate()
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
		AfxMessageBox("��ѡ���ļ�!");
		return;
	}
	if (strSQLData.IsEmpty())
	{
		AfxMessageBox("���������ݼ�!");
		return;
	}
	if (strWhere.IsEmpty())
	{
		AfxMessageBox("�����������ֶ�!");
		return;
	}
	if (strUpdate.IsEmpty())
	{
		AfxMessageBox("����������ֶ�!");
		return;
	}
	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Open(strFileName.GetBuffer(0));
	SheetsPtr worksheets = pBook->GetWorksheets();
	// Ŀ���ļ��ĵ�һ��sheetָ��
	_WorksheetPtr worksheet = worksheets->GetItem((_variant_t)(LONG)1);
	UpdateExcel(worksheet, strSQLData, strWhere, strUpdate);
	AfxMessageBox("���!");
	pBook->Save();
	pBook->Close();
	pBooks->Close();
}

void CUpdateExcelDlg::UpdateExcel(_WorksheetPtr worksheet, CString strSQL, CString strWhere, CString strUpdate)
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
		AfxMessageBox("�����ֶλ�����ֶ��������ô���!");
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
			strValue.Format("�����ֶ�%d", j+1);
			strValue2 = GetRangeString(worksheet, vecWhere[j][0], i);
			strValue2.TrimLeft();
			strValue2.TrimRight();
			if (strValue2.IsEmpty())
				goto end;
			
			strValue2 = "'"+ strValue2;
			strValue2 += "'";
			strSQLTemp.Replace(strValue, strValue2);
		}
		GetZiDuanValue(strSQLTemp, vecZiDuan);
		if (vecZiDuan.size() < vecUpdate.size())
			continue;

		iSize = vecUpdate.size();
		for (j = 0; j < iSize; ++j)
		{
			strValue = GetRangeString(worksheet, vecUpdate[j][0], i);
			strValue.TrimLeft();
			strValue.TrimRight();
			if (strValue.IsEmpty())
				PutRangeString(worksheet, vecZiDuan[j], vecUpdate[j][0], i);
		}
	}
end:
	return;
}

void CUpdateExcelDlg::GetZiDuanValue(CString strSQL, vector<CString>& vecZiDuan)
{
	mysql_init(&theApp.m_db);
	DBPeopleInfo dbinfo;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSQL);
		int iLine = 0;
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			int j = mysql_num_fields(result);
			// ��ȡ��������� 
			while (sql_row = mysql_fetch_row(result)) 
			{
				for (int k = 0; k < j; ++k)
					vecZiDuan.push_back(sql_row[k]);

				break;
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void GetSplitString(CString strValue, CString strKey, vector<CString>& vecSplit)
{
	int iLen = strValue.GetLength();
	char *pFind = new char[iLen+1];
	char *pBegin = pFind;
	char *pBuff;
	strcpy_s(pFind, iLen+1, strValue);
	pFind = strtok_s(pFind, strKey, &pBuff);
	while (pFind)
	{
		strValue = pFind;
		if (strValue.GetLength() >= 1)
		{
			vecSplit.push_back(strValue);
		}
		pFind = strtok_s(NULL, strKey, &pBuff);
	}

	delete [] pBegin;
}

BOOL CUpdateExcelDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //�س�
			if (pMsg->hwnd == m_editData.m_hWnd)
				return CDialogEx::PreTranslateMessage(pMsg);

			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CUpdateExcelDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editData.SetWindowText("select memberstyle,phone,comment from memberinfo where membercode=�����ֶ�1");
	SetDlgItemText(IDC_EDIT_TIAOJIANZIDUAN, "b2");
	SetDlgItemText(IDC_EDIT_UPDATEZIDUAN, "d2,e2,h2");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
