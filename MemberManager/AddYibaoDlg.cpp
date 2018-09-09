// AddYibaoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemberManager.h"
#include "AddYibaoDlg.h"
#include "afxdialogex.h"
#include "SelectYibaoMemberDlg.h"
#include "UpdateYibaoDlg.h"
#include "YibaoCostHintDlg.h"

// CAddYibaoDlg 对话框

IMPLEMENT_DYNAMIC(CAddYibaoDlg, CDialogEx)

CAddYibaoDlg::CAddYibaoDlg(CYiliaoDlg* pDlg, vector<YibaoStyle>* pVecYibaoStyle, CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddYibaoDlg::IDD, pParent)
{
	m_pDlg = pDlg;
	m_pvecYibaoStyle = pVecYibaoStyle;
}

CAddYibaoDlg::~CAddYibaoDlg()
{
}

void CAddYibaoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_cmbStyle);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_CODE, m_editCode);
	DDX_Control(pDX, IDC_EDIT_NAME2, m_editPhone);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_EDIT_DIBAO, m_editDibao);
	DDX_Control(pDX, IDC_STATIC_SUM, m_staticSum);
}


BEGIN_MESSAGE_MAP(CAddYibaoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddYibaoDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CAddYibaoDlg::OnNMDblclkList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CAddYibaoDlg::OnNMRClickList)
	ON_COMMAND(ID_YIBAO_DELETE, &CAddYibaoDlg::OnYibaoDelete)
	ON_COMMAND(ID_YIBAO_UPDATE, &CAddYibaoDlg::OnYibaoUpdate)
	ON_BN_CLICKED(IDOK, &CAddYibaoDlg::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT_CODE, &CAddYibaoDlg::OnEnKillfocusEditCode)
END_MESSAGE_MAP()


// CAddYibaoDlg 消息处理程序


