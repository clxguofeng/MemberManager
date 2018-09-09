// YibaoSumReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "YibaoSumReportDlg.h"
#include "afxdialogex.h"


// CYibaoSumReportDlg 对话框

IMPLEMENT_DYNAMIC(CYibaoSumReportDlg, CDialogEx)

CYibaoSumReportDlg::CYibaoSumReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYibaoSumReportDlg::IDD, pParent)
{

}

CYibaoSumReportDlg::~CYibaoSumReportDlg()
{
}

void CYibaoSumReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CYibaoSumReportDlg, CDialogEx)
END_MESSAGE_MAP()


// CYibaoSumReportDlg 消息处理程序


BOOL CYibaoSumReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("类别"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(1, _T("人数"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, _T("合计(元)"), LVCFMT_LEFT, 150);
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
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CYibaoSumReportDlg::InitList()
{
	BOOL bRet = FALSE;
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		// 查询
		int res = mysql_query(&theApp.m_db, m_strSQL);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			int iColumnNums = mysql_num_fields(result);
			int i = 0;
			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				m_List.InsertItem(i, sql_row[0]);
				m_List.SetItemText(i, 1, sql_row[1]);
				m_List.SetItemText(i, 2, sql_row[2]);
				++i;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);

			bRet = TRUE;
		}
	}

	mysql_close(&theApp.m_db);
	if (bRet == FALSE)
	{
		AfxMessageBox("读取数据库失败!");
	}
}