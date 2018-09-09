// Common.cpp: implementation of the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Common.h"
#include <wininet.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//base64
// 从双字中取单字节
#define B0(a) (a & 0xFF)
#define B1(a) (a >> 8 & 0xFF)
#define B2(a) (a >> 16 & 0xFF)
#define B3(a) (a >> 24 & 0xFF)

int Base64Decode(char * buf, const char * base64code, int src_len) 
{   
	if (src_len == 0)
		src_len = strlen(base64code);
	
	int len = 0;
	unsigned char* psrc = (unsigned char*)base64code;
	char * pbuf = buf;
	int i = 0;
	for (i = 0; i < src_len - 4; i += 4)
	{
		unsigned long ulTmp = *(unsigned long*)psrc;
		
		register int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
		register int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
		register int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
		
		*((unsigned long*)pbuf) = b0 | b1 << 8 | b2 << 16;
		psrc  += 4; 
		pbuf += 3;
		len += 3;
	}
	
	// 处理最后余下的不足4字节的饿数据
	if (i < src_len)
	{
		int rest = src_len - i;
		unsigned long ulTmp = 0;
		for (int j = 0; j < rest; ++j)
		{
			*(((unsigned char*)&ulTmp) + j) = *psrc++;
		}
		
		register int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
		*pbuf++ = b0;
		len  ++;
		
		if ('=' != B1(ulTmp) && '=' != B2(ulTmp))
		{
			register int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
			*pbuf++ = b1;
			len  ++;
		}
		
		if ('=' != B2(ulTmp) && '=' != B3(ulTmp))
		{
			register int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
			*pbuf++ = b2;
			len  ++;
		}
		
	}
	
	*pbuf = '\0'; 
	
	return len;
} 

int Base64Encode(char * base64code, const char * src, int src_len) 
{   
	if (src_len == 0)
		src_len = strlen(src);
	
	int len = 0;
	unsigned char* psrc = (unsigned char*)src;
	char * p64 = base64code;
	int i = 0;
	for (i = 0; i < src_len - 3; i += 3)
	{
		unsigned long ulTmp = *(unsigned long*)psrc;
		register int b0 = GetB64Char((B0(ulTmp) >> 2) & 0x3F); 
		register int b1 = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F); 
		register int b2 = GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F); 
		register int b3 = GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F); 
		*((unsigned long*)p64) = b0 | b1 << 8 | b2 << 16 | b3 << 24;
		
		len += 4;
		p64  += 4; 
		psrc += 3;
	}
	
	// 处理最后余下的不足3字节的饿数据
	if (i < src_len)
	{
		int rest = src_len - i;
		unsigned long ulTmp = 0;
		for (int j = 0; j < rest; ++j)
		{
			*(((unsigned char*)&ulTmp) + j) = *psrc++;
		}
		
		p64[0] = GetB64Char((B0(ulTmp) >> 2) & 0x3F); 
		p64[1] = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F); 
		p64[2] = rest > 1 ? GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F) : '='; 
		p64[3] = rest > 2 ? GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F) : '='; 
		p64 += 4; 
		len += 4;
	}
	
	*p64 = '\0'; 
	return len;
}

char GetB64Char(int index)
{
	const char szBase64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	if (index >= 0 && index < 64)
		return szBase64Table[index];

	return '=';
}

int GetB64Index(char ch)
{
	int index = -1;
	if (ch >= 'A' && ch <= 'Z')
	{
		index = ch - 'A';
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		index = ch - 'a' + 26;
	}
	else if (ch >= '0' && ch <= '9')
	{
		index = ch - '0' + 52;
	}
	else if (ch == '+')
	{
		index = 62;
	}
	else if (ch == '/')
	{
		index = 63;
	}
	
	return index;
}

