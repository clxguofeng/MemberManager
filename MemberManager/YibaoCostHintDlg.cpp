// YibaoCostHintDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "YibaoCostHintDlg.h"
#include "afxdialogex.h"


// CYibaoCostHintDlg �Ի���

IMPLEMENT_DYNAMIC(CYibaoCostHintDlg, CDialogEx)

CYibaoCostHintDlg::CYibaoCostHintDlg(CString strBtnName, CWnd* pParent /*=NULL*/)
	: CDialogEx(CYibaoCostHintDlg::IDD, pParent)
{
	m_strBtnName = strBtnName;
}

CYibaoCostHintDlg::~CYibaoCostHintDlg()
{
}

void CYibaoCostHintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_staticHint);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CYibaoCostHintDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CYibaoCostHintDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CYibaoCostHintDlg ��Ϣ�������


void CYibaoCostHintDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL CYibaoCostHintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_staticHint.SetWindowText(m_strMemberList);
	m_btnOK.SetWindowText(m_strBtnName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
