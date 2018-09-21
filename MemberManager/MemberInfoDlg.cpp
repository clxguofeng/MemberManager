// MemberInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "MemberInfoDlg.h"
#include "afxdialogex.h"
#include "UpdateMemberDlg.h"

// CMemberInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMemberInfoDlg, CMFCDialog)

CMemberInfoDlg::CMemberInfoDlg(CWnd* pParent)
: CMFCDialog(IDD, pParent)
{
}

CMemberInfoDlg::~CMemberInfoDlg()
{
}

void CMemberInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMBERINFO, m_List);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_COMBO, m_combo);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnNew);
}


BEGIN_MESSAGE_MAP(CMemberInfoDlg, CMFCDialog)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CMemberInfoDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CMemberInfoDlg::OnBnClickedButtonImport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MEMBERINFO, &CMemberInfoDlg::OnDblclkListMemberinfo)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CMemberInfoDlg::OnBnClickedButtonNew)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MEMBERINFO, &CMemberInfoDlg::OnRclickListMemberinfo)
	ON_COMMAND(ID_EDIT_COPY, &CMemberInfoDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_DELETE, &CMemberInfoDlg::OnEditDelete)
END_MESSAGE_MAP()


// CMemberInfoDlg 消息处理程序


void CMemberInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_List.m_hWnd)
		m_List.MoveWindow(10, 50, cx - 20, cy - 50 - 10);
}