BOOL EncryptString(CString strSource, CString& strDes, CString strKey)
{
	//   Declare and initialize local variables.	
	PBYTE pbBuffer = NULL;
	char  *pString = NULL;
	char *pBase64 = NULL;

	HCRYPTKEY hKey = 0;
	HCRYPTHASH hHash = 0;
	HCRYPTPROV hCryptProv = 0; 

	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount;
	BOOL bFlag = TRUE;
	DWORD dwBegin = 0;
	DWORD dwLen;
	DWORD dwBlockCount;
	DWORD dwIndex;
	DWORD dwDesLen = 0;
	DWORD dwBaseLen;
	
	//--------------------------------------------------------------------
	if (strSource.GetLength() == 0)
	{
		bFlag = FALSE;
		goto end;
	}

	//以下获得一个CSP句柄
	if(CryptAcquireContext(
		&hCryptProv, 
		NULL,				//NULL表示使用默认密钥容器，默认密钥容器名为用户登陆名
		NULL, 
		PROV_RSA_FULL, 
		0))
	{
	}
	else//密钥容器不存在
	{
		if(CryptAcquireContext(
			&hCryptProv, 
			NULL, 
			NULL, 
			PROV_RSA_FULL, 
			CRYPT_NEWKEYSET))//创建密钥容器
		{
			//创建密钥容器成功，并得到CSP句柄
		}
		else
		{
			bFlag = FALSE;
			goto end;
		}
		
	}

	//--------------------------------------------------------------------
	// 创建一个会话密钥（session key）
	// 会话密钥也叫对称密钥，用于对称加密算法。
	// （注: 一个Session是指从调用函数CryptAcquireContext到调用函数
	//   CryptReleaseContext 期间的阶段。）

	//--------------------------------------------------------------------
	// Create a hash object. 
	if(CryptCreateHash(
		hCryptProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash))
    {
    }
    else
    {
		bFlag = FALSE;
		goto end;
    }  

	//--------------------------------------------------------------------
	// 用输入的密码产生一个散列
	if(CryptHashData(
		hHash, 
		(BYTE *)strKey.GetBuffer(0), 
		strKey.GetLength(), 
		0))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	//--------------------------------------------------------------------
	// 通过散列生成会话密钥(session key)
	if(CryptDeriveKey(
		hCryptProv, 
		ENCRYPT_ALGORITHM, 
		hHash, 
		KEYLENGTH, 
		&hKey))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Destroy the hash object. 
	
	CryptDestroyHash(hHash); 
	hHash = NULL; 
	
	//--------------------------------------------------------------------
	//  The session key is now ready. 	
	//--------------------------------------------------------------------
	// 因为加密算法是按ENCRYPT_BLOCK_SIZE 大小的块加密的，所以被加密的
	// 数据长度必须是ENCRYPT_BLOCK_SIZE 的整数倍。下面计算一次加密的
	// 数据长度。
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 
	
	//--------------------------------------------------------------------
	// Determine the block size. If a block cipher is used, 
	// it must have room for an extra block. 	
	if(ENCRYPT_BLOCK_SIZE > 1) 
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
	else 
		dwBufferLen = dwBlockLen; 
	
	//--------------------------------------------------------------------
	// Allocate memory. 
	if(pbBuffer = (BYTE *)malloc(dwBufferLen))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	//--------------------------------------------------------------------
	// In a do loop, encrypt the source file and write to the source file. 
	dwLen = strSource.GetLength();
	dwBlockCount = dwLen / dwBlockLen;
	if (dwLen % dwBlockLen)
		++dwBlockCount;

	if(pString = (char *)malloc(dwBufferLen*dwBlockCount))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}
	dwIndex = 1;
	do 
	{	
		//--------------------------------------------------------------------
		// Read up to dwBlockLen bytes from the source file. 
		BOOL bEnd = FALSE;
		if (dwIndex == dwBlockCount)
		{	
			bEnd = TRUE;
			dwCount = dwLen - (dwIndex-1) * dwBlockLen;
		}
		else
		{
			dwCount = dwBlockLen;
		}
		
		memcpy(pbBuffer, strSource.GetBuffer(0)+dwBegin, dwCount);

		//--------------------------------------------------------------------
		// 加密数据
		DWORD dwTemp = dwCount;

		if(!CryptEncrypt(
			hKey,			//密钥
			0,				//如果数据同时进行散列和加密，这里传入一个散列对象
			bEnd,			//如果是最后一个被加密的块，输入TRUE.如果不是输入FALSE.
							//这里通过判断是否到文件尾来决定是否为最后一块。
			0,				//保留
			pbBuffer,		//输入被加密数据，输出加密后的数据
			&dwTemp,		//输入被加密数据实际长度，输出加密后数据长度
			dwBufferLen))	//pbBuffer的大小。
		{ 
			bFlag = FALSE;
			goto end;
		} 	
		//--------------------------------------------------------------------
		memcpy(pString+dwDesLen, pbBuffer, dwTemp);
		// 目标字符串的大小
		dwDesLen += dwTemp;
		// 源字符串的大小
		dwBegin += dwCount;

		++dwIndex;
	} 
	while(dwIndex <= dwBlockCount); 

	dwBaseLen = dwDesLen*2+255;
	if (pBase64 = (char*)malloc(dwBaseLen))
	{	}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	Base64Encode(pBase64, pString, dwDesLen);
	strDes = pBase64;
	//--------------------------------------------------------------------
	//  End the do loop when the last block of the source file has been
	//  read, encrypted, and written to the destination file.
	
	//--------------------------------------------------------------------
	// Close files.
