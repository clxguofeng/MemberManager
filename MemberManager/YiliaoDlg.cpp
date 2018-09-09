// YiliaoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "YiliaoDlg.h"
#include "afxdialogex.h"
#include "AddYibaoDlg.h"
#include "UpdateYibaoDlg.h"
#include "YibaoSumReportDlg.h"

// CYiliaoDlg 对话框

IMPLEMENT_DYNAMIC(CYiliaoDlg, CDialogEx)

CYiliaoDlg::CYiliaoDlg(CWnd* pParent /*=NULL*/)
	: CMFCDialog(IDD, pParent)
{
	m_iSel = -1;
	m_bChange = TRUE;
	m_bRefresh = FALSE;
}

CYiliaoDlg::~CYiliaoDlg()
{
}

void CYiliaoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_SelectBtn);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnAdd);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_cmbStyle);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editSelect);
	DDX_Control(pDX, IDC_DATETIME_END, m_dtEnd);
	DDX_Control(pDX, IDC_DATETIME_BEGIN, m_dtBegin);
	DDX_Control(pDX, IDC_COMBO_DATE, m_cmbDateStyle);
	DDX_Control(pDX, IDC_COMBO_YIBAOSTYLE, m_cmbYibaoStyle);
	DDX_Control(pDX, IDC_BUTTON_SELECT_EXPORT, m_btnSelectExport);
	DDX_Control(pDX, IDC_BUTTON_SUM_EXPORT, m_btnSumExport);
	DDX_Control(pDX, IDC_COMBO_STATE, m_cmbState);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BUTTON_SUM, m_btnSum);
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_btnRefresh);
	DDX_Control(pDX, IDC_CHECK_UPDATETIME, m_checkUpdatetime);
	DDX_Control(pDX, IDC_COMBO_USER, m_cmbUser);
}


BEGIN_MESSAGE_MAP(CYiliaoDlg, CMFCDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CYiliaoDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CYiliaoDlg::OnBnClickedButtonSelect)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CYiliaoDlg::OnNMRClickList)
	ON_COMMAND(ID_YIBAO_UPDATE, &CYiliaoDlg::OnYibaoUpdate)
	ON_COMMAND(ID_YIBAO_DELETE, &CYiliaoDlg::OnYibaoDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CYiliaoDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_EXPORT, &CYiliaoDlg::OnBnClickedButtonSelectExport)
	ON_BN_CLICKED(IDC_BUTTON_SUM_EXPORT, &CYiliaoDlg::OnBnClickedButtonSumExport)
	ON_COMMAND(ID_YIBAO_CANCEL, &CYiliaoDlg::OnYibaoCancel)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CYiliaoDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_SUM, &CYiliaoDlg::OnBnClickedButtonSum)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CYiliaoDlg::OnBnClickedButtonRefresh)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_DATE, &CYiliaoDlg::OnSelchangeComboDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_BEGIN, &CYiliaoDlg::OnDatetimechangeDatetimeBegin)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_END, &CYiliaoDlg::OnDatetimechangeDatetimeEnd)
	ON_CBN_SELCHANGE(IDC_COMBO_STATE, &CYiliaoDlg::OnSelchangeComboState)
	ON_CBN_SELCHANGE(IDC_COMBO_YIBAOSTYLE, &CYiliaoDlg::OnSelchangeComboYibaostyle)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, &CYiliaoDlg::OnSelchangeComboStyle)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CYiliaoDlg::OnChangeEditName)
END_MESSAGE_MAP()


// CYiliaoDlg 消息处理程序


void CYiliaoDlg::OnSize(UINT nType, int cx, int cy)
{
	CMFCDialog::OnSize(nType, cx, cy);

	if (m_List.m_hWnd)
		m_List.MoveWindow(10, 100, cx - 20, cy - 100 - 10);
}



void CYiliaoDlg::OnBnClickedButtonNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddYibaoDlg dlg(this, &m_vecYibaoStyle);
	dlg.DoModal();
}