void CMemberInfoDlg::InitList(CString strSQL)
{
	int iLine = 0;
	CString strNum;
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
			while (sql_row = mysql_fetch_row(result)) 
			{ 
				// strNum.Format("%d", iLine+1);
				// m_List.InsertItem(iLine, strNum);
				// m_List.SetItemData(iLine, atoi(sql_row[0]));
				m_List.InsertItem(iLine, sql_row[0]);
				m_List.SetItemText(iLine, 1, sql_row[1]);
				m_List.SetItemText(iLine, 2, sql_row[2]);
				m_List.SetItemText(iLine, 3, sql_row[3]);
				m_List.SetItemText(iLine, 4, sql_row[4]);
				m_List.SetItemText(iLine, 5, sql_row[5]);
				++iLine;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);


		}
	}

	mysql_close(&theApp.m_db);
}
void CMemberInfoDlg::SelectMemberInfo(CString strKey, CString strSelect)
{
	m_List.DeleteAllItems();
	CString strSQL;
	strSQL = "select memberid,membername,membercode,memberstyle,phone,comment from memberinfo where 1=1 ";
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

BOOL CMemberInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);  
	m_List.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, _T("身份证"), LVCFMT_LEFT, 220);
	m_List.InsertColumn(3, _T("类型"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(4, _T("联系方式"), LVCFMT_LEFT, 300);
	m_List.InsertColumn(5, _T("备注"), LVCFMT_LEFT, 300);
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

	// m_btnNew.m_bTransparent = FALSE;
	// m_btnNew.SetFaceColor(afxGlobalData.clrBarFace);

	InitCombo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


int CMemberInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CMemberInfoDlg::OnBnClickedButtonSelect()
{
	int iIndex = m_combo.GetCurSel();
	CString strSelect;
	m_editName.GetWindowText(strSelect);
	SelectMemberInfo(m_vecCombo[iIndex], strSelect);
}


void CMemberInfoDlg::OnBnClickedButtonImport()
{
	CFileDialog cFileDlg(TRUE, _T( "Excel"),(LPCTSTR)NULL,
		OFN_ENABLESIZING|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_LONGNAMES|
		OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		"Excel Files(*.xls;*.xlsx)|*.xls;*.xlsx|All Files (*.*)|*.*||",
		this);
	//获得要打开的文件
	if (cFileDlg.DoModal() == IDOK)
	{
		ImportFile(cFileDlg.GetPathName());
		return;
	}
}

void CMemberInfoDlg::InitCombo()
{
	m_combo.InsertString(0, "姓名");
	m_combo.InsertString(1, "身份证");
	m_combo.InsertString(2, "类型");
	m_combo.InsertString(3, "联系方式");
	m_combo.InsertString(4, "备注");
	m_vecCombo.push_back("membername");
	m_vecCombo.push_back("membercode");
	m_vecCombo.push_back("memberstyle");
	m_vecCombo.push_back("phone");
	m_vecCombo.push_back("comment");
	m_combo.SetCurSel(0);
}

BOOL CMemberInfoDlg::ImportFile(CString strFileName)
{
	_ApplicationPtr pXL;
	pXL.CreateInstance(L"Excel.Application");

	CString strName, strCode, strTemp;
	_WorksheetPtr worksheet;

	RangePtr rangeName;
	CString strOldPhone;
	int i;
	
	WorkbooksPtr pBooks = pXL->Workbooks;
	_WorkbookPtr pBook = pBooks->Open(strFileName.GetBuffer(0));
	SheetsPtr worksheets = pBook->GetWorksheets();
	DWORD dwCount = worksheets->GetCount();
	vector<char> vecPhone;
	if (dwCount == 0)
	{
		AfxMessageBox("XLS文件没有内容");
		pBook->Close();
		pBooks->Close();
		return FALSE;
	}
	else
	{
		for (int iSheet = 1; iSheet <= (int)dwCount; ++iSheet)
		{
			worksheet = worksheets->GetItem((_variant_t)(LONG)iSheet);
			char szChars[2] = {0};
			char cMemberName = 0, cCode = 0;
			int iBegin = 0;
			vecPhone.clear();
			for (i = 1; i < 8; ++i)
			{
				char cChar = 'A';
				while(cChar != 'Z')
				{
					szChars[0] = cChar;
					strName.Format("%s%d", szChars, i);
					rangeName = worksheet->GetRange(_variant_t(strName), _variant_t(strName));
					strName = (LPCTSTR)(_bstr_t)(rangeName->GetValue2());
					strName.Replace(" ", "");
					if (strName.Find("姓名") != -1)
					{
						iBegin = i + 1;
						cMemberName = cChar;
					}
					else if (strName.Find("身份") != -1)
					{
						iBegin = i + 1;
						cCode = cChar;
					}
					else if ((strName.Find("联系方式") != -1) ||
						(strName.Find("手机") != -1) ||
						(strName.Find("电话") != -1))
					{
						iBegin = i + 1;
						vecPhone.push_back(cChar);
					}
					++cChar;
				}
				if (iBegin > 0)
				{
					break;
				}
			}

			// 如果没有找到姓名，电话，身份证则该sheet不做处理
			if (!((cMemberName > 0) &&
				(cCode > 0) &&
				(vecPhone.size() > 0)))
			{
				break;
			}

			for (i = iBegin; ;++i)
			{
				szChars[0] = cMemberName;
				strName.Format("%s%d", szChars, i);
				if (cCode != 0)
				{
					szChars[0] = cCode;
					strCode.Format("%s%d", szChars, i);
					RangePtr rangeCode = worksheet->GetRange(_variant_t(strCode), _variant_t(strCode));
					strCode = (LPCTSTR)(_bstr_t)(rangeCode->GetValue2());
					strCode.MakeUpper();
				}


				RangePtr rangeName = worksheet->GetRange(_variant_t(strName), _variant_t(strName));
				strName = (LPCTSTR)(_bstr_t)(rangeName->GetValue2());

				vector<char>::iterator it = vecPhone.begin();
				CString strPhone;
				for (; it != vecPhone.end(); ++it)
				{
					szChars[0] = *it;
					strTemp.Format("%s%d", szChars, i);
					RangePtr rangePhone = worksheet->GetRange(_variant_t(strTemp), _variant_t(strTemp));
					strTemp = (LPCTSTR)(_bstr_t)(rangePhone->GetValue2());
					strTemp.TrimLeft();
					strTemp.TrimRight();
					if (strTemp.IsEmpty() == FALSE)
					{
						strPhone += strTemp;
						strPhone += ";";
					}
				}

				if (strName.IsEmpty() || (strName.Find("合计") > -1))
					break;

				if (cCode == 0)
				{
					if (CheckMemberNameExist(strName) == FALSE)
					{
						InsertMember(strName, "", strPhone, "", "");
					}
				}
				else if (CheckMemberExist(strCode, strOldPhone) == FALSE)
				{
					InsertMember(strName, strCode, strPhone, "", "");
				}
				else
				{
					UpdateMember(strName, strCode, strPhone, strOldPhone);
				}
			}
		}
		pBook->Close();
		pBooks->Close();
	}
	// OnBnClickedButtonSelect();
	AfxMessageBox("导入成功！");
	return TRUE;
}

BOOL CMemberInfoDlg::CheckMemberNameExist(CString strName)
{
	BOOL bFind = FALSE;
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strName.TrimLeft();
		strName.TrimRight();
		strSelect.Format("select membername from memberinfo where membername = '%s'", strName);

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				bFind = TRUE;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);

	return bFind;
}

BOOL CMemberInfoDlg::CheckMemberExist(CString strCode, CString& strOldPhone)
{
	BOOL bFind = FALSE;
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strCode.TrimLeft();
		strCode.TrimRight();
		strSelect.Format("select phone from memberinfo where membercode = '%s'", strCode);

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				strOldPhone = sql_row[0];

				bFind = TRUE;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);

	return bFind;
}

