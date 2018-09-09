#pragma once
#include "afxcmn.h"
#include "afxbutton.h"
#include "afxwin.h"
// #include "MFCDialog.h"

// CExcelDlg 对话框

class CExcelDlg : public CMFCDialog
{
	DECLARE_DYNAMIC(CExcelDlg)

public:
	CExcelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExcelDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXCEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonSource();
	afx_msg void OnBnClickedButtonDes();
	CProgressCtrl m_progress;
public:
	void ImportExcel(CString strSource, CString strDes);
	void PutHousePeopleInfo(vector<GroupInfo>& vecGroup, _WorksheetPtr workbuildsheet, _WorksheetPtr workhousesheet, _WorksheetPtr workpeoplesheet, _WorksheetPtr worksourcesheet);
	int GetBeginPutInfoPos(_WorksheetPtr worksheet);
	void GetPeopleinfo(_WorksheetPtr worksourcesheet, int iRow, PeopleInfo& peopleinfo);
	RangePtr GetMergerAreaRange(_WorksheetPtr worksheet, char cColumn, int iRow);
	void GetHouseInfo(_WorksheetPtr worksheet, RangePtr rangeName, HouseInfo& houseinfo, GroupInfo& GroupInfo, int iHouseNumber);
	void CheckHouseinfo(vector<GroupInfo>::iterator it);
	void PutPeopleInfo(_WorksheetPtr worksheet, vector<GroupInfo>::iterator itGroup, int& iPos);
	void PutHouseInfo(_WorksheetPtr worksheet, vector<GroupInfo>::iterator itGroup, int& iPos);
	virtual BOOL OnInitDialog();
	void SetBorderProperty(_WorksheetPtr worksheet, int iHeight, char cEndColumn, int iBeginPos, int iEndPos);
	void SetSourceState(_WorksheetPtr workhousesheet, vector<GroupInfo>& vecGroup);
	void OperHouseName(vector<GroupInfo>::iterator it);
	void CheckExcelFormat(CString strFileName);
	void GetSimpleHouseinfo(_WorksheetPtr worksheet, vector<SimpleHouseInfo>& vecHouseInfo);
	void UpdatePeopleInfo(_WorksheetPtr worksheet, vector<SimpleHouseInfo>& vecHouseInfo);
	void ImportPeopleinfo(SimplePeopleInfo& peopleinfo, _WorksheetPtr worksheet, int i);
	void GetPeopleDBInfo(CString strName, vector<DBPeopleInfo>& vecDBPeople);
	BOOL CheckPeopleFormat(_WorksheetPtr worksheet, SimplePeopleInfo& info, vector<DBPeopleInfo>& vecInfo, CString& strPhone);
	void CheckPeopleFormat2(_WorksheetPtr worksheet, vector<SimpleHouseInfo>& vecInfo);
	CString GetSinglePhone(CString strPhone);
	BOOL MatchDBPeopleInfo(_WorksheetPtr worksheet, vector<DBPeopleInfo>& vecInfo, SimplePeopleInfo& info, const CString& strValue, CString& strPhone);
	void UpdateOtherPeopleNumber(_WorksheetPtr worksheet, SimpleHouseInfo& houseinfo, int iIndex, const CString& strPhone);
	void CheckExcelFormat2(CString strFileName);
	void CheckPhoneFormat(_WorksheetPtr worksheet, SimplePeopleInfo& info);
	CString GetNumber(CString strValue, int iMin);
	void GetAllPeopleinfo(_WorksheetPtr worksourcesheet, vector<GroupInfo>& vecGroup);
	vector<GroupInfo>::iterator GetGroupInterator(vector<GroupInfo>& vecGroup, CString strValue);
	void PutGroupInfo(_WorksheetPtr worksheet, vector<GroupInfo>::iterator it);
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonCheckFormat();
	// afx_msg void OnPaint();
	CMFCButton m_btnImport;
	CMFCButton m_btnCheckFromDB;
	CMFCButton m_btnCheckFormat;
	CMFCButton m_btnBrowserSource;
	CMFCButton m_btnBrowserDes;
	// afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_staticSource;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
