// ExportExcelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "ExportExcelDlg.h"
#include "afxdialogex.h"
#include "UpdateSQLTemplateDlg.h"

// CExportExcelDlg �Ի���

IMPLEMENT_DYNAMIC(CExportExcelDlg, CMFCDialog)

CExportExcelDlg::CExportExcelDlg(CWnd* pParent)
: CMFCDialog(IDD, pParent)
{

}

CExportExcelDlg::~CExportExcelDlg()
{
}

void CExportExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editSQL);
	DDX_Control(pDX, IDC_EDIT_EXPORTZIDUAN, m_editFieldName);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_editWidth);
}


BEGIN_MESSAGE_MAP(CExportExcelDlg, CMFCDialog)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CExportExcelDlg::OnBnClickedButtonExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CExportExcelDlg::OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CExportExcelDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CExportExcelDlg::OnRclickList)
	ON_COMMAND(ID_CERTIFY_UPDATE, &CExportExcelDlg::OnCertifyUpdate)
	ON_COMMAND(ID_CERTIFY_DELETE, &CExportExcelDlg::OnCertifyDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CExportExcelDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CExportExcelDlg ��Ϣ�������


void CExportExcelDlg::OnBnClickedButtonExport()
{
	CString strSQL, strZiDuan, strTitle, strWidth;
	GetDlgItemText(IDC_EDIT_DATA, strSQL);
	GetDlgItemText(IDC_EDIT_EXPORTZIDUAN, strZiDuan);
	GetDlgItemText(IDC_EDIT_TITLE, strTitle);
	GetDlgItemText(IDC_EDIT_WIDTH, strWidth);

	strSQL.Trim();
	strZiDuan.Trim();
	strTitle.Trim();
	strWidth.Trim();

	if (strSQL.IsEmpty())
	{
		AfxMessageBox("������SQL���!");
		return;
	}
	if (strZiDuan.IsEmpty())
	{
		AfxMessageBox("�������ֶ���!");
		return;
	}
	if (strTitle.IsEmpty())
	{
		AfxMessageBox("���������!");
		return;
	}

	ExportExcel(strSQL, strZiDuan, strTitle, strTitle, strWidth);
}

void CExportExcelDlg::ExportExcel(vector<SQLEXPORTSTRUCT>& vecSQLStruct)
{
	int iSize = vecSQLStruct.size();
	BOOL bRet = FALSE;
	CString strFilename;
	if (iSize >= 1)
	{
		strFilename = vecSQLStruct[0].strFilename;
	}

	CFileDialog cFileDlg(FALSE, _T( "Excel"),strFilename,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||");
	//���Ҫ�򿪵��ļ�
	if (cFileDlg.DoModal() == IDCANCEL)
		return;

	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");
	pXL->PutDisplayAlerts(LOCALE_USER_DEFAULT, VARIANT_FALSE);

	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Add((long)xlWorkbook);
	SheetsPtr worksheets = pBook->GetWorksheets();
	
	for (int i = (iSize-1); i >= 0; --i)
	{

		_WorksheetPtr worksheet = worksheets->Add();
		// Ŀ���ļ��ĵ�һ��sheetָ��
		// _WorksheetPtr worksheet = worksheets->GetItem((_variant_t)(LONG)(i+1));
		if (vecSQLStruct[i].strSheetname.IsEmpty() == FALSE)
			worksheet->PutName(_bstr_t(vecSQLStruct[i].strSheetname));

		bRet = ExportExcelFromDB(worksheet,vecSQLStruct[i].strSQL,vecSQLStruct[i].strField,vecSQLStruct[i].strTitle,vecSQLStruct[i].strWidth);
		if (bRet == FALSE)
			break;
	}
	
	if (bRet)
	{
		pBook->SaveAs(cFileDlg.GetPathName().GetBuffer(0),
			xlWorkbookNormal,
			_variant_t(""),
			_variant_t(""),
			_variant_t(false),
			_variant_t(false),
			xlNoChange,
			xlLocalSessionChanges,
			_variant_t(false));
	}

	pBook->Close();
	pBooks->Close();
	pXL->Quit();

	if (bRet)
		AfxMessageBox("���!");
	else
		AfxMessageBox("����ʧ��!");
}

void CExportExcelDlg::ExportExcel(CString strSQL, CString strZiDuan, CString strTitle, CString strSheetname, CString strWidth)
{
	CFileDialog cFileDlg(FALSE, _T( "Excel"),strTitle,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||");
	//���Ҫ�򿪵��ļ�
	if (cFileDlg.DoModal() == IDCANCEL)
		return;

	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");
	pXL->PutDisplayAlerts(LOCALE_USER_DEFAULT, VARIANT_FALSE);
	
	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Add((long)xlWorkbook);
	SheetsPtr worksheets = pBook->GetWorksheets();
	// Ŀ���ļ��ĵ�һ��sheetָ��
	_WorksheetPtr worksheet = worksheets->GetItem((_variant_t)(LONG)1);
	if (strSheetname.IsEmpty() == FALSE)
		worksheet->PutName(_bstr_t(strSheetname));
	
	BOOL bRet = ExportExcelFromDB(worksheet,strSQL,strZiDuan,strTitle,strWidth);
	if (bRet)
	{
		pBook->SaveAs(cFileDlg.GetPathName().GetBuffer(0),
			xlWorkbookNormal,
			_variant_t(""),
			_variant_t(""),
			_variant_t(false),
			_variant_t(false),
			xlNoChange,
			xlLocalSessionChanges,
			_variant_t(false));
	}

	pBook->Close();
	pBooks->Close();

	if (bRet)
		AfxMessageBox("���!");
	else
		AfxMessageBox("����ʧ��!");
}

void CExportExcelDlg::SetColumInfo(_WorksheetPtr worksheet, CString strTitle, char cBeginColum, char cEndColum, vector<CString>& vecZiDuan)
{
	// ���ñ����
	PutRangeString(worksheet, strTitle, 'A', 1);
	CString strRange;
	strRange.Format("A1:%c1", cEndColum);
	RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->Merge(COleVariant((long)0));
	rangeName->PutHorizontalAlignment(xlHAlignCenter);
	rangeName->Font->Size = 20;
	// �����ֶο�Ⱥͱ���ɫ
	strRange.Format("A:%c", cEndColum);
	rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->ColumnWidth = 10;
	rangeName->NumberFormat = "@";
	strRange.Format("A2:%c2", cEndColum);
	rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->Interior->ColorIndex = (long)15;
	// �����ֶο��
	strRange.Format("%c:%c", cBeginColum, cEndColum);
	rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->ColumnWidth = 20;
	rangeName->NumberFormat = "@";
	// д�ֶ���
	int iSize = vecZiDuan.size();
	for (int i = 0; i < iSize; ++i)
	{
		PutRangeString(worksheet, vecZiDuan[i], cBeginColum, 2);
		++cBeginColum;
	}
}

void CExportExcelDlg::SetColumInfo(_WorksheetPtr worksheet, CString strTitle, char cBeginColum, char cEndColum, vector<CString>& vecZiDuan, vector<CString>& vecWidth)
{
	// ���ñ����
	PutRangeString(worksheet, strTitle, 'A', 1);
	CString strRange;
	strRange.Format("%c1:%c1", cBeginColum, cEndColum);
	RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->Merge(COleVariant((long)0));
	rangeName->PutHorizontalAlignment(xlHAlignCenter);
	rangeName->Font->Size = 20;
	// �����ֶο��
	vector<CString>::iterator it = vecWidth.begin();
	char cWidth = 'A';
	for (; it != vecWidth.end(); ++it)
	{
		strRange.Format("%c:%c", cWidth, cWidth);
		rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
		rangeName->ColumnWidth = atoi(*it);
		rangeName->NumberFormat = "@";
		++cWidth;
	}
	/*
	strRange.Format("A:%c", cEndColum);
	rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->ColumnWidth = 10;
	rangeName->NumberFormat = "@";
	*/
	// ���ñ���ɫ
	strRange.Format("A2:%c2", cEndColum);
	rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
	rangeName->Interior->ColorIndex = (long)15;
	// д�ֶ���
	int iSize = vecZiDuan.size();
	for (int i = 0; i < iSize; ++i)
	{
		PutRangeString(worksheet, vecZiDuan[i], cBeginColum, 2);
		++cBeginColum;
	}
}

BOOL CExportExcelDlg::ExportExcelFromDB(_WorksheetPtr worksheet,CString strSQL, CString strZiDuan, CString strTitle, CString strWidth)
{
	BOOL bRet = FALSE;
	
	vector<CString> vecZiDuan;
	GetSplitString(strZiDuan, ",", vecZiDuan);
	if (vecZiDuan.size() == 0)
	{
		AfxMessageBox("�ֶ�������Ϊ��!");
		return bRet;
	}

	int iSize = vecZiDuan.size();
	char cBeginColum = 'A';
	char cEndColum = 'A'+iSize-1;

	vector<CString> vecWidth;
	GetSplitString(strWidth, ",", vecWidth);
	if (vecWidth.size() == 0)
		SetColumInfo(worksheet, strTitle, cBeginColum, cEndColum, vecZiDuan);
	else
		SetColumInfo(worksheet, strTitle, cBeginColum, cEndColum, vecZiDuan, vecWidth);

	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSQL);
		int iRow = 3;
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			int iColumnNums = mysql_num_fields(result);

			// ��ȡ��������� 
			while (sql_row = mysql_fetch_row(result)) 
			{
				cBeginColum = 'A';
				for (int i = 0; i < iColumnNums; ++i)
				{
					PutRangeString(worksheet, sql_row[i], cBeginColum, iRow);
					++cBeginColum;
				}
				++iRow;
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);

			if (iRow > 2)
				--iRow;

			CString strRange;
			strRange.Format("1:1");
			RangePtr rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
			rangeName->RowHeight = 50;

			strRange.Format("2:%d", iRow);
			rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
			rangeName->RowHeight = 20;

			strRange.Format("A2:%C%d", cEndColum, iRow);
			rangeName = worksheet->GetRange(_variant_t(strRange), _variant_t(strRange));
			rangeName->Borders->PutColor(RGB(0, 0, 0));
			bRet = TRUE;
		}
	}

	mysql_close(&theApp.m_db);
	return bRet;
}