BOOL CYiliaoDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();
	m_cmbState.InsertString(0, "有效");
	m_cmbState.InsertString(1, "退保");
	m_cmbState.InsertString(2, "无效");
	m_cmbState.SetCurSel(0);

	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("ID号"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(2, _T("单号"), LVCFMT_LEFT, 50); 
	m_List.InsertColumn(3, _T("姓名"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(4, _T("身份证"), LVCFMT_LEFT, 160);
	m_List.InsertColumn(5, _T("类型"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(6, _T("金额"), LVCFMT_LEFT, 60);
	m_List.InsertColumn(7, _T("低保号"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(8, _T("联系方式"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(9, _T("登记日期"), LVCFMT_LEFT, 170);
	m_List.InsertColumn(10, _T("退保日期"), LVCFMT_LEFT, 170);
	m_List.InsertColumn(11, _T("操作员"), LVCFMT_LEFT, 60);
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
	InitCombo();
	m_checkUpdatetime.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CYiliaoDlg::Init()
{
	mysql_init(&theApp.m_db);
	YibaoStyle yibaostyle;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		CTime curtime = CTime::GetCurrentTime();
		strSelect.Format("SELECT yibaostyle,yibaostylename,yibaocost FROM yibaostyle where yibaoyear='%d' order by yibaostyle", curtime.GetYear());

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				yibaostyle.iYibaoStyleID = atoi(sql_row[0]);
				yibaostyle.strYibaoStyle = sql_row[1];
				yibaostyle.iYibaoCost = atoi(sql_row[2]);
				m_vecYibaoStyle.push_back(yibaostyle);
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
		//////////////////////////////////////////////////////////////////////////
		/// 获取操作员列表
		strSelect.Format("select username from userlogin where username <> 'admin'");

		// 查询
		res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				m_vecUser.push_back(sql_row[0]);
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

void CYiliaoDlg::InitCombo()
{
	m_cmbStyle.InsertString(0, "姓名");
	m_cmbStyle.InsertString(1, "身份证");
	m_vecComboStyle.push_back("membername");
	m_vecComboStyle.push_back("membercode");
	m_cmbStyle.SetCurSel(0);

	m_cmbYibaoStyle.InsertString(0, "所有人");
	int iSize = m_vecYibaoStyle.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_cmbYibaoStyle.InsertString(i+1, m_vecYibaoStyle[i].strYibaoStyle);
	}
	m_cmbYibaoStyle.SetCurSel(0);

	m_cmbDateStyle.InsertString(0, "年");
	m_cmbDateStyle.InsertString(1, "月");
	m_cmbDateStyle.InsertString(2, "日");
	m_cmbDateStyle.SetCurSel(0);

	iSize = m_vecUser.size();
	m_cmbUser.InsertString(0, "所有人");
	for (int i = 0; i < iSize; ++i)
	{
		m_cmbUser.InsertString(i+1, m_vecUser[i]);
	}
	m_cmbUser.SetCurSel(0);
}

void CYiliaoDlg::OnBnClickedButtonSelect()
{
	InitList();
}

CString CYiliaoDlg::GetWhere(CString& strTitle)
{
	int iSel = m_cmbDateStyle.GetCurSel();
	CTime timeBegin, timeEnd;
	m_dtBegin.GetTime(timeBegin);
	m_dtEnd.GetTime(timeEnd);
	int iYearBegin = timeBegin.GetYear();
	int iYearEnd = timeEnd.GetYear();
	CString strWhere;
	CString strValue;
	CString strTime;
	int iCursel = m_cmbState.GetCurSel();
	if (iCursel == 0)
		strTime = "yibaotime";
	else if (m_checkUpdatetime.GetCheck())
		strTime = "yibaoupdatetime";
	else
		strTime = "yibaotime";

	if (iSel == 0)
	{
		strWhere.Format("%s > '%d' and %s < '%d'", strTime, iYearBegin, strTime, iYearEnd+1);
		if (iYearBegin == iYearEnd)
			strTitle.Format("%d年", iYearBegin);
		else
			strTitle.Format("%d年至%d", iYearBegin, iYearEnd);
	}
	else if (iSel == 1)
	{
		int iMonthBegin = timeBegin.GetMonth();
		int iMonthEnd = timeEnd.GetMonth();

		if ((iYearBegin == iYearEnd) && (iMonthBegin == iMonthEnd))
			strTitle.Format("%d年%02d月", iYearBegin, iMonthBegin);
		else
			strTitle.Format("%d年%02d月至%d年%02d月", iYearBegin, iMonthBegin, iYearEnd, iMonthEnd);

		if (iMonthEnd == 12)
		{
			++iYearEnd;
			iMonthEnd = 1;
		}
		else
		{
			++iMonthEnd;
		}
		strWhere.Format("%s > '%d-%02d' and %s < '%d-%02d'", strTime, iYearBegin, iMonthBegin, strTime, iYearEnd, iMonthEnd);
	}
	else
	{
		int iMonthBegin = timeBegin.GetMonth();
		int iDayBegin = timeBegin.GetDay();

		if (timeBegin == timeEnd)
			strTitle.Format("%d%02d%02d", iYearBegin, iMonthBegin, iDayBegin);
		else
			strTitle.Format("%d%02d%02d至%d%02d%02d", iYearBegin,iMonthBegin,iDayBegin,timeEnd.GetYear(),timeEnd.GetMonth(),timeEnd.GetDay());

		CTime timeDayEnd = timeEnd + CTimeSpan(1, 0, 0, 0);
		iYearEnd = timeDayEnd.GetYear();
		int iMonthEnd = timeDayEnd.GetMonth();
		int iDayEnd = timeDayEnd.GetDay();

		strWhere.Format("%s > '%d-%02d-%02d' and %s < '%d-%02d-%02d'", 
			strTime, iYearBegin, iMonthBegin, iDayBegin,
			strTime, iYearEnd, iMonthEnd, iDayEnd);
	}

	int iYibaoStyleSel = m_cmbYibaoStyle.GetCurSel();
	if (iYibaoStyleSel > 0)
	{
		strValue.Format(" and yibao.yibaostyle=%d", m_vecYibaoStyle[iYibaoStyleSel-1].iYibaoStyleID);
		strWhere += strValue;
	}

	CString strSelect;
	m_editSelect.GetWindowText(strSelect);
	strSelect.Trim();
	if (strSelect.IsEmpty() == FALSE)
	{
		int iStyleSel = m_cmbStyle.GetCurSel();
		strValue.Format(" and %s like '%%%s%%'", m_vecComboStyle[iStyleSel], strSelect);
		strWhere += strValue;
	}
	if (m_cmbUser.GetCurSel() > 0)
	{
		CString strUser;
		m_cmbUser.GetWindowText(strUser);
		strSelect.Format(" and author='%s'", strUser);
		strWhere += strSelect;
	}
	return strWhere;
}

void CYiliaoDlg::InitList()
{
	m_List.DeleteAllItems();
	CString strTitle;
	CString strWhere = GetWhere(strTitle);

	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select yibaoid,yibaodanju,membername,membercode,memberphone,yibao.yibaostyle,dibaocode,yibaostylename,"
			"yibaocost,yibaotime,yibaoupdatetime,author from yibao left join yibaostyle on yibaostyle.yibaostyle=yibao.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status = %d",
			strWhere, m_cmbState.GetCurSel()+1);

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			m_iSel = m_cmbState.GetCurSel();
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			int iRow = 0;
			CString strValue;
			while (sql_row = mysql_fetch_row(result)) 
			{
				strValue.Format("%d", iRow+1);
				m_List.InsertItem(iRow, strValue);
				m_List.SetItemText(iRow, 1, sql_row[0]);
				m_List.SetItemText(iRow, 2, sql_row[1]);
				m_List.SetItemText(iRow, 3, sql_row[2]);
				m_List.SetItemText(iRow, 4, sql_row[3]);
				m_List.SetItemText(iRow, 5, sql_row[7]);
				m_List.SetItemText(iRow, 6, sql_row[8]);
				m_List.SetItemText(iRow, 7, sql_row[6]);
				m_List.SetItemText(iRow, 8, sql_row[4]);
				m_List.SetItemText(iRow, 9, sql_row[9]);
				m_List.SetItemText(iRow, 10, sql_row[10]);
				m_List.SetItemText(iRow, 11, sql_row[11]);
				m_List.SetItemData(iRow, atoi(sql_row[5]));
				++iRow;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);

	m_bChange = FALSE;
}

void CYiliaoDlg::OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if ((m_iSel == 0) && (iSelect != -1))
	{
		CPoint point;
		GetCursorPos(&point);
		CMenu menu;
		menu.LoadMenu(IDR_MENU_YIBAO_LIST);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y,this);
	}

	*pResult = 0;
}

void CYiliaoDlg::OnYibaoUpdate()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CUpdateYibaoDlg dlg;
		CString strYibaoid = m_List.GetItemText(iSelect, 1);
		dlg.m_strName = m_List.GetItemText(iSelect, 3);
		dlg.m_strCode = m_List.GetItemText(iSelect, 4);
		dlg.m_strDibao = m_List.GetItemText(iSelect, 7);
		dlg.m_strPhone = m_List.GetItemText(iSelect, 8);
		int iStyleid = m_List.GetItemData(iSelect);
		int iSize = m_vecYibaoStyle.size();
		dlg.m_iSel = 0;
		for (int i = 0; i < iSize; ++i)
		{
			if (m_vecYibaoStyle[i].iYibaoStyleID == iStyleid)
			{
				dlg.m_iSel = i;
				break;
			}
		}
		
		dlg.m_pvecYibaoStyle = &m_vecYibaoStyle;
		if (dlg.DoModal() == IDOK)
		{
			CString strSQL;

			CString strDibaoCode;
			if ((dlg.m_iSel == 2) || (dlg.m_iSel == 3) || (dlg.m_iSel == 4))
				strDibaoCode = dlg.m_strDibao;
			else
				strDibaoCode.Empty();

			strSQL.Format("update yibao set membercode='%s',membername='%s',memberphone='%s',yibaostyle=%d,dibaocode='%s',author='%s' where yibaoid=%s",
				dlg.m_strCode,dlg.m_strName,dlg.m_strPhone,m_vecYibaoStyle[dlg.m_iSel].iYibaoStyleID,strDibaoCode,theApp.m_strUser,strYibaoid);
			
			if (ExecuteDBSQL(strSQL))
			{
				InitList();
			}
			else
			{
				AfxMessageBox("修改失败!");
			}
		}
	}
}


void CYiliaoDlg::OnYibaoDelete()
{
	CString strSQL;
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED);
	if (iSelect != -1)
	{
		if (AfxMessageBox("你确定删除吗?", MB_OKCANCEL) == IDOK)
		{
			CString strYibaoid = m_List.GetItemText(iSelect, 1);
			strSQL.Format("update yibao set status=3,yibaoupdatetime=now(),author='%s' where yibaoid=%s", theApp.m_strUser,strYibaoid);
			if (ExecuteDBSQL(strSQL))
			{
				InitList();
			}
			else
			{
				AfxMessageBox("删除失败!");
			}
		}
	}
}


void CYiliaoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnYibaoUpdate();
	*pResult = 0;
}


BOOL CYiliaoDlg::PreTranslateMessage(MSG* pMsg)
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
					InitList();
				}
			}
			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	} 
	return CMFCDialog::PreTranslateMessage(pMsg);
}