end:	
	//--------------------------------------------------------------------
	// Free memory. 
	if(pbBuffer) 
		free(pbBuffer); 
	
	if(pString)
		free(pString);

	if(pBase64)
		free(pBase64);
	//--------------------------------------------------------------------
	// Destroy session key. 
	
	if(hKey) 
		CryptDestroyKey(hKey); 
	
	//--------------------------------------------------------------------
	// Destroy hash object. 
	
	if(hHash) 
		CryptDestroyHash(hHash); 
	
	//--------------------------------------------------------------------
	// Release provider handle. 
	
	if(hCryptProv) 
		CryptReleaseContext(hCryptProv, 0);

	return(bFlag);
}

BOOL DecryptString(const CString& strSource, CString& strDes, CString strKey)
{
	//--------------------------------------------------------------------
	//   Declare and initialize local variables.
	PBYTE pbBuffer=NULL;
	char  *pString = NULL;
	char *pBase64 = NULL;

	HCRYPTPROV hCryptProv=0; 
	HCRYPTKEY hKey=0; 
	HCRYPTHASH hHash=0; 

	BOOL bFlag = TRUE;
	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount;
	DWORD dwIndex;
	DWORD dwLen;
	DWORD dwBlockCount;
	DWORD dwBegin = 0;
	DWORD dwDesLen = 0;
	DWORD dwBaseLen;

	if (strSource.GetLength() == 0)
	{
		bFlag = FALSE;
		goto end;
	}

	//--------------------------------------------------------------------
	// Get a handle to the default provider. 
	if(!CryptAcquireContext(
		&hCryptProv, 
		NULL, 
		NULL, 
		PROV_RSA_FULL, 
		0))
	{
		bFlag = FALSE;
		goto end;
	}
	
	//--------------------------------------------------------------------
	// Decrypt the file with a session key derived from a password. 
	
	//--------------------------------------------------------------------
	// Create a hash object. 
	if(!CryptCreateHash(
		hCryptProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash))
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Hash in the password data. 
	
	if(!CryptHashData(
		hHash, 
		(BYTE *)strKey.GetBuffer(0), 
		strKey.GetLength(), 
		0)) 
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Derive a session key from the hash object. 
	
	if(!CryptDeriveKey(
		hCryptProv, 
		ENCRYPT_ALGORITHM, 
		hHash, 
		KEYLENGTH, 
		&hKey))
	{ 
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Destroy the hash object. 
	
	CryptDestroyHash(hHash); 
	hHash = 0; 
	
	//--------------------------------------------------------------------
	//   The decryption key is now available, either having been imported
	//   from a BLOB read in from the source file or having been created 
	//   using the password. This point in the program is not reached if 
	//   the decryption key is not available.
	
	//--------------------------------------------------------------------
	// Determine the number of bytes to decrypt at a time. 
	// This must be a multiple of ENCRYPT_BLOCK_SIZE. 
	
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 
	dwBufferLen = dwBlockLen; 
	
	//--------------------------------------------------------------------
	// Allocate memory. 
	
	if(!(pbBuffer = (BYTE *)malloc(dwBufferLen)))
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	dwLen = strSource.GetLength();
	dwBaseLen = dwLen*2+255;
	if (pBase64 = (char*)malloc(dwBaseLen))
	{}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	// dwLen = Base64Decode(pBase64, strSource, dwLen);
	dwLen = Base64Decode(pBase64, strSource, dwLen);
	if (dwLen > 0)
	{	}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	dwBlockCount = dwLen / dwBlockLen;
	if (dwLen % dwBlockLen)
		++dwBlockCount;
	
	if(pString = (char *)malloc(dwBufferLen*dwBlockCount+1))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}
	dwIndex = 1;

	do { 
		//--------------------------------------------------------------------
		// Read up to dwBlockLen bytes from source file. 
		BOOL bEnd = FALSE;
		if (dwIndex == dwBlockCount)
		{	
			bEnd = TRUE;
			dwCount = dwLen - (dwIndex-1) * dwBlockLen;
		}
		else
		{
			dwCount = dwBlockLen;
		}

		memcpy(pbBuffer, pBase64+dwBegin, dwCount);
		//--------------------------------------------------------------------
		// Decrypt data. 
		DWORD dwTemp = dwCount;

		if(!CryptDecrypt(
			hKey, 
			0, 
			bEnd, 
			0, 
			pbBuffer, 
			&dwTemp))
		{
			bFlag = FALSE;
			goto end;
		}
		//--------------------------------------------------------------------
		//--------------------------------------------------------------------
		memcpy(pString+dwDesLen, pbBuffer, dwTemp);
		// 目标字符串的大小
		dwDesLen += dwTemp;
		// 源字符串的大小
		dwBegin += dwCount;
		
		++dwIndex;
	} while(dwIndex <= dwBlockCount);

	*(pString+dwDesLen) = 0;
	strDes = pString;
end:
	//--------------------------------------------------------------------
	// Free memory.
	if(pbBuffer) 
		free(pbBuffer); 
	
	if(pString)
		free(pString);
	
	if(pBase64)
		free(pBase64);
	//--------------------------------------------------------------------
	// Destroy session key. 
	
	if(hKey) 
		CryptDestroyKey(hKey); 
	
	//--------------------------------------------------------------------
	// Destroy hash object. 
	if(hHash) 
		CryptDestroyHash(hHash); 
	
	//--------------------------------------------------------------------
	// Release provider handle. 
	
	if(hCryptProv) 
		CryptReleaseContext(hCryptProv, 0); 
	
	return bFlag;
}

