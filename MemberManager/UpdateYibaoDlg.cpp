// UpdateYibaoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateYibaoDlg.h"
#include "afxdialogex.h"


// CUpdateYibaoDlg �Ի���

IMPLEMENT_DYNAMIC(CUpdateYibaoDlg, CDialogEx)

CUpdateYibaoDlg::CUpdateYibaoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateYibaoDlg::IDD, pParent)
{

}

CUpdateYibaoDlg::~CUpdateYibaoDlg()
{
}

void CUpdateYibaoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_CODE, m_editCode);
	DDX_Control(pDX, IDC_EDIT_PHONE, m_editPhone);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_cmbStyle);
	DDX_Control(pDX, IDC_EDIT_DIBAO, m_editDibao);
}


BEGIN_MESSAGE_MAP(CUpdateYibaoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateYibaoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdateYibaoDlg ��Ϣ�������


void CUpdateYibaoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iSel = m_cmbStyle.GetCurSel();
	m_editName.GetWindowText(m_strName);
	m_editCode.GetWindowText(m_strCode);
	m_editPhone.GetWindowText(m_strPhone);
	m_editDibao.GetWindowText(m_strDibao);
	m_strName.Trim();
	m_strCode.Trim();
	m_strPhone.Trim();
	m_strDibao.Trim();

	if ((m_iSel == 2) || (m_iSel == 3) || (m_iSel == 4))
	{
		if (m_strDibao.IsEmpty())
		{
			AfxMessageBox("�ͱ��Ų���Ϊ��!");
			m_editDibao.SetFocus();
			return;
		}
	}

	if (m_strName.IsEmpty() || m_strCode.IsEmpty())
	{
		AfxMessageBox("���ݲ���Ϊ��!");
		return;
	}
	
	if (AfxMessageBox("��ȷ���޸���?", MB_OKCANCEL) == IDOK)
		CDialogEx::OnOK();
}


BOOL CUpdateYibaoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_editName.SetWindowText(m_strName);
	m_editCode.SetWindowText(m_strCode);
	m_editPhone.SetWindowText(m_strPhone);
	m_editDibao.SetWindowText(m_strDibao);
	int iSize = m_pvecYibaoStyle->size();
	for (int i = 0; i < iSize; ++i)
		m_cmbStyle.InsertString(i, (*m_pvecYibaoStyle)[i].strYibaoStyle);

	m_cmbStyle.SetCurSel(m_iSel);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
