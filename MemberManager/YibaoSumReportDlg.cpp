// YibaoSumReportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "YibaoSumReportDlg.h"
#include "afxdialogex.h"


// CYibaoSumReportDlg �Ի���

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


// CYibaoSumReportDlg ��Ϣ�������


BOOL CYibaoSumReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("���"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(1, _T("����"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, _T("�ϼ�(Ԫ)"), LVCFMT_LEFT, 150);
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
		// ��ѯ
		int res = mysql_query(&theApp.m_db, m_strSQL);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			int iColumnNums = mysql_num_fields(result);
			int i = 0;
			// ��ȡ��������� 
			while (sql_row = mysql_fetch_row(result)) 
			{
				m_List.InsertItem(i, sql_row[0]);
				m_List.SetItemText(i, 1, sql_row[1]);
				m_List.SetItemText(i, 2, sql_row[2]);
				++i;
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);

			bRet = TRUE;
		}
	}

	mysql_close(&theApp.m_db);
	if (bRet == FALSE)
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!");
	}
}