BOOL EncryptFile(PCHAR szSource, PCHAR szDestination, CString strKey)
{
	//   Declare and initialize local variables.	
	FILE *hSource = NULL; 
	FILE *hDestination = NULL; 
	PBYTE pbBuffer = 0;
	HCRYPTKEY hKey = 0;
	HCRYPTHASH hHash = 0;
	HCRYPTPROV hCryptProv = 0; 

	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount;
	BOOL bFlag = TRUE;
	//--------------------------------------------------------------------
	// Open source file. 
	if(fopen_s(&hSource,szSource,"rb") == 0)
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	} 

	//--------------------------------------------------------------------
	// Open destination file. 
	if(fopen_s(&hDestination, szDestination,"wb") == 0)
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	//以下获得一个CSP句柄
	if(CryptAcquireContext(
		&hCryptProv, 
		NULL,				//NULL表示使用默认密钥容器，默认密钥容器名为用户登陆名
		NULL, 
		PROV_RSA_FULL, 
		0))
	{
		// printf("A cryptographic provider has been acquired. \n");
	}
	else//密钥容器不存在
	{
		if(CryptAcquireContext(
			&hCryptProv, 
			NULL, 
			NULL, 
			PROV_RSA_FULL, 
			CRYPT_NEWKEYSET))//创建密钥容器
		{
			//创建密钥容器成功，并得到CSP句柄
			// printf("A new key container has been created.\n");
		}
		else
		{
			bFlag = FALSE;
			goto end;
		}
		
	}

	//--------------------------------------------------------------------
	// 创建一个会话密钥（session key）
	// 会话密钥也叫对称密钥，用于对称加密算法。
	// （注: 一个Session是指从调用函数CryptAcquireContext到调用函数
	//   CryptReleaseContext 期间的阶段。）

	//--------------------------------------------------------------------
	// Create a hash object. 
	if(CryptCreateHash(
		hCryptProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash))
    {
    }
    else
    {
		bFlag = FALSE;
		goto end;
    }  

	//--------------------------------------------------------------------
	// 用输入的密码产生一个散列
	if(CryptHashData(
		hHash, 
		(BYTE *)strKey.GetBuffer(0), 
		strKey.GetLength(), 
		0))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}

	//--------------------------------------------------------------------
	// 通过散列生成会话密钥(session key)
	if(CryptDeriveKey(
		hCryptProv, 
		ENCRYPT_ALGORITHM, 
		hHash, 
		KEYLENGTH, 
		&hKey))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Destroy the hash object. 
	
	CryptDestroyHash(hHash); 
	hHash = NULL; 
	
	//--------------------------------------------------------------------
	//  The session key is now ready. 
	
	//--------------------------------------------------------------------
	// 因为加密算法是按ENCRYPT_BLOCK_SIZE 大小的块加密的，所以被加密的
	// 数据长度必须是ENCRYPT_BLOCK_SIZE 的整数倍。下面计算一次加密的
	// 数据长度。
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 
	
	//--------------------------------------------------------------------
	// Determine the block size. If a block cipher is used, 
	// it must have room for an extra block. 	
	if(ENCRYPT_BLOCK_SIZE > 1) 
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
	else 
		dwBufferLen = dwBlockLen;
	
	//--------------------------------------------------------------------
	// Allocate memory. 
	if(pbBuffer = (BYTE *)malloc(dwBufferLen))
	{
	}
	else
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// In a do loop, encrypt the source file and write to the source file. 
	do 
	{
		//--------------------------------------------------------------------
		// Read up to dwBlockLen bytes from the source file. 
		dwCount = fread(pbBuffer, 1, dwBlockLen, hSource); 
		if(ferror(hSource))
		{
			bFlag = FALSE;
			goto end;
		}
		
		//--------------------------------------------------------------------
		// 加密数据
		if(!CryptEncrypt(
			hKey,			//密钥
			0,				//如果数据同时进行散列和加密，这里传入一个散列对象
			feof(hSource),	//如果是最后一个被加密的块，输入TRUE.如果不是输入FALSE.
							//这里通过判断是否到文件尾来决定是否为最后一块。
			0,				//保留
			pbBuffer,		//输入被加密数据，输出加密后的数据
			&dwCount,		//输入被加密数据实际长度，输出加密后数据长度
			dwBufferLen))	//pbBuffer的大小。
		{ 
			bFlag = FALSE;
			goto end;
		} 
		
		//--------------------------------------------------------------------
		// Write data to the destination file. 
		
		fwrite(pbBuffer, 1, dwCount, hDestination); 
		if(ferror(hDestination))
		{ 
			bFlag = FALSE;
			goto end;
		}
		
	} 
	while(!feof(hSource)); 
	//--------------------------------------------------------------------
	//  End the do loop when the last block of the source file has been
	//  read, encrypted, and written to the destination file.
	
	//--------------------------------------------------------------------
	// Close files.