BOOL CMemberInfoDlg::InsertMember(CString strName, CString strCode, CString strPhone, CString strComment, CString strStyle)
{
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strName.TrimLeft();
		strName.TrimRight();
		strCode.TrimLeft();
		strCode.TrimRight();
		strPhone.TrimLeft();
		strPhone.TrimRight();

		strSelect.Format("insert into memberinfo(membername,membercode,phone,comment,memberstyle) values('%s','%s','%s','%s','%s')", strName, strCode, strPhone, strComment, strStyle);

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			mysql_close(&theApp.m_db);
			return TRUE;
		}
	}
	
	mysql_close(&theApp.m_db);
	return FALSE;
}

BOOL CMemberInfoDlg::UpdatePhoneString(CString& strNew, const CString& strOld)
{
	BOOL bUpdate = FALSE;
	vector<CString> vecNew, vecOld;
	GetSplitString(strNew, ",;", vecNew);
	GetSplitString(strOld, ",;", vecOld);
	sort(vecNew.begin(), vecNew.end());
	sort(vecOld.begin(), vecOld.end());
	if (includes(vecOld.begin(), vecOld.end(), vecNew.begin(), vecNew.end()))
		return bUpdate;
	else
		bUpdate = TRUE;
	vector<CString> vecUpdate;
	set_union(vecNew.begin(), vecNew.end(), vecOld.begin(), vecOld.end(), back_inserter(vecUpdate));
	strNew.Empty();
	for (vector<CString>::iterator it = vecUpdate.begin(); it != vecUpdate.end(); ++it)
	{
		strNew += *it;
		strNew += ";";
	}
	return bUpdate;
}

BOOL CMemberInfoDlg::UpdateMember(CString strName, CString strCode, CString strNewPhone, CString strOldPhone)
{
	if (UpdatePhoneString(strNewPhone, strOldPhone) == FALSE)
		return FALSE;

	mysql_init(&theApp.m_db);

	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strName.TrimLeft();
		strName.TrimRight();
		strCode.TrimLeft();
		strCode.TrimRight();
		strNewPhone.TrimLeft();
		strNewPhone.TrimRight();

		strSelect.Format("update memberinfo set phone='%s' where membercode='%s'", strNewPhone, strCode);
		// (membername,membercode,phone) values('%s','%s','%s')", strName, strCode, strPhone);
		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			mysql_close(&theApp.m_db);
			return TRUE;
		}
	}
	mysql_close(&theApp.m_db);
	return FALSE;
}

