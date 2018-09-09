// ExportCertifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "ExportCertifyDlg.h"
#include "SelectYibaoMemberDlg.h"
#include "afxdialogex.h"
#include "UpdateCertifyDlg.h"

// CExportCertifyDlg 对话框

IMPLEMENT_DYNAMIC(CExportCertifyDlg, CMFCDialog)

CExportCertifyDlg::CExportCertifyDlg(CWnd* pParent /*=NULL*/)
	: CMFCDialog(CExportCertifyDlg::IDD, pParent)
{

}

CExportCertifyDlg::~CExportCertifyDlg()
{
}

void CExportCertifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME_1, m_editName1);
	DDX_Control(pDX, IDC_EDIT_CODE_1, m_editCode1);
	DDX_Control(pDX, IDC_EDIT_NAME_2, m_editName2);
	DDX_Control(pDX, IDC_EDIT_NAME_3, m_editName3);
	DDX_Control(pDX, IDC_EDIT_CODE_2, m_editCode2);
	DDX_Control(pDX, IDC_EDIT_CODE_3, m_editCode3);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
	DDX_Control(pDX, IDC_BUTTON_ASSIGN, m_btnAssign);
	DDX_Control(pDX, IDC_EDIT_SELECT, m_editSelect);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_CHECK_CERTIFY_FLAG, m_CertifyCheck);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_date2);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_date3);

}


BEGIN_MESSAGE_MAP(CExportCertifyDlg, CMFCDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CExportCertifyDlg::OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_BUTTON_ASSIGN, &CExportCertifyDlg::OnBnClickedButtonAssign)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CExportCertifyDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CExportCertifyDlg::OnBnClickedButtonAdd)
	ON_COMMAND(ID_CERTIFY_UPDATE, &CExportCertifyDlg::OnCertifyUpdate)
	ON_COMMAND(ID_CERTIFY_DELETE, &CExportCertifyDlg::OnCertifyDelete)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CExportCertifyDlg::OnNMRClickList)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CExportCertifyDlg::OnBnClickedButtonSelect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CExportCertifyDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CExportCertifyDlg 消息处理程序


BOOL CExportCertifyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //回车
			{
				if (pMsg->hwnd == m_editName1.m_hWnd)
				{
					CString strName;
					m_editName1.GetWindowText(strName);
					CSelectYibaoMemberDlg dlg(strName);
					if (dlg.DoModal() == IDOK)
					{
						m_editName1.SetWindowText(dlg.m_strName);
						m_editCode1.SetWindowText(dlg.m_strCode);
						m_editName2.SetFocus();
					}
				}
				else if (pMsg->hwnd == m_editName2.m_hWnd)
				{
					CString strName;
					m_editName2.GetWindowText(strName);
					CSelectYibaoMemberDlg dlg(strName);
					if (dlg.DoModal() == IDOK)
					{
						m_editName2.SetWindowText(dlg.m_strName);
						m_editCode2.SetWindowText(dlg.m_strCode);
						m_editName3.SetFocus();
					}
				}
				else if (pMsg->hwnd == m_editName3.m_hWnd)
				{
					CString strName;
					m_editName3.GetWindowText(strName);
					CSelectYibaoMemberDlg dlg(strName);
					if (dlg.DoModal() == IDOK)
					{
						m_editName3.SetWindowText(dlg.m_strName);
						m_editCode3.SetWindowText(dlg.m_strCode);
						m_btnAssign.SetFocus();
					}
				}
				if (pMsg->hwnd == m_editSelect.m_hWnd)
				{
					OnBnClickedButtonSelect();
				}
			}
			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	}
	return CMFCDialog::PreTranslateMessage(pMsg);
}