end:	
	if(hSource) 
		fclose(hSource); 
	if(hDestination) 
		fclose(hDestination); 	
	//--------------------------------------------------------------------
	// Free memory. 
	
	if(pbBuffer) 
		free(pbBuffer); 
	
	//--------------------------------------------------------------------
	// Destroy session key. 
	
	if(hKey) 
		CryptDestroyKey(hKey); 
	
	//--------------------------------------------------------------------
	// Destroy hash object. 
	
	if(hHash) 
		CryptDestroyHash(hHash); 
	
	//--------------------------------------------------------------------
	// Release provider handle. 
	
	if(hCryptProv) 
		CryptReleaseContext(hCryptProv, 0);

	return(bFlag);
}

BOOL DecryptFile(PCHAR szSource, PCHAR szDestination, CString strKey)
{
	//--------------------------------------------------------------------
	//   Declare and initialize local variables.
	BOOL bFlag = TRUE;
	FILE *hSource=0; 
	FILE *hDestination=0; 
	
	HCRYPTPROV hCryptProv=0; 
	HCRYPTKEY hKey=0; 
	HCRYPTHASH hHash=0; 
	
	PBYTE pbBuffer=0; 
	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount; 	
	//--------------------------------------------------------------------
	// Open source file. 
	if (fopen_s(&hSource,szSource,"rb") != 0) 
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Open destination file. 
	
	if (fopen_s(&hDestination,szDestination,"wb") != 0)
	{
		bFlag = FALSE;
		goto end;
	} 
	//--------------------------------------------------------------------
	// Get a handle to the default provider. 
	if(!CryptAcquireContext(
		&hCryptProv, 
		NULL, 
		NULL, 
		PROV_RSA_FULL, 
		0))
	{
		bFlag = FALSE;
		goto end;
	}
	
	//--------------------------------------------------------------------
	// Decrypt the file with a session key derived from a password. 
	
	//--------------------------------------------------------------------
	// Create a hash object. 
	if(!CryptCreateHash(
		hCryptProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash))
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Hash in the password data. 
	
	if(!CryptHashData(
		hHash, 
		(BYTE *)strKey.GetBuffer(0), 
		strKey.GetLength(), 
		0)) 
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Derive a session key from the hash object. 
	
	if(!CryptDeriveKey(
		hCryptProv, 
		ENCRYPT_ALGORITHM, 
		hHash, 
		KEYLENGTH, 
		&hKey))
	{ 
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Destroy the hash object. 
	
	CryptDestroyHash(hHash); 
	hHash = 0; 
	
	//--------------------------------------------------------------------
	//   The decryption key is now available, either having been imported
	//   from a BLOB read in from the source file or having been created 
	//   using the password. This point in the program is not reached if 
	//   the decryption key is not available.
	
	//--------------------------------------------------------------------
	// Determine the number of bytes to decrypt at a time. 
	// This must be a multiple of ENCRYPT_BLOCK_SIZE. 
	
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 
	dwBufferLen = dwBlockLen; 
	
	//--------------------------------------------------------------------
	// Allocate memory. 
	
	if(!(pbBuffer = (BYTE *)malloc(dwBufferLen)))
	{
		bFlag = FALSE;
		goto end;
	}
	//--------------------------------------------------------------------
	// Decrypt source file, and write to destination file. 
	
	do { 
		//--------------------------------------------------------------------
		// Read up to dwBlockLen bytes from source file. 
		
		dwCount = fread(
			pbBuffer, 
			1, 
			dwBlockLen, 
			hSource); 
		if(ferror(hSource))
		{
			bFlag = FALSE;
			goto end;
		}
		//--------------------------------------------------------------------
		// Decrypt data. 
		if(!CryptDecrypt(
			hKey, 
			0, 
			feof(hSource), 
			0, 
			pbBuffer, 
			&dwCount))
		{
			bFlag = FALSE;
			goto end;
		}
		//--------------------------------------------------------------------
		// Write data to destination file. 
		
		fwrite(
			pbBuffer, 
			1, 
			dwCount, 
			hDestination); 
		if(ferror(hDestination))
		{
			bFlag = FALSE;
			goto end;
		}
	} while(!feof(hSource)); 

end:
	//--------------------------------------------------------------------
	// Close files. 
	if(hSource) 
		fclose(hSource); 
	if(hDestination) 
		fclose(hDestination); 
	
	//--------------------------------------------------------------------
	// Free memory. 
	
	if(pbBuffer) 
		free(pbBuffer); 
	
	//--------------------------------------------------------------------
	// Destroy session key. 
	
	if(hKey) 
		CryptDestroyKey(hKey); 
	
	//--------------------------------------------------------------------
	// Destroy hash object. 
	if(hHash) 
		CryptDestroyHash(hHash); 
	
	//--------------------------------------------------------------------
	// Release provider handle. 
	
	if(hCryptProv) 
		CryptReleaseContext(hCryptProv, 0); 
	
	return bFlag;
}

void GB2312ToUTF_8(CString& pOut,char *pText, int pLen)
{
    char buf[4];
    memset(buf,0,4);
	
    //pOut.clear();
	
    int i = 0;
    while(i < pLen)
    {
        //如果是英文直接复制就可以
        if( pText[i] >= 0)
        {
            char asciistr[2]={0};
            asciistr[0] = (pText[i++]);
			// pOut.append(asciistr);
			pOut += asciistr;
        }
        else
        {
            WCHAR pbuffer;
            Gb2312ToUnicode(&pbuffer,pText+i);
			
            UnicodeToUTF_8(buf,&pbuffer);
			
            // pOut.append(buf);
			pOut += buf;
			
            i += 2;
        }
    }
	
    return;
}

CString UrlUTF8(char * str)
{
    CString tt;
    CString dd;
    GB2312ToUTF_8(tt,str,(int)strlen(str));
	
    int len=tt.GetLength();
    for (int i=0;i<len;i++)
    {
        if(isalnum((BYTE)tt[i]))
        {
            char tempbuff[2]={0};
            sprintf_s(tempbuff,"%c",(BYTE)tt[i]);
			dd += tempbuff;
            // dd.append(tempbuff);
        }
        else if (isspace((BYTE)tt[i]))
        {
            // dd.append("+");
			dd += "+";
        }
        else
        {
            char tempbuff[4];
            sprintf_s(tempbuff,"%%%X%X",((BYTE)tt[i]) >>4,((BYTE)tt[i]) %16);
            // dd.append(tempbuff);
			dd += tempbuff;
        }
		
    }
    return dd;
}

void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer)
{
    ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
    return;
}