BOOL CAddYibaoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);  
	m_List.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(2, _T("身份证"), LVCFMT_LEFT, 180);
	m_List.InsertColumn(3, _T("金额"), LVCFMT_LEFT, 60);
	m_List.InsertColumn(4, _T("类型"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(5, _T("低保号"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(6, _T("联系方式"), LVCFMT_LEFT, 180);
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
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAddYibaoDlg::Init()
{
	int iSize = m_pvecYibaoStyle->size();
	for (int i = 0; i < iSize; ++i)
		m_cmbStyle.InsertString(i, (*m_pvecYibaoStyle)[i].strYibaoStyle);

	if (iSize > 0)
		m_cmbStyle.SetCurSel(0);
}

BOOL /*CAddYibaoDlg::*/ CheckCurYearExistYibao(CString strSelect)
{
	BOOL bFind = FALSE;
	mysql_init(&theApp.m_db);
	// YibaoStyle yibaostyle;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");

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
				break;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
	return bFind;
}

BOOL CAddYibaoDlg::CheckValid()
{
	m_iSel = m_cmbStyle.GetCurSel();
	if (m_strName.IsEmpty() || m_strCode.IsEmpty() || m_strCost.IsEmpty())
	{
		AfxMessageBox("内容不能为空!");
		return FALSE;
	}
	else if (((m_iSel == 2) || (m_iSel == 3) || (m_iSel == 4)) && (m_strDibao.IsEmpty()))
	{
		AfxMessageBox("低保号不能为空!");
		m_editDibao.SetFocus();
		return FALSE;
	}
	else
	{
		CString strSelect;
		CString strYibaotime;
		CTime curTime;
		curTime = CTime::GetCurrentTime();
		strYibaotime.Format("%d-01-01", curTime.GetYear());
		strSelect.Format("select yibaoid from yibao where yibaotime > '%s' and membercode like '%%%s%%' and status=1", strYibaotime, m_strCode);

		if (CheckCurYearExistYibao(strSelect))
		{
			AfxMessageBox("已经交过！");
			return FALSE;
		}
		else if (CheckListExist())
		{
			AfxMessageBox("表中已经存在！");
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CAddYibaoDlg::CheckListExist()
{
	int iRow = m_List.GetItemCount();
	for (int i = 0; i < iRow; ++i)
	{
		CString strCode = m_List.GetItemText(i, 2);
		strCode.Trim();
		if (strCode == m_strCode)
			return TRUE;
	}
	return FALSE;
}

BOOL CAddYibaoDlg::PreTranslateMessage(MSG* pMsg)
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
					CString strName;
					m_editName.GetWindowText(strName);
					CSelectYibaoMemberDlg dlg(strName);
					if (dlg.DoModal() == IDOK)
					{
						m_editName.SetWindowText(dlg.m_strName);
						m_editCode.SetWindowText(dlg.m_strCode);
						m_editPhone.GetWindowText(strName);
						strName.Trim();
						int iLen = dlg.m_strPhone.GetLength();
						if ((iLen > 0) && (dlg.m_strPhone[iLen-1] == ';'))
							dlg.m_strPhone.Delete(iLen-1);
							
						if (strName.IsEmpty())
							m_editPhone.SetWindowText(dlg.m_strPhone);

						CheckYear();
						m_btnAdd.SetFocus();
					}
				}
				else if (pMsg->hwnd == m_btnAdd.m_hWnd)
				{
					AddMember();
					SumCost();
				}
			}
			return TRUE;
		case VK_ESCAPE: //ESC  
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CAddYibaoDlg::AddMember()
{
	m_editName.GetWindowText(m_strName);
	m_editCode.GetWindowText(m_strCode);
	m_editPhone.GetWindowText(m_strPhone);
	m_editDibao.GetWindowText(m_strDibao);
	m_strName.Trim();
	m_strCode.Trim();
	m_strPhone.Trim();
	int iSel = m_cmbStyle.GetCurSel();
	if (iSel >= 0)
	{
		m_strCost.Format("%d", (*m_pvecYibaoStyle)[iSel].iYibaoCost);
	}
	int iRow = m_List.GetItemCount();
	if (CheckValid())
	{
		CString strRow;
		strRow.Format("%d", iRow+1);
		m_List.InsertItem(iRow, strRow);
		m_List.SetItemText(iRow, 1, m_strName);
		m_List.SetItemText(iRow, 2, m_strCode);
		m_List.SetItemText(iRow, 3, m_strCost);
		m_List.SetItemText(iRow, 4, (*m_pvecYibaoStyle)[iSel].strYibaoStyle);
		m_List.SetItemText(iRow, 5, m_strDibao);
		m_List.SetItemText(iRow, 6, m_strPhone);
		m_List.SetItemData(iRow, iSel);
		m_editName.SetFocus();
		m_editName.SetWindowText("");
		m_editCode.SetWindowText("");
	}
}

void CAddYibaoDlg::OnBnClickedButtonAdd()
{
	AddMember();
	SumCost();
}


void CAddYibaoDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnYibaoUpdate();
	*pResult = 0;
}


void CAddYibaoDlg::OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CPoint point;
		GetCursorPos(&point);
		CMenu menu;
		menu.LoadMenu(IDR_MENU_YIBAO_LIST);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y,this);
	}
	*pResult = 0;
}

void CAddYibaoDlg::SumCost()
{
	int iSize = m_List.GetItemCount();
	int iSum = 0;
	for (int i = 0; i < iSize; ++i)
	{
		m_strCost = m_List.GetItemText(i, 3);
		iSum += atoi(m_strCost);
	}

	m_strCost.Format("%d元", iSum);
	m_staticSum.SetWindowText(m_strCost);
	m_staticSum.Invalidate(TRUE);
}

void CAddYibaoDlg::OnYibaoDelete()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		m_List.DeleteItem(iSelect);
		int iSize = m_List.GetItemCount();
		CString strNum;
		for (int i = iSelect; i < iSize; ++i)
		{
			strNum.Format("%d", i+1);
			m_List.SetItemText(i, 0, strNum);
		}
	}
	SumCost();
}