BOOL CExportCertifyDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_editTitle.SetWindowText("证   明");
	m_editName1.SetFocus();
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);  
	m_List.InsertColumn(1, _T("模板名"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, _T("标题"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(3, _T("正文"), LVCFMT_LEFT, 340);

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
	m_CertifyCheck.SetCheck(1);
	OnBnClickedButtonSelect();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CExportCertifyDlg::InitList(CString strSQL)
{	
	m_List.DeleteAllItems();
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
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			int iRow = 0;
			CString strValue;
			while (sql_row = mysql_fetch_row(result)) 
			{
				strValue.Format("%d", iRow+1);
				m_List.InsertItem(iRow, strValue);
				m_List.SetItemText(iRow, 1, sql_row[1]);
				m_List.SetItemText(iRow, 2, sql_row[2]);
				m_List.SetItemText(iRow, 3, sql_row[3]);
				m_List.SetItemData(iRow, atoi(sql_row[0]));
				++iRow;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CExportCertifyDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		m_editTitle.SetWindowText(m_List.GetItemText(iSelect, 2));
		m_editData.SetWindowText(m_List.GetItemText(iSelect, 3));
	}
	*pResult = 0;
}


void CExportCertifyDlg::OnBnClickedButtonAssign()
{
	CString strText, strValue, strSex;
	m_editData.GetWindowText(strText);
	m_editName1.GetWindowText(strValue);
	strValue = strValue.Trim();
	if (strValue.IsEmpty() == FALSE)
	{
		strText.Replace("<name1>", strValue);
	}
	m_editCode1.GetWindowText(strValue);
	strValue = strValue.Trim();
	if (strValue.IsEmpty() == FALSE)
	{
		strText.Replace("<code1>", strValue);
		strText.Replace("<sex1>", GetSex(strValue));
	}
	CTime timeTime;
	m_date1.GetTime(timeTime);
	strText.Replace("<date1>", timeTime.Format("%Y年%m月%d日"));
	
	m_editName2.GetWindowText(strValue);
	strValue = strValue.Trim();
	if (strValue.IsEmpty() == FALSE)
	{
		strText.Replace("<name2>", strValue);
	}

	m_editCode2.GetWindowText(strValue);
	strValue = strValue.Trim();
	if (strValue.IsEmpty() == FALSE)
	{
		strText.Replace("<code2>", strValue);
		strText.Replace("<sex2>", GetSex(strValue));
	}

	m_date2.GetTime(timeTime);
	strText.Replace("<date2>", timeTime.Format("%Y年%m月%d日"));

	m_editName3.GetWindowText(strValue);
	strValue = strValue.Trim();
	if (strValue.IsEmpty() == FALSE)
	{
		strText.Replace("<name3>", strValue);
	}

	m_editCode3.GetWindowText(strValue);
	strValue = strValue.Trim();
	if (strValue.IsEmpty() == FALSE)
	{
		strText.Replace("<code3>", strValue);
		strText.Replace("<sex3>", GetSex(strValue));
	}

	m_date3.GetTime(timeTime);
	strText.Replace("<date3>", timeTime.Format("%Y年%m月%d日"));
	m_editData.SetWindowText(strText);
}

CString GetSex(CString strCode)
{
	CString strRet;
	int iLen = strCode.GetLength();
	if (iLen == 18)
	{
		int iValue = atoi(CString(strCode[16]));
		if (iValue % 2 == 0)
			strRet = "女";
		else
			strRet = "男";
	}
	
	return strRet;
}

void CExportCertifyDlg::OnBnClickedButtonExport()
{
	CString strTitle;
	m_editTitle.GetWindowText(strTitle);
	CFileDialog cFileDlg(FALSE, _T( "Word"),
		strTitle,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Word Files(*.doc;*.docx)|*.doc;*.docx|All Files (*.*)|*.*||");
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDCANCEL)
		return;

	Word::_ApplicationPtr spWordApp;
	HRESULT hr = spWordApp.CreateInstance(__uuidof(Word::Application)); 
	if (FAILED(hr)) 
	{ 
		AfxMessageBox("导出失败!");
		return; 
	}
	CString strValue;
	m_editData.GetWindowText(strValue);
	strValue.Trim();
	strValue = "    " + strValue;
	spWordApp->Visible = VARIANT_FALSE;
	Word::DocumentsPtr spDocs = spWordApp->Documents; 
	Word::_DocumentPtr spDoc = spDocs->Add();
	Word::ParagraphsPtr spParas = spDoc->Paragraphs; 
	Word::ParagraphPtr spPara = spParas->Add();
	Word::RangePtr spParaRng = spPara->Range;
	spParaRng->Text = _bstr_t(strTitle);
	spPara->PutAlignment(Word::wdAlignParagraphCenter);
	Word::_FontPtr spFont = spParaRng->Font; 
	spFont->Bold = 1;
	spFont->Size = 25;
	spParaRng->InsertParagraphAfter();

	spPara = spParas->Add();
	spParaRng = spPara->Range;
	spParaRng->Text = _bstr_t(strValue);
	spPara->PutAlignment(Word::wdAlignParagraphJustify);


	spParaRng->InsertParagraphAfter();
	spParaRng->InsertParagraphAfter();
	spParaRng->InsertParagraphAfter();
	if (m_CertifyCheck.GetCheck())
	{
		strValue = "\t\t\t\t特此证明";
		spParaRng->InsertAfter(_bstr_t(strValue));
	}

	spFont = spParaRng->Font;
	spFont->Size = 18;
	spParaRng->InsertParagraphAfter();
	spParaRng->InsertParagraphAfter();
	spParaRng->InsertParagraphAfter();
	spParaRng->InsertParagraphAfter();
	spParaRng->InsertParagraphAfter();
	spPara = spParas->Add();
	spParaRng = spPara->Range;
	strValue = "城西居委会";
	spParaRng->Text = _bstr_t(strValue);
	spPara->PutAlignment(Word::wdAlignParagraphRight);
	spFont = spParaRng->Font;
	spFont->Size = 18;
	spParaRng->InsertParagraphAfter();

	spPara = spParas->Add();
	spParaRng = spPara->Range;
	CTime curtime = CTime::GetCurrentTime();
	strValue = curtime.Format("%Y年%m月%d日");
	spParaRng->Text = _bstr_t(strValue);
	spPara->PutAlignment(Word::wdAlignParagraphRight);
	spFont = spParaRng->Font;
	spFont->Size = 18;

	variant_t vtFileName(cFileDlg.GetPathName());
	spDoc->SaveAs(&vtFileName); 
	spDoc->Close();
	spWordApp->Quit();
	AfxMessageBox("导出成功!");
}


void CExportCertifyDlg::OnBnClickedButtonAdd()
{
	UpdateCertifyDlg dlg(0);
	if (dlg.DoModal() == IDOK)
	{
		OnBnClickedButtonSelect();
	}
}


void CExportCertifyDlg::OnCertifyUpdate()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		UpdateCertifyDlg dlg(1);
		dlg.m_strID = m_List.GetItemText(iSelect, 0);
		dlg.m_strName = m_List.GetItemText(iSelect, 1);
		dlg.m_strTitle = m_List.GetItemText(iSelect, 2);
		dlg.m_strData = m_List.GetItemText(iSelect, 3);
		if (dlg.DoModal() == IDOK)
		{
			OnBnClickedButtonSelect();
		}
	}
}


void CExportCertifyDlg::OnCertifyDelete()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		if (AfxMessageBox("你确定删除吗?", MB_OKCANCEL) == IDOK)
		{
			CString strID = m_List.GetItemText(iSelect, 0);
			CString strSQL;
			strSQL.Format("delete certifytemplate where certifyid=%s", strID);
			if (ExecuteDBSQL(strSQL))
			{
				OnBnClickedButtonSelect();
			}
			else
			{
				AfxMessageBox("删除失败!");
			}
		}
	}
}


void CExportCertifyDlg::OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult)
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
	*pResult = 0;
}


void CExportCertifyDlg::OnBnClickedButtonSelect()
{
	CString strName;
	m_editSelect.GetWindowText(strName);
	strName.Trim();
	CString strSQL;
	strSQL.Format("select certifyid,certifyname,certifytitle,certifydata from certifytemplate where 1=1 ");
	if (strName.IsEmpty() == FALSE)
	{
		CString strWhere;
		strWhere.Format("and certifyname like '%%%s%%'", strName);
		strSQL += strWhere;
	}
	InitList(strSQL);
}


void CExportCertifyDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		UpdateCertifyDlg dlg(1);
		dlg.m_strID = m_List.GetItemText(iSelect, 0);
		dlg.m_strName = m_List.GetItemText(iSelect, 1);
		dlg.m_strTitle = m_List.GetItemText(iSelect, 2);
		dlg.m_strData = m_List.GetItemText(iSelect, 3);
		if (dlg.DoModal() == IDOK)
		{
			OnBnClickedButtonSelect();
		}
	}
	*pResult = 0;
}