BOOL CMemberInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
			case VK_RETURN: //回车
				{
					if (pMsg->hwnd == m_editName.m_hWnd)
					{
						OnBnClickedButtonSelect();
					}
				}
				return TRUE;
			case VK_ESCAPE: //ESC  
				return TRUE;
		}
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMemberInfoDlg::OnDblclkListMemberinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int iCode = pNMItemActivate->iItem;
	if (iCode >= 0)
	{
		CUpdateMemberDlg dlg(this, 0);
		// dlg.m_iID = m_List.GetItemData(iCode);
		dlg.m_strID = m_List.GetItemText(iCode, 0);
		dlg.m_strName = m_List.GetItemText(iCode, 1);
		dlg.m_strCode = m_List.GetItemText(iCode, 2);
		dlg.m_strStyle = m_List.GetItemText(iCode, 3);
		dlg.m_strPhone = m_List.GetItemText(iCode, 4);
		dlg.m_strComment = m_List.GetItemText(iCode, 5);
		
		if (dlg.DoModal() == IDOK)
		{
			m_List.SetItemText(iCode, 1, dlg.m_strName);
			m_List.SetItemText(iCode, 2, dlg.m_strCode);
			m_List.SetItemText(iCode, 3, dlg.m_strStyle);
			m_List.SetItemText(iCode, 4, dlg.m_strPhone);
			m_List.SetItemText(iCode, 5, dlg.m_strComment);
		}
	}
}

/*
void CMemberInfoDlg::OnPaint()
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
HBRUSH CMemberInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// HBRUSH hbr;
	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	// if (nCtlColor == IDC_BUTTON_SELECT)
	// return (HBRUSH)afxGlobalData.brBarFace;
	// pDC->SetBkColor(afxGlobalData.clrBarFace);
	// hbr = (HBRUSH)afxGlobalData.brBarFace;
	return hbr;
	/*
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetBkColor(afxGlobalData.clrBarFace);
		hbr = (HBRUSH)afxGlobalData.brBarFace;
		break;
	case CTLCOLOR_EDIT:
		pDC->SetBkColor(afxGlobalData.clrBarFace);
		hbr = (HBRUSH)afxGlobalData.brBarFace;
		break;
	case CTLCOLOR_BTN:
		pDC->SetBkColor(afxGlobalData.clrBarFace);
		hbr = (HBRUSH)afxGlobalData.brBarFace;
		break;
	default:
		break;
	}
	return hbr;
	*/
//}
/*
*/

void CMemberInfoDlg::OnBnClickedButtonNew()
{
	CUpdateMemberDlg dlg(this, 1);
	if (dlg.DoModal() == IDOK)
	{
		/*
		int iCount = m_List.GetItemCount();
		CString strNum;
		strNum.Format("%d", iCount+1);
		m_List.InsertItem(iCount, strNum);
		m_List.SetItemText(iCount, 1, dlg.m_strName);
		m_List.SetItemText(iCount, 2, dlg.m_strCode);
		m_List.SetItemText(iCount, 3, dlg.m_strStyle);
		m_List.SetItemText(iCount, 4, dlg.m_strPhone);
		m_List.SetItemText(iCount, 5, dlg.m_strComment);
		*/
	}
}


void CMemberInfoDlg::OnRclickListMemberinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		menu.LoadMenu(IDR_POPUP_EDIT);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y,this);
	}
}


void CMemberInfoDlg::OnEditCopy()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	CString strTemp;
	if (iSelect != -1)
	{
		for (int i = 0; i < 5; ++i)
		{
			CString str = m_List.GetItemText(iSelect, i);
			str.TrimLeft();
			str.TrimRight();
			if (str.IsEmpty() == FALSE)
			{
				strTemp += str;
				strTemp += "\t";
			}
		}
		if (strTemp.IsEmpty() == FALSE)
		{
			strTemp.Delete(strTemp.GetLength()-1);
		}

		if (OpenClipboard())
		{
			EmptyClipboard();
			HANDLE hClip;
			hClip = GlobalAlloc(GMEM_MOVEABLE, strTemp.GetLength()+1); 
			char *pBuf = (char*)GlobalLock(hClip);
			strcpy_s(pBuf, strTemp.GetLength()+1, strTemp);
			SetClipboardData(CF_TEXT, hClip);
			GlobalUnlock(hClip);
			CloseClipboard();
		}
	}

}


void CMemberInfoDlg::OnEditDelete()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		if (AfxMessageBox("你确定删除吗?", MB_OKCANCEL) == IDOK)
		{
			CString strID = m_List.GetItemText(iSelect, 0);
			CString strSQL;
			strSQL.Format("delete from memberinfo where memberid=%s", strID);
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