void CYiliaoDlg::OnBnClickedButtonSelectExport()
{
	CString strSQL,strZiDuan,strWhere,strTitle,strValue;
	strWhere = GetWhere(strValue);
	int iSel = m_cmbState.GetCurSel();

	strSQL.Format("SELECT @rownum:=@rownum+1 id,yibaodanju,membername,membercode,memberphone,dibaocode,yibaostylename,yibaocost \
				  FROM (SELECT @rownum:=0) r, yibao left join yibaostyle on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d and yibaoreportflag=1", strWhere,iSel+1);	
	CString strName;
	if (iSel == 0)
		strName = "医保交费明细";
	else if (iSel == 1)
		strName = "医保退费明细";
	else
		strName = "医保删除明细";
	strTitle.Format("%s%s",strValue,strName);

	CExportExcelDlg::ExportExcel(strSQL, EXPORT_YIBAO_MINGXI_FIELDNAME, strTitle, strName, EXPORT_YIBAO_MINGXI_WIDTH);
}


void CYiliaoDlg::OnBnClickedButtonSumExport()
{
	CString strSQL,strZiDuan,strWhere,strTitle,strValue;
	int iSel = m_cmbState.GetCurSel();
	strWhere = GetWhere(strValue);
	strSQL.Format("select yibaostylename,count(yibaocost) yibaonum,sum(yibaocost) yibaocost from yibao left join yibaostyle \
		on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d and yibaoreportflag=1 group by yibaostyle.yibaostyle union all select '合计',\
		count(yibaocost),sum(yibaocost) from yibao left join yibaostyle \
		on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d and yibaoreportflag=1",strWhere,iSel+1,strWhere,iSel+1);
	CString strName;
	if (iSel == 0)
		strName = "医保交费合计";
	else if (iSel == 1)
		strName = "医保退费合计";
	else
		strName = "医保删除合计";

	strTitle.Format("%s%s",strValue,strName);
	CExportExcelDlg::ExportExcel(strSQL, "类别,人数,合计", strTitle, strName, "30,20,20");
}


