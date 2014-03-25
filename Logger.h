#pragma once

#define MAXBUFERSIZE	1024

#define __FILE_NAME__ (strrchr(__FILE__,'\\')+1)



#define INFO(s) CLogger::GetLogger()->Info("%s(%d)\t%s\r\n",__FILE_NAME__,__LINE__,s)
#define DBUG(s) CLogger::GetLogger()->Info("%s(%d)\t%s\r\n",__FILE_NAME__,__LINE__,s)
#define WARN(s) CLogger::GetLogger()->Info("%s(%d)\t%s\r\n",__FILE_NAME__,__LINE__,s)
#define ERRO(s) CLogger::GetLogger()->Info("%s(%d)\t%s\r\n",__FILE_NAME__,__LINE__,s)



#define FINFO(fmt,...) (CLogger::GetLogger()->Info(("%s(%d)\t" fmt "\r\n"),__FILE_NAME__,__LINE__,##__VA_ARGS__))
#define FDBUG(fmt,...) (CLogger::GetLogger()->Info(("%s(%d)\t" fmt "\r\n"),__FILE_NAME__,__LINE__,##__VA_ARGS__))
#define FWARN(fmt,...) (CLogger::GetLogger()->Info(("%s(%d)\t" fmt "\r\n"),__FILE_NAME__,__LINE__,##__VA_ARGS__))
#define FERRO(fmt,...) (CLogger::GetLogger()->Info(("%s(%d)\t" fmt "\r\n"),__FILE_NAME__,__LINE__,##__VA_ARGS__))

#define LOGFREE	(CLogger::GetLogger()->Release())

class CLogger
{
private:
	CLogger(void);
	~CLogger(void);

	size_t	m_logIndex;
	DWORD	m_dwMaxSize;
	DWORD	m_dwLastWrite;
	HANDLE	m_hLogFile;

	TCHAR tmp[MAXBUFERSIZE];
	static CLogger* g_Logger;
public:
	static CLogger* GetLogger();

	void Release();
	void TimeStamp();
	void Info(LPCTSTR lpstr,...);
	void Warn(LPCTSTR lpstr,...);
	void Debug(LPCTSTR lpstr,...);
	void Error(LPCTSTR lpstr,...);
	void NewLog();
	void SetMaxLogSize(size_t new_size);
};

