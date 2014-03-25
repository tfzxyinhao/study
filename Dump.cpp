#include "stdafx.h"

#include "Dump.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



void CDump::Start()
{
	SetUnhandledExceptionFilter(StartAutoDump);
}

long	WINAPI CDump::StartAutoDump( struct _EXCEPTION_POINTERS *pep )
{
	TCHAR	szFileName[_MAX_PATH]	= {0};
	SYSTEMTIME stLocalTime;
	GetLocalTime( &stLocalTime );
	sprintf( szFileName,_T("%d%d%d%d%d.dmp"),stLocalTime.wYear,stLocalTime.wMonth,stLocalTime.wDay,stLocalTime.wHour,stLocalTime.wMinute);  
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	
	if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
	{	
		MINIDUMP_EXCEPTION_INFORMATION mdei; 
		mdei.ThreadId           = GetCurrentThreadId(); 
		mdei.ExceptionPointers  = pep; 
		mdei.ClientPointers     = FALSE; 
		MINIDUMP_TYPE mdt       = static_cast<MINIDUMP_TYPE>(MiniDumpNormal |MiniDumpWithDataSegs|MiniDumpWithHandleData|MiniDumpWithProcessThreadData); 
		MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, mdt, (pep != 0) ? &mdei : 0, 0, 0 ); 
		CloseHandle( hFile );
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

void CDump::Stop()
{
	SetUnhandledExceptionFilter(NULL);
}