void CAddYibaoDlg::OnYibaoUpdate()
{
	int iSelect = m_List.GetNextItem(-1, LVIS_SELECTED); 
	if (iSelect != -1)
	{
		CUpdateYibaoDlg dlg;
		dlg.m_strName = m_List.GetItemText(iSelect, 1);
		dlg.m_strCode = m_List.GetItemText(iSelect, 2);
		dlg.m_strDibao = m_List.GetItemText(iSelect, 5);
		dlg.m_strPhone = m_List.GetItemText(iSelect, 6);
		dlg.m_iSel = m_List.GetItemData(iSelect);
		dlg.m_pvecYibaoStyle = m_pvecYibaoStyle;
		if (dlg.DoModal() == IDOK)
		{
			m_List.SetItemText(iSelect, 1, dlg.m_strName);
			m_List.SetItemText(iSelect, 2, dlg.m_strCode);
			m_List.SetItemText(iSelect, 6, dlg.m_strPhone);
			CString strCost;
			strCost.Format("%d", (*m_pvecYibaoStyle)[dlg.m_iSel].iYibaoCost);
			m_List.SetItemText(iSelect, 3, strCost);
			m_List.SetItemText(iSelect, 4, (*m_pvecYibaoStyle)[dlg.m_iSel].strYibaoStyle);
			if ((dlg.m_iSel == 2) || (dlg.m_iSel == 3) || (dlg.m_iSel == 4))
				m_List.SetItemText(iSelect, 5, dlg.m_strDibao);
			else
				m_List.SetItemText(iSelect, 5, "");
			m_List.SetItemData(iSelect, dlg.m_iSel);
			SumCost();
		}
	}

}


void CAddYibaoDlg::OnBnClickedOk()
{
	CYibaoCostHintDlg dlg("提交");
	
	int iSize = m_List.GetItemCount();
	if (iSize == 0)
	{
		AfxMessageBox("请选择至少一位居民!");
		return;
	}
	for (int i = 0; i < iSize; ++i)
	{
		CString strName, strCode, strCost, strStyle, strMsg;
		strName = m_List.GetItemText(i, 1);
		strCode = m_List.GetItemText(i, 2);
		strStyle = (*m_pvecYibaoStyle)[m_List.GetItemData(i)].strYibaoStyle;
		strCost = m_List.GetItemText(i, 3);
		strMsg.Format("姓名：%s,身份证：%s,类型：%s,费用：%s\r\n",strName,strCode,strStyle,strCost);
		dlg.m_strMemberList += strMsg;
	}
	dlg.m_strMemberList += "合计：";
	dlg.m_strMemberList += m_strCost;
	if (dlg.DoModal() == IDOK)
	{
		int iYibaodanju, iYibaoid;
		if (InsertYibaoCost(iYibaodanju, iYibaoid))
		{
			/*
			int iRow = m_pParentList->GetItemCount();
			int iSize = m_List.GetItemCount();
			for (int i = 0; i < iSize; ++i)
			{
				CString strValue;
				strValue.Format("%d", iRow+1);
				m_strName = m_List.GetItemText(i, 1);
				m_strCode = m_List.GetItemText(i, 2);
				m_strCost = m_List.GetItemText(i, 3);
				CString strStyle = m_List.GetItemText(i, 4);
				m_strDibao = m_List.GetItemText(i, 5);
				m_strPhone = m_List.GetItemText(i, 6);
				m_pParentList->InsertItem(iRow, strValue);
				strValue.Format("%d", iYibaoid);
				m_pParentList->SetItemText(iRow, 1, strValue);
				strValue.Format("%d", iYibaodanju);
				m_pParentList->SetItemText(iRow, 2, strValue);
				m_pParentList->SetItemText(iRow, 3, m_strName);
				m_pParentList->SetItemText(iRow, 4, m_strCode);
				m_pParentList->SetItemText(iRow, 5, m_strCost);
				m_pParentList->SetItemText(iRow, 6, strStyle);
				m_pParentList->SetItemText(iRow, 7, m_strDibao);
				m_pParentList->SetItemText(iRow, 8, m_strPhone);
				m_pParentList->SetItemData(iRow, m_List.GetItemData(i));
				++iRow;
				++iYibaoid;
			}
			*/
			m_pDlg->InitList();
			EmptyAllControl();
		}
	}
}

void CAddYibaoDlg::EmptyAllControl()
{
	m_List.DeleteAllItems();
	m_editCode.SetWindowText("");
	m_editName.SetWindowText("");
	m_editPhone.SetWindowText("");
	m_editDibao.SetWindowText("");
	m_cmbStyle.SetCurSel(0);
	m_staticSum.SetWindowText("0元");
}

