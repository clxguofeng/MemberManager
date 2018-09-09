// YaoLaoButieDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "YaoLaoButieDlg.h"
#include "afxdialogex.h"


// CYaoLaoButieDlg 对话框

IMPLEMENT_DYNAMIC(CYaoLaoButieDlg, CDialogEx)

CYaoLaoButieDlg::CYaoLaoButieDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYaoLaoButieDlg::IDD, pParent)
{

}

CYaoLaoButieDlg::~CYaoLaoButieDlg()
{
}

void CYaoLaoButieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DATE, m_cmbStyle);
	DDX_Control(pDX, IDC_COMBO_STATE, m_cmbState);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_cmbSelect);
	DDX_Control(pDX, IDC_DATETIME_BEGIN, m_dtBegin);
	DDX_Control(pDX, IDC_DATETIME_END, m_dtEnd);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editSelect);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CYaoLaoButieDlg, CDialogEx)
END_MESSAGE_MAP()


// CYaoLaoButieDlg 消息处理程序


BOOL CYaoLaoButieDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cmbStyle.InsertString(0, "年");
	m_cmbStyle.InsertString(1, "月");
	m_cmbStyle.InsertString(2, "日");
	m_cmbStyle.SetCurSel(0);

	m_cmbState.InsertString(0, "有效");
	m_cmbState.InsertString(1, "无效");
	m_cmbState.SetCurSel(0);

	m_cmbSelect.InsertString(0, "姓名");
	m_cmbSelect.InsertString(1, "身份证");
	m_vecSelect.push_back("membername");
	m_vecSelect.push_back("membercode");
	m_cmbSelect.SetCurSel(0);

	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("ID号"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(2, _T("姓名"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(3, _T("身份证"), LVCFMT_LEFT, 180);
	m_List.InsertColumn(4, _T("联系方式"), LVCFMT_LEFT, 180);
	m_List.InsertColumn(5, _T("登记日期"), LVCFMT_LEFT, 200);
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CYaoLaoButieDlg::Init()
{

}

CString CYaoLaoButieDlg::GetWhere()
{
	int iSel = m_cmbStyle.GetCurSel();
	CTime timeBegin, timeEnd;
	m_dtBegin.GetTime(timeBegin);
	m_dtEnd.GetTime(timeEnd);
	int iYearBegin = timeBegin.GetYear();
	int iYearEnd = timeEnd.GetYear();
	CString strWhere;
	CString strValue;
	if (iSel == 0)
	{
		strWhere.Format("updatetime > '%d' and updatetime < '%d'", iYearBegin, iYearEnd+1);
	}
	else if (iSel == 1)
	{
		int iMonthBegin = timeBegin.GetMonth();
		int iMonthEnd = timeEnd.GetMonth();

		if (iMonthEnd == 12)
		{
			++iYearEnd;
			iMonthEnd = 1;
		}
		else
		{
			++iMonthEnd;
		}
		strWhere.Format("updatetime > '%d-%02d' and updatetime < '%d-%02d'", iYearBegin, iMonthBegin, iYearEnd, iMonthEnd);
	}
	else
	{
		int iMonthBegin = timeBegin.GetMonth();
		int iDayBegin = timeBegin.GetDay();

		CTime timeDayEnd = timeEnd + CTimeSpan(1, 0, 0, 0);
		iYearEnd = timeDayEnd.GetYear();
		int iMonthEnd = timeDayEnd.GetMonth();
		int iDayEnd = timeDayEnd.GetDay();

		strWhere.Format("updatetime > '%d-%02d-%02d' and updatetime < '%d-%02d-%02d'", 
			iYearBegin, iMonthBegin, iDayBegin,
			iYearEnd, iMonthEnd, iDayEnd);
	}

	CString strSelect;
	m_editSelect.GetWindowText(strSelect);
	strSelect.Trim();
	if (strSelect.IsEmpty() == FALSE)
	{
		int iStyleSel = m_cmbStyle.GetCurSel();
		strValue.Format(" and %s like '%%%s%%'", m_vecSelect[iStyleSel], strSelect);
		strWhere += strValue;
	}
	return strWhere;
}