BOOL CExportExcelDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("���"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("����"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, _T("SQL���"), LVCFMT_LEFT, 250);
	m_List.InsertColumn(3, _T("�ֶ�"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, _T("�ֶο��"), LVCFMT_LEFT, 150);
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
	InitList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CExportExcelDlg::InitList()
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
		strSelect.Format("select sqlid,sqlname,sqlstring,fieldname,fieldwidth from exportsql");

		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// ��ȡ��������� 
			int iRow = 0;
			// CString strValue;
			while (sql_row = mysql_fetch_row(result)) 
			{
				// strValue.Format("%d", iRow+1);
				m_List.InsertItem(iRow, sql_row[0]);
				m_List.SetItemText(iRow, 1, sql_row[1]);
				m_List.SetItemText(iRow, 2, sql_row[2]);
				m_List.SetItemText(iRow, 3, sql_row[3]);
				m_List.SetItemText(iRow, 4, sql_row[4]);
				// m_List.SetItemData(iRow, atoi(sql_row[0]));
				++iRow;
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CExportExcelDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		m_editTitle.SetWindowText(m_List.GetItemText(iSelect, 1));
		m_editSQL.SetWindowText(m_List.GetItemText(iSelect, 2));
		m_editFieldName.SetWindowText(m_List.GetItemText(iSelect, 3));
		m_editWidth.SetWindowText(m_List.GetItemText(iSelect, 4));
	}
	*pResult = 0;
}


void CExportExcelDlg::OnBnClickedButtonAdd()
{
	CUpdateSQLTemplateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		InitList();
	}
}


