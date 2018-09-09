// UpdateYibaoBiaozhunDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateYibaoBiaozhunDlg.h"
#include "afxdialogex.h"


// CUpdateYibaoBiaozhunDlg �Ի���

IMPLEMENT_DYNAMIC(CUpdateYibaoBiaozhunDlg, CDialogEx)

CUpdateYibaoBiaozhunDlg::CUpdateYibaoBiaozhunDlg(int iFlag, CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateYibaoBiaozhunDlg::IDD, pParent)
{
	m_iFlag = iFlag;
}

CUpdateYibaoBiaozhunDlg::~CUpdateYibaoBiaozhunDlg()
{
}

void CUpdateYibaoBiaozhunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_YEAR, m_combYear);
	DDX_Control(pDX, IDC_COMBO_STYLE2, m_combStyle);
	DDX_Control(pDX, IDC_EDIT_DIBAO, m_editMoney);
}


BEGIN_MESSAGE_MAP(CUpdateYibaoBiaozhunDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateYibaoBiaozhunDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdateYibaoBiaozhunDlg ��Ϣ�������


BOOL CUpdateYibaoBiaozhunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int iYear = 2010;
	CTime curTime = CTime::GetCurrentTime();
	for (int i = 0; i < 100; ++i)
	{
		CString strYear;
		strYear.Format("%d��", iYear+i);
		m_combYear.AddString(strYear);
	}

	int iCursel = curTime.GetYear() - iYear;
	m_combYear.SetCurSel(iCursel);
	m_combStyle.InsertString(0, "��ͨ");
	m_combStyle.InsertString(1, "60������");
	m_combStyle.InsertString(2, "A��ͱ�");
	m_combStyle.InsertString(3, "B��ͱ�");
	m_combStyle.InsertString(4, "C��ͱ�");
	m_combStyle.InsertString(5, "C�м�");
	m_combStyle.InsertString(6, "�ѹ�������ż");
	m_combStyle.InsertString(7, "�������");
	m_combStyle.SetCurSel(0);

	if (m_iFlag == 1)
	{
		SetWindowText("�������ѱ�׼");
	}
	else
	{
		m_combStyle.EnableWindow(0);
		m_combYear.EnableWindow(0);
		m_combYear.SetCurSel(m_iYear-2010);
		m_combStyle.SetCurSel(m_iStyle-1);
		m_editMoney.SetWindowText(m_strMoney);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUpdateYibaoBiaozhunDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	m_editMoney.GetWindowText(m_strMoney);
	m_iYear = m_combYear.GetCurSel() + 2010;
	m_iStyle = m_combStyle.GetCurSel()+1;
	m_combStyle.GetWindowText(m_strStyle);
}