void UnicodeToUTF_8(char* pOut,WCHAR* pText)
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;
	
    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));
	
    return;
}

CString UTF8ToGB2312(LPCSTR lpszInBuf)
{
	CString str;
	if(NULL == lpszInBuf)
	{
		return str;
	}
	LPWSTR lpszTmp = UTF8ToUnicode(lpszInBuf);
	LPSTR lpszBuf = UnicodeToGB2312(lpszTmp);
	str = lpszBuf;

	delete[] lpszTmp;
	delete[] lpszBuf;
	lpszTmp = NULL;
	lpszBuf = NULL;

	return str;
}

LPWSTR UTF8ToUnicode(LPCSTR lpszInBuf)
{
	if(NULL == lpszInBuf)
	{
		return NULL;
	}
	WCHAR* pBuf = NULL;
	int nLen = MultiByteToWideChar(CP_UTF8, 0, lpszInBuf, -1, pBuf, 0);
	pBuf = new WCHAR[nLen];
	memset(pBuf, 0, sizeof(WCHAR) * nLen);
	MultiByteToWideChar(CP_UTF8, 0, lpszInBuf, -1, pBuf, nLen);
	return pBuf;
}

LPSTR UnicodeToGB2312(LPCWSTR lpszInBuf)
{
	if(NULL == lpszInBuf)
	{
		return NULL;
	}
	CHAR* pBuf = NULL;
	int nLen = WideCharToMultiByte(CP_ACP, 0, lpszInBuf, -1, pBuf, 0, NULL, NULL);
	pBuf = new CHAR[nLen];
	memset(pBuf, 0, sizeof(CHAR) * nLen);
	WideCharToMultiByte(CP_ACP, 0, lpszInBuf, -1, pBuf, nLen, NULL, NULL);
	return pBuf;
}

