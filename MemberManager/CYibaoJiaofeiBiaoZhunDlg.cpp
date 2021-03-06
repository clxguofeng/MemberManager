// CYibaoJiaofeiBiaoZhunDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "CYibaoJiaofeiBiaoZhunDlg.h"
#include "UpdateYibaoBiaozhunDlg.h"
#include "afxdialogex.h"


// CYibaoJiaofeiBiaoZhunDlg 对话框

IMPLEMENT_DYNAMIC(CYibaoJiaofeiBiaoZhunDlg, CMFCDialog)

CYibaoJiaofeiBiaoZhunDlg::CYibaoJiaofeiBiaoZhunDlg(CWnd* pParent /*=nullptr*/)
	: CMFCDialog(IDD_DIALOG_YILIAO_JIAOFEIBIAOZHUN, pParent)
{

}

CYibaoJiaofeiBiaoZhunDlg::~CYibaoJiaofeiBiaoZhunDlg()
{
}

void CYibaoJiaofeiBiaoZhunDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO_YEAR, m_combYear);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CYibaoJiaofeiBiaoZhunDlg, CMFCDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CYibaoJiaofeiBiaoZhunDlg::OnNMRClickList)
	ON_COMMAND(ID_CERTIFY_UPDATE, &CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonUpdate)
	ON_COMMAND(ID_CERTIFY_DELETE, &CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CYibaoJiaofeiBiaoZhunDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CYibaoJiaofeiBiaoZhunDlg 消息处理程序


void CYibaoJiaofeiBiaoZhunDlg::OnSize(UINT nType, int cx, int cy)
{
	CMFCDialog::OnSize(nType, cx, cy);
	if (m_List.m_hWnd)
		m_List.MoveWindow(10, 50, cx - 20, cy - 50 - 10);
	// TODO: 在此处添加消息处理程序代码
}


BOOL CYibaoJiaofeiBiaoZhunDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);  
	m_List.InsertColumn(1, _T("年"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, _T("交费类型"), LVCFMT_LEFT, 180);
	m_List.InsertColumn(3, _T("金额"), LVCFMT_LEFT, 60);
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

	int iYear = 2010;
	CTime curTime = CTime::GetCurrentTime();
	for (int i = 0; i < 100; ++i)
	{
		CString strYear;
		strYear.Format("%d年", iYear+i);
		m_combYear.AddString(strYear);
	}

	int iCursel = curTime.GetYear() - iYear;
	m_combYear.SetCurSel(iCursel);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonSelect()
{
	m_List.DeleteAllItems();
	CString strSQL;
	int iYear = m_combYear.GetCurSel()+2010;
	int iLine  = 0;
	strSQL.Format("select yibaostyle,yibaoyear,yibaostylename,yibaocost from yibaostyle where yibaoyear='%d' order by yibaostyle", iYear);

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

			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{ 
				m_List.InsertItem(iLine, sql_row[0]);
				m_List.SetItemText(iLine, 1, sql_row[1]);
				m_List.SetItemText(iLine, 2, sql_row[2]);
				m_List.SetItemText(iLine, 3, sql_row[3]);
				++iLine;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}


void CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonNew()
{
	CUpdateYibaoBiaozhunDlg dlg(1);
	if (dlg.DoModal() == IDOK)
	{
		CString strSQL;
		strSQL.Format("select yibaostyle from yibaostyle where yibaoyear='%d' and yibaostyle=%d", dlg.m_iYear, dlg.m_iStyle);
		if (CheckCurYearExistYibao(strSQL))
		{
			AfxMessageBox("已经存在该交费标准,请重新录入！");
			return;
		}
		strSQL.Format("insert into yibaostyle(yibaostyle,yibaoyear,yibaostylename,yibaocost,yibaoreportflag) values(%d,'%d','%s',%s,1)", dlg.m_iStyle,dlg.m_iYear,dlg.m_strStyle,dlg.m_strMoney);
		if (ExecuteDBSQL(strSQL))
		{
			OnBnClickedButtonSelect();
			AfxMessageBox("新增成功！");
		}
		else
			AfxMessageBox("新增失败！");
	}
}


void CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonUpdate()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CString strid = m_List.GetItemText(iSelect, 0);
		CString strYear = m_List.GetItemText(iSelect, 1);
		CString strMoney = m_List.GetItemText(iSelect, 3);
		CUpdateYibaoBiaozhunDlg dlg(0);
		dlg.m_iYear= atoi(strYear);
		dlg.m_iStyle = atoi(strid);
		dlg.m_strMoney = strMoney;
		if (dlg.DoModal() == IDOK)
		{
			CString strSQL;
			strSQL.Format("update yibaostyle set yibaocost=%s where yibaostyle=%d and yibaoyear='%d'", dlg.m_strMoney,dlg.m_iStyle,dlg.m_iYear);
			if (ExecuteDBSQL(strSQL))
			{
				OnBnClickedButtonSelect();
				AfxMessageBox("修改成功！");
			}
			else
				AfxMessageBox("修改失败！");
		}
	}
}


void CYibaoJiaofeiBiaoZhunDlg::OnBnClickedButtonDelete()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CString strid = m_List.GetItemText(iSelect, 0);
		CString strYear = m_List.GetItemText(iSelect, 1);
		CString strSQL;
		strSQL.Format("delete from yibaostyle where yibaostyle=%s and yibaoyear='%s'",strid, strYear);
		if (ExecuteDBSQL(strSQL))
		{
			OnBnClickedButtonSelect();
			AfxMessageBox("删除成功！");
		}
		else
			AfxMessageBox("删除失败！");
		
	}
}


void CYibaoJiaofeiBiaoZhunDlg::OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult)
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


void CYibaoJiaofeiBiaoZhunDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedButtonUpdate();
	*pResult = 0;
}
