/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
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

#endif 

#ifdef __cplusplus
}
#endif