void CYiliaoDlg::OnYibaoCancel()
{
	CString strSQL;
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED);
	if (iSelect != -1)
	{
		if (AfxMessageBox("你确定退保吗?", MB_OKCANCEL) == IDOK)
		{
			CString strYibaoid = m_List.GetItemText(iSelect, 1);
			strSQL.Format("update yibao set status=2,author='%s',yibaoupdatetime=now() where yibaoid=%s", theApp.m_strUser,strYibaoid);
			if (ExecuteDBSQL(strSQL))
			{
				InitList();
			}
			else
			{
				AfxMessageBox("退保失败!");
			}
		}
	}
}


void CYiliaoDlg::OnBnClickedButtonExport()
{
	CString strSQL,strZiDuan,strWhere,strTitle,strValue;
	int iSel = m_cmbState.GetCurSel();
	strWhere = GetWhere(strValue);

	strSQL.Format("SELECT @rownum:=@rownum+1 id,yibaodanju,membername,membercode,memberphone,dibaocode,yibaostylename,yibaocost \
				  FROM (SELECT @rownum:=0) r, yibao left join yibaostyle on yibao.yibaostyle=yibaostyle.yibaostyle and \
				  yibaoyear=left(yibao.yibaotime,4) where %s and status=%d and yibaoreportflag=1", strWhere,iSel+1);	

	CString strName, strSumName, strFilename;
	if (iSel == 0)
	{
		strName = "医保交费明细";
		strSumName = "医保交费合计";
		strFilename = "医保交费";
	}
	else if (iSel == 1)
	{
		strName = "医保退费明细";
		strSumName = "医保退费合计";
		strFilename = "医保退费";
	}
	else
	{
		strName = "医保删除明细";
		strSumName = "医保删除合计";
		strFilename = "医保删除";
	}

	SQLEXPORTSTRUCT SqlExportStruct;
	SqlExportStruct.strSQL = strSQL;
	SqlExportStruct.strField = EXPORT_YIBAO_MINGXI_FIELDNAME;
	SqlExportStruct.strWidth = EXPORT_YIBAO_MINGXI_WIDTH;

	strTitle.Format("%s%s",strValue,strName);
	SqlExportStruct.strFilename.Format("%s%s",strValue,strFilename);
	SqlExportStruct.strTitle = strTitle;
	SqlExportStruct.strSheetname = strName;
	vector<SQLEXPORTSTRUCT> vecSQLStruct;
	vecSQLStruct.push_back(SqlExportStruct);

	strSQL.Format("select yibaostylename,count(yibaocost) yibaonum,sum(yibaocost) yibaocost from yibao left join yibaostyle \
				  on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d and yibaoreportflag=1 \
				  group by yibaostyle.yibaostyle union all select '合计',\
				  count(yibaocost),sum(yibaocost) from yibao left join yibaostyle \
				  on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d and yibaoreportflag=1",strWhere,iSel+1,strWhere,iSel+1);

	SqlExportStruct.strSQL = strSQL;
	SqlExportStruct.strField = "类别,人数,合计(元)";
	SqlExportStruct.strWidth = "30,20,20";
	strTitle.Format("%s%s",strValue,strSumName);
	SqlExportStruct.strTitle = strTitle;
	SqlExportStruct.strSheetname = strSumName;
	vecSQLStruct.push_back(SqlExportStruct);
	CExportExcelDlg::ExportExcel(vecSQLStruct);
}