//UTF-8转Unicode  
std::wstring Utf82Unicode(const std::string& utf8string)  
{  
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);  
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)  
	{  
		throw std::exception("Invalid UTF-8 sequence.");  
	}  
	if (widesize == 0)  
	{  
		throw std::exception("Error in conversion.");  
	}  

	std::vector<wchar_t> resultstring(widesize);  

	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);  

	if (convresult != widesize)  
	{  
		throw std::exception("La falla!");  
	}  

	return std::wstring(&resultstring[0]);  
}  

//unicode 转为 ascii  

string WideByte2Acsi(wstring& wstrcode)  
{  
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);  
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)  
	{  
		throw std::exception("Invalid UTF-8 sequence.");  
	}  
	if (asciisize == 0)  
	{  
		throw std::exception("Error in conversion.");  
	}  
	std::vector<char> resultstring(asciisize);  
	int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);  

	if (convresult != asciisize)  
	{  
		throw std::exception("La falla!");  
	}  

	return std::string(&resultstring[0]);  
}  

//utf-8 转 ascii  

string UTF_82ASCII(string& strUtf8Code)  
{  
	string strRet("");  


	//先把 utf8 转为 unicode   
	wstring wstr = Utf82Unicode(strUtf8Code);  

	//最后把 unicode 转为 ascii  
	strRet = WideByte2Acsi(wstr);  


	return strRet;  
}  

///////////////////////////////////////////////////////////////////////  

//ascii 转 Unicode  

wstring Acsi2WideByte(string& strascii)  
{  
	int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);  
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)  
	{  
		throw std::exception("Invalid UTF-8 sequence.");  
	}  
	if (widesize == 0)  
	{  
		throw std::exception("Error in conversion.");  
	}  
	std::vector<wchar_t> resultstring(widesize);  
	int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);  

	if (convresult != widesize)  
	{  
		throw std::exception("La falla!");  
	}  

	return std::wstring(&resultstring[0]);  
}  

//Unicode 转 Utf8  

