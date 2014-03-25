#include "StdAfx.h"
#include "Logger.h"

CLogger* CLogger::g_Logger = nullptr;

CLogger::CLogger(void)
:m_logIndex(0),m_dwMaxSize(2<<20),m_dwLastWrite(0),m_hLogFile(0)
{
	NewLog();
}

CLogger::~CLogger(void)
{
	CloseHandle(m_hLogFile);
}

void CLogger::Info( LPCTSTR lpstr,... )
{
	if(m_hLogFile){
		TimeStamp();
		size_t len;
		va_list args;
		va_start(args, lpstr);
		len = vsprintf_s(tmp,MAXBUFERSIZE,lpstr, args);
		WriteFile(m_hLogFile,tmp,len,&m_dwLastWrite,NULL);
		va_end (args);

		if(GetFileSize(m_hLogFile,NULL) > m_dwMaxSize)
			NewLog();
	}
}

void CLogger::Warn( LPCTSTR lpstr,... )
{
	if(m_hLogFile){
		TimeStamp();
		size_t len;
		va_list args;
		va_start(args, lpstr);
		len = vsprintf_s(tmp,MAXBUFERSIZE,lpstr, args);
		WriteFile(m_hLogFile,tmp,len,&m_dwLastWrite,NULL);
		va_end (args);

		if(GetFileSize(m_hLogFile,NULL) > m_dwMaxSize)
			NewLog();
	}
}

void CLogger::Debug( LPCTSTR lpstr,... )
{
	if(m_hLogFile){
		TimeStamp();
		size_t len;
		va_list args;
		va_start(args, lpstr);
		len = vsprintf_s(tmp,MAXBUFERSIZE,lpstr, args);
		WriteFile(m_hLogFile,tmp,len,&m_dwLastWrite,NULL);
		va_end (args);

		if(GetFileSize(m_hLogFile,NULL) > m_dwMaxSize)
			NewLog();
	}
}

void CLogger::Error( LPCTSTR lpstr,... )
{
	if(m_hLogFile){
		TimeStamp();
		size_t len;
		va_list args;
		va_start(args, lpstr);
		len = vsprintf_s(tmp,MAXBUFERSIZE,lpstr, args);
		WriteFile(m_hLogFile,tmp,len,&m_dwLastWrite,NULL);
		va_end (args);

		if(GetFileSize(m_hLogFile,NULL) > m_dwMaxSize)
			NewLog();
	}
}

CLogger* CLogger::GetLogger()
{
	if(g_Logger == nullptr)
		g_Logger = new CLogger();

	return g_Logger;
}

void CLogger::TimeStamp()
{
	size_t len;
	SYSTEMTIME st;
	GetSystemTime(&st);
	len = sprintf_s(tmp,MAXBUFERSIZE,"%04d%02d%02d%02d%02d%02d\t",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	WriteFile(m_hLogFile,tmp,len,&m_dwLastWrite,NULL);
}

void CLogger::NewLog()
{
	if(m_hLogFile){
		CloseHandle(m_hLogFile);
		m_hLogFile = nullptr;
	}

	DWORD dwLen;
	TCHAR szDir[MAX_PATH];
	TCHAR szlogfile[MAX_PATH];
	dwLen = GetModuleFileName(NULL,szDir,MAX_PATH);
	if(dwLen){
		char* pos = strrchr(szDir,'.');
		if(pos)
			*pos = '\0';

		++m_logIndex;
		sprintf_s(szlogfile,"%s%d.log",szDir,m_logIndex);
		m_hLogFile = CreateFile(szlogfile,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(m_hLogFile == INVALID_HANDLE_VALUE)
			m_hLogFile = nullptr;

		SetFilePointer(m_hLogFile,0,0,SEEK_END);
	}
}

void CLogger::SetMaxLogSize( size_t new_size )
{
	m_dwMaxSize = new_size;
}

void CLogger::Release()
{
	CloseHandle(m_hLogFile);
	m_hLogFile = nullptr;
	delete g_Logger;
	g_Logger = nullptr;
}


