#if !defined(AFX_DUMP_H__F6CE24A2_F646_4700_8B31_C091BD185C66__INCLUDED_)
#define AFX_DUMP_H__F6CE24A2_F646_4700_8B31_C091BD185C66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DbgHelp.h>
#pragma comment ( lib, "dbghelp.lib" )
class CDump  
{
public:
	static void Start();
	static void Stop();
	static long	WINAPI StartAutoDump(struct _EXCEPTION_POINTERS *pep);
};

#endif // !defined(AFX_DUMP_H__F6CE24A2_F646_4700_8B31_C091BD185C66__INCLUDED_)