void CYiliaoDlg::OnBnClickedButtonSum()
{
	CString strSQL,strWhere,strValue,strText;
	CString strStyle, strNum;
	int iSel = m_cmbState.GetCurSel();
	strWhere = GetWhere(strValue);
	CYibaoSumReportDlg dlg;
	dlg.m_strSQL.Format("select yibaostylename,count(yibaocost) yibaonum,sum(yibaocost) yibaocost from yibao left join yibaostyle \
				  on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d group by yibaostyle.yibaostyle union all select '合计',\
				  count(yibaocost),sum(yibaocost) from yibao left join yibaostyle \
				  on yibao.yibaostyle=yibaostyle.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status=%d",strWhere,iSel+1,strWhere,iSel+1);

	
	dlg.DoModal();
}


void CYiliaoDlg::OnBnClickedButtonRefresh()
{
	if (m_bRefresh)
	{
		m_btnRefresh.SetWindowText("自动刷新");
		KillTimer(1000);
		m_bRefresh = FALSE;
	}
	else
	{
		m_btnRefresh.SetWindowText("停止");
		SetTimer(1000, 15000, NULL);
		m_bRefresh = TRUE;
	}
}


void CYiliaoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1000)
	{
		RefreshYibaoList();
	}
	CMFCDialog::OnTimer(nIDEvent);
}