std::string Unicode2Utf8(const std::wstring& widestring)  
{  
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);  
	if (utf8size == 0)  
	{  
		throw std::exception("Error in conversion.");  
	}  

	std::vector<char> resultstring(utf8size);  

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);  

	if (convresult != utf8size)  
	{  
		throw std::exception("La falla!");  
	}  

	return std::string(&resultstring[0]);  
}  

//ascii 转 Utf8  

string ASCII2UTF_8(string& strAsciiCode)  
{  
	string strRet("");  


	//先把 ascii 转为 unicode   
	wstring wstr = Acsi2WideByte(strAsciiCode);  

	//最后把 unicode 转为 utf8  

	strRet = Unicode2Utf8(wstr);  


	return strRet;  
}

void GetServerInfo(const CString& strFile, const CString& strKey, SERVERINFO& ServerInfo)
{
	char szServer[MAX_PATH];
	GetPrivateProfileString(strKey, "ServerIP", "", szServer, MAX_PATH, strFile);
	ServerInfo.strServer = szServer;

	GetPrivateProfileString(strKey, "UserName", "", szServer, MAX_PATH, strFile);
	ServerInfo.strUser = szServer;

	GetPrivateProfileString(strKey, "PW", "", szServer, MAX_PATH, strFile);
	CString strDecryp = szServer;
	if (strDecryp.IsEmpty() == FALSE)
	{
		DecryptString(strDecryp, ServerInfo.strPassword, ENCRYPT_STRING_USERPWD_KEY);
	}

	GetPrivateProfileString("Local", "Save", "", szServer, MAX_PATH, strFile);
	ServerInfo.strState = szServer;
}


void WriteServerInfo(const CString& strFile, const CString& strKey, const SERVERINFO& ServerInfo)
{
	WritePrivateProfileString(strKey, "ServerIP", ServerInfo.strServer, strFile);

	WritePrivateProfileString(strKey, "UserName", ServerInfo.strUser, strFile);

	WritePrivateProfileString(strKey, "PW", ServerInfo.strPassword, strFile);

	WritePrivateProfileString(strKey, "Save", ServerInfo.strState, strFile);
}

void EmptyServerInfo(const CString& strFile, const CString& strKey)
{	
	WritePrivateProfileString(strKey, "PW", "", strFile);

	WritePrivateProfileString(strKey, "Save", "0", strFile);
}

BOOL ConnectDB(LPSERVERINFO lpServerInfo)
{
	if (lpServerInfo == NULL)
		return FALSE;

	if (lpServerInfo->pSQL)
	{
		mysql_close(lpServerInfo->pSQL);
		lpServerInfo->pSQL = NULL;
	}
	if (lpServerInfo->strServer.IsEmpty())
	{
		AfxMessageBox("没有指定数据库.");
		return FALSE;
	}

	lpServerInfo->pSQL = mysql_init(NULL);
	CString strPwd;
	// EncryptString(lpServerInfo->strPassword, strPwd);
	
	/*
	if (lpServerInfo->strServer != "121.40.122.137")
		strPwd = "gcMAnERQ790327";
	else
		strPwd = "jfdKf3*93*fjLFK";
	*/
	strPwd = "gcMAnERQ790327";
	int iFind = lpServerInfo->strServer.Find(":");
	CString strServer;
	int iPort = 3306;
	if (iFind < 0)
		strServer = lpServerInfo->strServer;
	else
	{
		strServer = lpServerInfo->strServer.Mid(0, iFind);
		iPort = atoi(lpServerInfo->strServer.Mid(iFind+1));
	}

	if (mysql_real_connect(lpServerInfo->pSQL, strServer,"root",strPwd,"zhixunzhishi",iPort,NULL,0))
	{
		mysql_real_query(lpServerInfo->pSQL, "SET NAMES GBK", strlen("SET NAMES GBK"));
		return TRUE;
	}
	else
	{
		AfxMessageBox("无法访问数据库.");
		mysql_close(lpServerInfo->pSQL);
		lpServerInfo->pSQL = NULL;
		return FALSE;
	}
}

BOOL ExecuteSQL(LPSERVERINFO lpServerInfo, const CString& strSQL)
{
	if (ConnectDB(lpServerInfo))
	{
		if(mysql_real_query(lpServerInfo->pSQL, strSQL, strSQL.GetLength()) ==0)
		{
			return TRUE;
		}
		else
		{
			AfxMessageBox("访问数据库出错.");
		}
	}
	return FALSE;
}