void CAddYibaoDlg::GetYibaoMsg(int& iDanju, int& iYibaoid)
{
	iDanju = 1;
	iYibaoid = 1;
	CTime curTime;
	curTime = CTime::GetCurrentTime();
	mysql_init(&theApp.m_db);
	YibaoStyle yibaostyle;
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		MYSQL_RES *result;  
		MYSQL_ROW sql_row;  

		// MYSQL_FIELD *fd;
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSelect;
		CString strYibaotime;
		strYibaotime.Format("%d-01-01", curTime.GetYear());
		strSelect.Format("select max(yibaodanju),max(yibaoid) from yibao where yibaotime > '%s'", strYibaotime);
		// 查询
		int res = mysql_query(&theApp.m_db, strSelect);
		if (res == 0)
		{
			result = mysql_store_result(&theApp.m_db);
			// 获取具体的数据 
			while (sql_row = mysql_fetch_row(result)) 
			{
				CString strMax = sql_row[0];
				iDanju=atoi(strMax)+1;
				strMax = sql_row[1];
				iYibaoid=atoi(strMax)+1;
				break;
			}

			//释放结果资源
			if (result != NULL)
				mysql_free_result(result);
		}
	}

	mysql_close(&theApp.m_db);
}

BOOL CAddYibaoDlg::InsertYibaoCost(int& iYibaodanju, int& iYibaoid)
{
	BOOL bReturn = TRUE;
	GetYibaoMsg(iYibaodanju, iYibaoid);
	mysql_init(&theApp.m_db);
	if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
	{
		mysql_query(&theApp.m_db, "SET NAMES GBK");
		CString strSQL;
		strSQL = "lock tables yibao write";
		int res = mysql_query(&theApp.m_db, strSQL);
		if (res == 0)
		{
			int iSize = m_List.GetItemCount();
			for (int i = 0; i < iSize; ++i)
			{
				m_strName = m_List.GetItemText(i, 1);
				m_strCode = m_List.GetItemText(i, 2);
				m_strDibao = m_List.GetItemText(i, 5);
				m_strPhone = m_List.GetItemText(i, 6);
				m_iSel = m_List.GetItemData(i);
				if ((m_iSel == 2) || (m_iSel == 3) || (m_iSel == 4))
					strSQL.Format("insert into yibao(yibaodanju,membercode,membername,memberphone,yibaostyle,dibaocode,status,author) values(%d,'%s','%s','%s',%d,'%s',1,'%s')", 
					iYibaodanju,m_strCode,m_strName,m_strPhone,(*m_pvecYibaoStyle)[m_iSel].iYibaoStyleID,m_strDibao,theApp.m_strUser);
				else
					strSQL.Format("insert into yibao(yibaodanju,membercode,membername,memberphone,yibaostyle,status,author) values(%d,'%s','%s','%s',%d,1,'%s')", 
					iYibaodanju,m_strCode,m_strName,m_strPhone,(*m_pvecYibaoStyle)[m_iSel].iYibaoStyleID,theApp.m_strUser);
				res = mysql_query(&theApp.m_db, strSQL);
				if (res != 0)
				{
					AfxMessageBox("提交失败!");
					bReturn = FALSE;
					break;
				}
			}

			strSQL = "unlock tables";
			mysql_query(&theApp.m_db, strSQL);
		}

	}

	mysql_close(&theApp.m_db);
	return bReturn;
}

void CAddYibaoDlg::OnEnKillfocusEditCode()
{
	CheckYear();
}


void CAddYibaoDlg::CheckYear()
{
	CString strCode;
	m_editCode.GetWindowText(strCode);
	strCode.Trim();
	if (strCode.GetLength() == 18)
	{
		int iYear = atoi(strCode.Mid(6, 4));
		CTime tmYear = CTime::GetCurrentTime();
		if ((tmYear.GetYear()-iYear) >= 60)
			m_cmbStyle.SetCurSel(1);
		else
			m_cmbStyle.SetCurSel(0);
	}
}