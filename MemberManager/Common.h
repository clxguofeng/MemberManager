// Common.h: interface for the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMON_H__4D85B307_D3C0_4AA0_AA1C_1715637F4EA2__INCLUDED_)
#define AFX_COMMON_H__4D85B307_D3C0_4AA0_AA1C_1715637F4EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wincrypt.h>
#include <string>
#include <vector>
using namespace std;

#define WM_USER_SHOWTASK					WM_USER+1000
#define WM_USER_CLOSE						WM_USER+1001

#define MY_ENCODING_TYPE					(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define KEYLENGTH							0x00800000
#define ENCRYPT_ALGORITHM CALG_RC4 
#define ENCRYPT_BLOCK_SIZE 8 
#define ENCRYPT_STRING_DEFAULT_KEY			"chulixinse+10240"
#define ENCRYPT_STRING_USERPWD_KEY		    "cfulikina7+10240"

#define	BUFFERSIZE							2048

#define CONFIGFILENAME						"\\config.ini"

#pragma comment(lib, "wininet.lib")

typedef struct _SERVERINFO
{
	CString strServer;
	CString strUser;
	CString strPassword;
	CString strState;
	MYSQL   *pSQL;
	_SERVERINFO()
	{
		pSQL = NULL;
	}
} SERVERINFO, FAR* LPSERVERINFO;

int		CheckStartNum(const CString& strLine);
BOOL	CheckUserAndPwd(const CString& strUser, const CString& strPwd);

void GetServerInfo(const CString& strFile, const CString& strKey, SERVERINFO& ServerInfo);
void WriteServerInfo(const CString& strFile, const CString& strKey, SERVERINFO& ServerInfo);
void EmptyServerInfo(const CString& strFile, const CString& strKey);

BOOL CheckConnectState();

BOOL ConnectDB(LPSERVERINFO ServerInfo);
BOOL ExecuteSQL(LPSERVERINFO lpServerInfo, const CString& strSQL);

// 加解密文件
BOOL EncryptFile(PCHAR szSource, PCHAR szDestination, CString strKey = ENCRYPT_STRING_DEFAULT_KEY);
BOOL DecryptFile(PCHAR szSource, PCHAR szDestination, CString strKey = ENCRYPT_STRING_DEFAULT_KEY); 
// 加解密字符串
BOOL EncryptString(CString strSource, CString& strDes, CString strKey = ENCRYPT_STRING_DEFAULT_KEY);
BOOL DecryptString(const CString& strSource, CString& strDes, CString strKey = ENCRYPT_STRING_DEFAULT_KEY);

CString UrlUTF8(char * str);
CString UTF8ToGB2312(LPCSTR lpszInBuf);
void  GB2312ToUTF_8(CString& pOut,char *pText, int pLen);
int Base64Decode(char * buf, const char * base64code, int src_len = 0);
int Base64Encode(char * base64code, const char * src, int src_len = 0);

int GetB64Index(char ch);
char GetB64Char(int index);

void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer);
void UnicodeToUTF_8(char* pOut,WCHAR* pText);
LPWSTR UTF8ToUnicode(LPCSTR lpszInBuf);
LPSTR UnicodeToGB2312(LPCWSTR lpszInBuf);

string ASCII2UTF_8(string& strAsciiCode);
string UTF_82ASCII(string& strUtf8Code);

#endif // !defined(AFX_COMMON_H__4D85B307_D3C0_4AA0_AA1C_1715637F4EA2__INCLUDED_)
