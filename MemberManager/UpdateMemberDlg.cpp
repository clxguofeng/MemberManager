// UpdateMemberDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemberManager.h"
#include "UpdateMemberDlg.h"
#include "afxdialogex.h"
#include "MemberInfoDlg.h"

// CUpdateMemberDlg �Ի���

IMPLEMENT_DYNAMIC(CUpdateMemberDlg, CMFCDialog)

CUpdateMemberDlg::CUpdateMemberDlg(CWnd* pParent /*=NULL*/, int iMod)
: CMFCDialog(IDD, pParent)
	// : CDialogEx(CUpdateMemberDlg::IDD, pParent)
{
	m_iMod = iMod;
}

CUpdateMemberDlg::~CUpdateMemberDlg()
{
}

void CUpdateMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CMFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnSave);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CUpdateMemberDlg, CMFCDialog)
	ON_BN_CLICKED(IDOK, &CUpdateMemberDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUpdateMemberDlg ��Ϣ�������


BOOL CUpdateMemberDlg::OnInitDialog()
{
	CMFCDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT_NAME, m_strName);
	SetDlgItemText(IDC_EDIT_CODE, m_strCode);
	SetDlgItemText(IDC_EDIT_PHONE, m_strPhone);
	SetDlgItemText(IDC_EDIT_COMMENT, m_strComment);
	SetDlgItemText(IDC_EDIT_STYLE, m_strStyle);
	if (m_iMod == 0)
		SetWindowText("�޸�");
	else
		SetWindowText("����");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUpdateMemberDlg::OnBnClickedOk()
{
	CString strSQL;
	GetDlgItemText(IDC_EDIT_NAME, m_strName);
	GetDlgItemText(IDC_EDIT_CODE, m_strCode);
	GetDlgItemText(IDC_EDIT_PHONE, m_strPhone);
	GetDlgItemText(IDC_EDIT_COMMENT, m_strComment);
	GetDlgItemText(IDC_EDIT_STYLE, m_strStyle);

	m_strName.TrimLeft();
	m_strName.TrimRight();
	m_strCode.TrimLeft();
	m_strCode.TrimRight();
	m_strCode.TrimLeft();
	m_strPhone.TrimRight();
	m_strComment.TrimRight();
	m_strComment.TrimLeft();
	m_strStyle.TrimRight();
	m_strStyle.TrimLeft();
	if (m_strName.IsEmpty() || m_strCode.IsEmpty() || m_strCode.IsEmpty())
	{
		AfxMessageBox("���ݲ���Ϊ�գ�");
		return;
	}

	if (m_iMod == 0)
	{
		mysql_init(&theApp.m_db);

		if (mysql_real_connect(&theApp.m_db, theApp.m_strIP, "clxguofeng", "gcMAnERQ790327", "membermanager", 3306, NULL, 0))
		{
			mysql_query(&theApp.m_db, "SET NAMES GBK");

			strSQL.Format("update memberinfo set membername='%s',memberstyle='%s',membercode='%s',phone='%s',comment='%s' where memberid=%s", 
				m_strName, m_strStyle, m_strCode, m_strPhone, m_strComment, m_strID);

			int res = mysql_query(&theApp.m_db, strSQL);
			if (res == 0)
			{
				mysql_close(&theApp.m_db);
				CUpdateMemberDlg::OnOK();
				return;
			}
			else
			{
				const char *pError = mysql_error(&theApp.m_db);
				AfxMessageBox(pError);
			}
		}
	}
	else
	{
		CString strOldPhone;
		if (CMemberInfoDlg::CheckMemberExist(m_strCode, strOldPhone) == FALSE)
		{
			if (CMemberInfoDlg::InsertMember(m_strName, m_strCode, m_strPhone, m_strComment, m_strStyle))
			{
				CUpdateMemberDlg::OnOK();
				return;
			}
			else
			{
				const char *pError = mysql_error(&theApp.m_db);
				AfxMessageBox(pError);
			}
		}
		else
		{
			mysql_close(&theApp.m_db);
			AfxMessageBox("�Ѿ�������ͬ���֤���룡");
			return;
		}
	}
	mysql_close(&theApp.m_db);
	return;
}
