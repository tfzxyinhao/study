#include "stdafx.h"
#include "FilePath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int CFilePath::GetModulePath( CString& strModulePath )
{
	strModulePath.GetBuffer(MAX_PATH);
	GetModuleFileName(NULL,strModulePath.GetBuffer(0),MAX_PATH);
	strModulePath.ReleaseBuffer();
	
	int nQuote = strModulePath.ReverseFind('\\');
	if(nQuote == -1)
		return 0;

	strModulePath.SetAt(nQuote,'\0');
	strModulePath.GetBufferSetLength(nQuote);
	return strModulePath.GetLength();
}

int CFilePath::GetModulePath( LPTSTR lpstrModulePath,int nMaxLen )
{
	if(lpstrModulePath == NULL)
		return 0;

	int nLen = GetModuleFileName(NULL,lpstrModulePath,nMaxLen);
	if(nLen <=0)
		return 0;

	const char* pQuote = strrchr(lpstrModulePath,'\\');
	if(pQuote == NULL)
		return 0;

	nLen = pQuote - lpstrModulePath;
	lpstrModulePath[nLen] = '\0';

	return nLen;
}

int CFilePath::IsFileExists( LPCTSTR lpstrFileName )
{
	if(lpstrFileName == NULL)
		return 0;

	HANDLE hFile = CreateFile(lpstrFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_BACKUP_SEMANTICS,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return 0;

	CloseHandle(hFile);
	return 1;
}

//E:\DevPrj\TestProj\FileTest\FilePath.cpp
int CFilePath::MakeSurePathExists( LPCTSTR lpstrPath )
{
	if(lpstrPath == NULL)
		return 0;

	int nPathLen = strlen(lpstrPath);
	if(nPathLen >= MAX_PATH)
		return 0;

	char PathBuf[MAX_PATH] = {0};
	const char* pExt = strchr(lpstrPath,'\\');
	if(pExt == NULL)
		return 0;

	pExt +=1;
	int nLen = 0;
	while (pExt)
	{
		pExt = strchr(pExt,'\\');
		if(pExt == NULL)
		{
			strcpy(PathBuf,lpstrPath);
			PathBuf[nPathLen] = '\0';
			if(!CreateDirectory(PathBuf,NULL))
			{
				if(ERROR_PATH_NOT_FOUND == GetLastError())
					return 0;
			}
			break;
		}
		
		pExt += 1;
		nLen = pExt - lpstrPath;
		strncpy(PathBuf,lpstrPath,nLen);
		PathBuf[nLen] = '\0';
		
		if(!CreateDirectory(PathBuf,NULL))
		{
			DWORD dwError = GetLastError();
			if(ERROR_PATH_NOT_FOUND == dwError || ERROR_NOT_READY == dwError)
				return 0;
		}
	}
	return 1;
}

int CFilePath::IsRootPath( LPCTSTR lpstrPath )
{
	if(lpstrPath == NULL)
		return 0;

	const char* pstr = strrchr(lpstrPath,'\\');
	if(pstr != NULL)
		return 0;

	return 1;
}

int CFilePath::GetParentPath(LPCTSTR lpstrPath,LPTSTR lpstrParentPath,int nMaxLen )
{
	if(lpstrPath == NULL)
		return 0;
	
	int nLen = 0;
	const char* pQuote = strrchr(lpstrPath,'\\');
	if(pQuote != NULL)
	{
		nLen = pQuote - lpstrPath;
		if(nMaxLen >= nLen)
		{
			strncpy(lpstrParentPath,lpstrPath,nLen);
			lpstrParentPath[nLen] = '\0';
		}
	}
	return nLen;
}

BOOL CFilePath::IsAbsolutePath( LPCTSTR lpstrPath )
{
	if(lpstrPath == NULL)
		return FALSE;

	int nLen = strlen(lpstrPath);
	if(nLen >= 3)
	{
		if(lpstrPath[1] == ':' && lpstrPath[2] == '\\' && isalpha(lpstrPath[0]))
			return TRUE;
	}
	if(nLen == 2)
	{
		if(lpstrPath[1] == ':' && isalpha(lpstrPath[0]))
			return TRUE;
	}
	
	return FALSE;
}