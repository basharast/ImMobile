/*
Date: 2025-Present

Bashar Astifan (https://github.com/basharast):
ImMobile Extension
Legacy support as tested on 8.1 (6.3.9651.0)
*/

#pragma once

#include "windows.h"

#ifndef __cplusplus
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#else
#include <cstdio>
#include <cstdlib>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef IMM_MAIN_INCLUDE
	HANDLE CreateFileC(char* path, long accessMode, long shareMode, long openMode);

	FILE* fopenImm(const char* filename, const char* mode);

	size_t freadImm(void* ptr, size_t size, size_t count, FILE* stream);

	size_t fwriteImm(const void* ptr, size_t size, size_t count, FILE* stream);

	int fseekImm(FILE* stream, long offset, int origin);

	int fcloseImm(FILE* stream);

	int ferrorImm(FILE* stream);

	int feofImm(FILE* stream);

	long ftellImm(FILE* stream);

	__int64 ftelli64Imm(FILE* stream);

	void rewindImm(FILE* stream);

	int fflushImm(FILE* stream);

	FILE* freopenImm(const char* filename, const char* mode, FILE* stream);

	int fseeki64Imm(FILE* stream, __int64 offset, int origin);

	int fgetcImm(FILE* stream);

	wint_t fgetwcImm(FILE* stream);

	int ungetcImm(int character, FILE* stream);

	wint_t ungetwcImm(wint_t character, FILE* stream);

	int fputcImm(int character, FILE* stream);

	wint_t fputwcImm(wchar_t character, FILE* stream);

	int fputsImm(const char* buffer, FILE* stream);

	int fputwsImm(const wchar_t* buffer, FILE* stream);

	char* fgetsImm(char* buffer, int maxCount, FILE* stream);

	wchar_t* fgetwsImm(wchar_t* buffer, int maxCount, FILE* stream);

	extern int(*fprintfImm)(FILE* stream, const char* format, ...);

	extern int(*fwprintfImm)(FILE* stream, const wchar_t* format, ...);

	extern int(*fscanfImm)(FILE* stream, const char* format, ...);

	extern int(*fwscanfImm)(FILE* stream, const wchar_t* format, ...);

	int fstatImm(const char* name, struct stat* out);

	int removeImm(const void* name);

	int renameImm(char const* oldFileName, char const* newFileName);

	LPVOID VirtualAllocImm(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);

	BOOL VirtualProtectImm(LPVOID lpAddress, SIZE_T dwSize, DWORD  flNewProtect, PDWORD lpflOldProtect);

	HANDLE CreateFileMappingWImm(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName);

	LPVOID MapViewOfFileExImm(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress);

	BOOL UnmapViewOfFileImm(LPCVOID lpBaseAddress);

	SIZE_T VirtualQueryImm(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

	BOOL FlushInstructionCacheImm(HANDLE  hProcess, LPCVOID lpBaseAddress, SIZE_T  dwSize);

	HANDLE FindFirstFileAImm(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);

	HANDLE FindFirstFileWImm(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);

	BOOL DeviceIoControlImm(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

	HANDLE CreateFileWImm(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

	HANDLE CreateEventWImm(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);

	BOOL CancelIoImm(HANDLE hFile);

	BOOL GetOverlappedResultImm(HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);

	BOOL GetVolumePathNameWImm(LPCWSTR lpszFileName, LPWSTR lpszVolumePathName, DWORD cchBufferLength);

	UINT GetDriveTypeWImm(LPCWSTR lpRootPathName);

	BOOL GetDiskFreeSpaceWImm(LPCWSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters);

	BOOL SetFileTimeImm(HANDLE hFile, const FILETIME *lpCreationTime, const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime);

	char *getenvImm(const char *varname);

	BOOL VirtualFreeImm(LPVOID lpAddress, SIZE_T dwSize, DWORD  dwFreeType);

	LPVOID VirtualAllocImm(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtect);

	BOOL PeekNamedPipeImm(HANDLE  hNamedPipe, LPVOID  lpBuffer, DWORD   nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage);

	UINT GetACPImm();

	DWORD GetTempPathWImm(DWORD  BufferLength, LPWSTR Buffer);

	DWORD GetFullPathNameWImm(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart);

	DWORD GetFileAttributesAImm(LPCSTR lpFileName);

	DWORD GetFileTypeImm(HANDLE hFile);

	BOOL GetExitCodeProcessImm(HANDLE hProcess, LPDWORD lpExitCode);

	DWORD SetFilePointerImm(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);

	DWORD GetCurrentDirectoryWImm(DWORD nBufferLength, LPTSTR lpBuffer);
#endif 

#ifdef __cplusplus
}
#endif