void CExportExcelDlg::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CPoint point;
		GetCursorPos(&point);
		CMenu menu;
		menu.LoadMenu(IDR_MENU_CERTIFY_LIST);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y,this);
	}
}


void CExportExcelDlg::OnCertifyUpdate()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CUpdateSQLTemplateDlg dlg;
		dlg.m_strID = m_List.GetItemText(iSelect, 0);
		dlg.m_strTitle = m_List.GetItemText(iSelect, 1);
		dlg.m_strSQL = m_List.GetItemText(iSelect, 2);
		dlg.m_strZiduan = m_List.GetItemText(iSelect, 3);
		dlg.m_strZiduanWidth = m_List.GetItemText(iSelect, 4);
		if (dlg.DoModal() == IDOK)
		{
			InitList();
		}
	}
}

void CExportExcelDlg::OnCertifyDelete()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		if (AfxMessageBox("��ȷ��ɾ����?", MB_OKCANCEL) == IDOK)
		{
			CString strID = m_List.GetItemText(iSelect, 0);
			CString strSQL;
			strSQL.Format("delete from exportsql where sqlid=%s", strID);
			if (ExecuteDBSQL(strSQL))
			{
				InitList();
			}
			else
			{
				AfxMessageBox("ɾ��ʧ��!");
			}
		}
	}
}


void CExportExcelDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnCertifyUpdate();
}