void CYiliaoDlg::RefreshYibaoList()
{
	int iCount = m_List.GetItemCount();
	if (m_bChange || (iCount == 0))
	{
		InitList();
	}
	else
	{
		InsertNewList(iCount);
	}
}

void CYiliaoDlg::InsertNewList(int iCount)
{
	CString strID = m_List.GetItemText(iCount - 1, 1);

	CString strTitle;
	CString strWhere = GetWhere(strTitle);

	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;
		MYSQL_ROW sql_row;

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		strSelect.Format("select yibaoid,yibaodanju,membername,membercode,memberphone,yibao.yibaostyle,dibaocode,yibaostylename,"
			"yibaocost,yibaotime,author from yibao left join yibaostyle on yibaostyle.yibaostyle=yibao.yibaostyle and yibaoyear=left(yibao.yibaotime,4) where %s and status = %d and yibaoid > %s",
			strWhere, m_cmbState.GetCurSel() + 1, strID);

		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			m_iSel = m_cmbState.GetCurSel();
			result = mysql_store_result(&theApp.m_db);
			// int j = mysql_num_fields(result);

			// 获取具体的数据 
			int iRow = iCount;
			CString strValue;
			while (sql_row = mysql_fetch_row(result))
			{
				strValue.Format("%d", iRow + 1);
				m_List.InsertItem(iRow, strValue);
				m_List.SetItemText(iRow, 1, sql_row[0]);
				m_List.SetItemText(iRow, 2, sql_row[1]);
				m_List.SetItemText(iRow, 3, sql_row[2]);
				m_List.SetItemText(iRow, 4, sql_row[3]);
				m_List.SetItemText(iRow, 5, sql_row[7]);
				m_List.SetItemText(iRow, 6, sql_row[8]);
				m_List.SetItemText(iRow, 7, sql_row[6]);
				m_List.SetItemText(iRow, 8, sql_row[4]);
				m_List.SetItemText(iRow, 9, sql_row[9]);
				m_List.SetItemText(iRow, 10, sql_row[10]);
				m_List.SetItemData(iRow, atoi(sql_row[5]));
				++iRow;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);

	m_bChange = FALSE;
}

void CYiliaoDlg::OnSelchangeComboDate()
{
	m_bChange = TRUE;
}


void CYiliaoDlg::OnDatetimechangeDatetimeBegin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
	m_bChange = TRUE;
}


void CYiliaoDlg::OnDatetimechangeDatetimeEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	*pResult = 0;
	m_bChange = TRUE;
}


void CYiliaoDlg::OnSelchangeComboState()
{
	m_bChange = TRUE;
	int iCursel = m_cmbState.GetCurSel();
	if (iCursel > 0)
	{
		m_checkUpdatetime.ShowWindow(SW_NORMAL);
		if (iCursel == 1)
			m_checkUpdatetime.SetWindowText("退保时间");
		else
			m_checkUpdatetime.SetWindowText("删除时间");
	}
	else
	{
		m_checkUpdatetime.ShowWindow(SW_HIDE);
	}
}


void CYiliaoDlg::OnSelchangeComboYibaostyle()
{
	m_bChange = TRUE;
}


void CYiliaoDlg::OnSelchangeComboStyle()
{
	m_bChange = TRUE;
}


void CYiliaoDlg::OnChangeEditName()
{
	m_bChange = TRUE;
}
