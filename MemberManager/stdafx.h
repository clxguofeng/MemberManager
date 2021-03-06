// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include "mysql.h"
#include "Common.h"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include "Common.h"
#include "MFCDialog.h"
#include <afxcontrolbars.h>

#pragma comment(lib,"libmysql.lib")

#import "C:\\Program Files (x86)\\Common Files\\microsoft shared\\OFFICE12\\mso.dll" rename("RGB", "ignorethis")
#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.OLB" raw_interfaces_only, rename("Reference", "ignorethis"), rename("VBE", "testVBE")
#import "C:\\Program Files (x86)\\Microsoft Office\\OFFICE12\excel.exe" exclude("IFont", "IPicture") rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "testVBE"), rename("ReplaceText", "EReplaceText"), rename("CopyFile","ECopyFile"), rename("FindText", "EFindText"), rename("NoPrompt", "ENoPrompt")
#import "C:\\Program Files (x86)\\Microsoft Office\\Office12\\MSWORD.OLB" rename("ExitWindows","WordExitWindows"), rename("VBE", "testVBE"), rename("FindText", "WordFindText")

using namespace Excel;
using namespace std;

typedef struct PEOPLEINFO
{
	CString strName;
	CString strRole;
	CString strSex;
	CString strNumber;
	CString strPhone;
} PeopleInfo;

typedef struct HOUSEINFO
{
	CString strHouseID;
	CString strHouse;
	int iHouseNumber;
	int iUnit;
	int iFloor;
	vector<PeopleInfo> vecPeoples;
} HouseInfo;

typedef struct GroupInfo
{
	CString strGroupID;
	CString strSimpleName;
	CString strName;
	int iPos;
	int iUpFloor;
	int iDownFloor;
	int iUnit;
	int iUnitQuantity;
	CString strGrid;
	int iState;
	vector<HouseInfo> vecHouseInfo;
} GroupInfo;

typedef struct SIMPLEPEOPLEINFO
{
	CString strName;
	CString strNumber;
	CString strPhone;
	int iRow;
} SimplePeopleInfo;

typedef struct DBPEOPLEINFO
{
	CString strNumber;
	CString strPhone;
} DBPeopleInfo;

typedef struct SIMPLEHOUSEINFO
{
	CString strGroup;
	CString strHouseID;
	vector<SimplePeopleInfo> vecPeoples;
} SimpleHouseInfo;

typedef struct YIBAOSTYLE
{
	int iYibaoStyleID;
	CString strYibaoStyle;
	int iYibaoCost;
} YibaoStyle;

struct HouseNumberLess : public binary_function<HouseInfo&, HouseInfo&, bool>
{
	bool operator()(const HouseInfo& lhs, const HouseInfo& rhs)
	{
		CString strlhs = lhs.strHouse;
		strlhs.Replace("室", "");
		strlhs.Replace("号", "");
		CString strrhs = rhs.strHouse;
		strrhs.Replace("室", "");
		strrhs.Replace("号", "");
		return atoi(strlhs) < atoi(strrhs);
	}
};

void PutRangeString(_WorksheetPtr worksheet, CString strValue, char cColumn, int iRow);
CString GetRangeString(_WorksheetPtr worksheet, char cColumn, int iRow);
void GetGroupInfo(_WorksheetPtr worksheet, vector<GroupInfo>& vecGroup, BOOL bState);
void GetSplitString(CString strValue, CString strKey, vector<CString>& vecSplit);
BOOL ExecuteDBSQL(CString strSQL);
BOOL CheckExistRecord(CString strSQL);
CString GetSex(CString strCode);
BOOL CheckCurYearExistYibao(CString strSelect);

typedef struct sqlexportstruct
{
	CString strFilename;
	CString strSQL;
	CString strField;
	CString strTitle;
	CString strSheetname;
	CString strWidth;
} SQLEXPORTSTRUCT;

#define USERRIGHT_LIST_WIDTH	250

#define EXPORT_YIBAO_MINGXI_WIDTH					"4,4,8,20,13,15,12,8"
#define	EXPORT_YIBAO_MINGXI_FIELDNAME				"序号,单号,姓名,身份证,联系方式,低保号,类别,金额"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


