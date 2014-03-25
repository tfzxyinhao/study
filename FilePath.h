#if !defined(AFX_FILEPATH_H__B8700BF9_C0A7_4713_8546_C4CF79A2E7EE__INCLUDED_)
#define AFX_FILEPATH_H__B8700BF9_C0A7_4713_8546_C4CF79A2E7EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFilePath  
{
public:
	static int GetParentPath(LPCTSTR lpstrPath,LPTSTR lpstrParentPath,int nMaxLen);
	static int IsRootPath(LPCTSTR lpstrPath);
	static int GetModulePath(CString& strModulePath);
	static int GetModulePath(LPTSTR lpstrModulePath,int nMaxLen);
	static int IsFileExists(LPCTSTR lpstrFileName);
	static int MakeSurePathExists(LPCTSTR lpstrPath);
	static BOOL IsAbsolutePath( LPCTSTR lpstrPath );
};
#endif // !defined(AFX_FILEPATH_H__B8700BF9_C0A7_4713_8546_C4CF79A2E7EE__INCLUDED_)
