// SelectYibaoMemberDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "SelectYibaoMemberDlg.h"
#include "afxdialogex.h"


// CSelectYibaoMemberDlg �Ի���

IMPLEMENT_DYNAMIC(CSelectYibaoMemberDlg, CMFCDialog)

CSelectYibaoMemberDlg::CSelectYibaoMemberDlg(CString strName, CWnd* pParent /*=NULL*/)
	: CMFCDialog(CSelectYibaoMemberDlg::IDD, pParent)
{
	m_strName = strName;
	m_strName.Trim();
}

CSelectYibaoMemberDlg::~CSelectYibaoMemberDlg()
{
}

void CSelectYibaoMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_CODE, m_editCode);
}


BEGIN_MESSAGE_MAP(CSelectYibaoMemberDlg, CMFCDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CSelectYibaoMemberDlg::OnBnClickedButtonSelect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CSelectYibaoMemberDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDOK, &CSelectYibaoMemberDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectYibaoMemberDlg ��Ϣ�������


BOOL CSelectYibaoMemberDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("���"), LVCFMT_LEFT, 60);  
	m_List.InsertColumn(1, _T("����"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, _T("���֤"), LVCFMT_LEFT, 180);
	m_List.InsertColumn(3, _T("��ϵ��ʽ"), LVCFMT_LEFT, 180);
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
	m_editName.SetWindowText(m_strName);
	Init();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSelectYibaoMemberDlg::Init()
{
	m_List.DeleteAllItems();
	m_editName.GetWindowText(m_strName);
	m_editCode.GetWindowText(m_strCode);

	m_strName.Trim();
	m_strCode.Trim();

	int iRow = 0;
	CString strRow;
	mysql_init(&theApp.m_db);
	YibaoStyle yibaostyle;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;

		if (m_strName.IsEmpty() && m_strCode.IsEmpty())
			strSelect.Format("select membername,membercode,phone from memberinfo");
		else if (m_strName.IsEmpty() == FALSE)
			strSelect.Format("select membername,membercode,phone from memberinfo where membername like '%%%s%%'", m_strName);
		else
			strSelect.Format("select membername,membercode,phone from memberinfo where membercode like '%%%s%%'", m_strCode);
		// ��ѯ
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// ��ȡ��������� 
			while (sql_row = mysql_fetch_row(result)) 
			{
				strRow.Format("%d", iRow+1);
				m_List.InsertItem(iRow, strRow);
				m_List.SetItemText(iRow, 1, sql_row[0]);
				m_List.SetItemText(iRow, 2, sql_row[1]);
				m_List.SetItemText(iRow, 3, sql_row[2]);
				++iRow;
			}

			//�ͷŽ����Դ
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
	int iSize = m_List.GetItemCount();
	if (iSize > 0)
	{
		m_List.SetFocus();
		m_List.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}
	
	if (iRow == 0)
	{
		CMFCDialog::OnCancel();
		AfxMessageBox("û���ҵ���");
	}
}

void CSelectYibaoMemberDlg::OnBnClickedButtonSelect()
{
	Init();
}


BOOL CSelectYibaoMemberDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam) 
		{
		case VK_RETURN: //�س�
			{
				if ((pMsg->hwnd == m_editName.m_hWnd) ||
					(pMsg->hwnd == m_editCode.m_hWnd))
				{
					Init();
				}
				else if (pMsg->hwnd == m_List.m_hWnd)
				{
					int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
					if (iSelect != -1)
					{
						m_strName = m_List.GetItemText(iSelect, 1);
						m_strCode = m_List.GetItemText(iSelect, 2);
						m_strPhone = m_List.GetItemText(iSelect, 3);
						OnOK();
					}
				}
			}
			return TRUE;
		/*
		case VK_ESCAPE: //ESC  
			return TRUE;
		*/
		}
	}
	return CMFCDialog::PreTranslateMessage(pMsg);
}



void CSelectYibaoMemberDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iCode = pNMItemActivate->iItem;
	if (iCode >= 0)
	{
		m_strName = m_List.GetItemText(iCode, 1);
		m_strCode = m_List.GetItemText(iCode, 2);
		m_strPhone = m_List.GetItemText(iCode, 3);
		OnOK();
	}
	*pResult = 0;
}


void CSelectYibaoMemberDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		m_strName = m_List.GetItemText(iSelect, 1);
		m_strCode = m_List.GetItemText(iSelect, 2);
		m_strPhone = m_List.GetItemText(iSelect, 3);
		CMFCDialog::OnOK();
	}
	else
	{
		AfxMessageBox("��ѡ��һ������!");
	}
}
