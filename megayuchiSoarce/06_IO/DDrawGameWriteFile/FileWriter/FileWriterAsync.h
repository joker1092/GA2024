#pragma once

#include "IFileWriter.h"

class CFileWriterAsync : public IFileWriter
{
	HANDLE m_hFile = INVALID_HANDLE_VALUE;
	char* m_pWriteBuffer = nullptr;
	DWORD m_dwWriteBufferSize = 0;
	UINT64 m_ui64AccumWrittenBytes = 0;
	UINT64 m_ui64MaxFileSize = 0;
	BOOL	m_bIsWriting = FALSE;
	OVERLAPPED m_Overlapped = {};
	BOOL	m_bIsPending = FALSE;
	DWORD	m_dwPendingBytes = 0;
	void	Close();

	BOOL	WaitForFlush(DWORD* pdwOutTranferredBytes);
	void	Cleanup();

public:
	BOOL	__stdcall Initialize(UINT64 ui64MaxFileSize);
	BOOL	__stdcall Write(const char* pImageData, DWORD dwWidth, DWORD dwHeight, DWORD dwPitch);
	BOOL	__stdcall IsWriting() const;
	BOOL	__stdcall Begin(const WCHAR* wchFileName);
	void	__stdcall Stop();
	void	__stdcall Destroy();
	FILE_WRITER_TYPE __stdcall GetType();

	CFileWriterAsync();
	~CFileWriterAsync();
};