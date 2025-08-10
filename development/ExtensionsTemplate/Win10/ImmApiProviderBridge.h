/*
	Date: 2025-Present

	Bashar Astifan (https://github.com/basharast):
	ImMobile Extension
	Legacy support as tested on 10240
*/

#pragma once

#ifdef __cplusplus
#include "StoragePath.h"
#include "StorageInfo.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <concrt.h>
#include <queue>
#include <memory>
#include <stdexcept>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath> 
#include <exception>
#include <new>
#include <sstream>
#include <filesystem>
#include <ppl.h>
#include <ppltasks.h>
#include <atomic>

#ifndef IMM_MAIN_INCLUDE
namespace Imm {
	/* LOGGER */
	namespace Logger {
		void Normal(std::string text);

		void Warn(std::string text);

		void Error(std::string text);

		void Notice(std::string text);

		void Success(std::string text);
	}

	/* DLL */
	namespace DLL {
		HMODULE LoadLibrary(std::string filename);

		FARPROC GetFromKernel(std::string process);

		// Not Working
		FARPROC GetFromUser(std::string process);
	}

	/* STORAGE */
	namespace Storage {
		/* PICKERS */
		namespace Pickers {
			// Filters can be like: 'Image{.jpg,.png,.jpeg},.*'
			// Don't add spaces between filters
			// Simply access to the first item if multiple is false
			// as example: path[0].ToString()
			void ChooseFile(std::function<void(const std::vector<PathUWP> files)> callback, std::string filters = ".*", bool multiple = false);

			void SaveFile(std::function<void(std::string path)> callback, std::string suggestedName = "");

			// Simply access to the first item if multiple is false
			// as example: path[0].ToString()
			void ChooseFolder(std::function<void(const std::vector<PathUWP> folders)> callback, bool multiple = false);
		}

		/* LOCATIONS */
		namespace Locations {
			std::string InstallationFolder();

			std::string InternalIcons(std::string icon);

			std::string LocalFolder();

			std::string TempFolder();

			// If user didn't set custom folder, by default this will be localstate
			std::string DataFolder();

			// Refers to ImMobile data folders not OS
			std::string MusicFolder();

			// Refers to ImMobile data folders not OS
			std::string VideosFolder();

			// Refers to ImMobile data folders not OS
			std::string PicturesFolder();

			std::string BackupFolder();

			std::string ExtensionsFolder();

			std::string RuntimesFolder();

			std::string DownloadsFolder();

			std::string TexturesFolder();

			std::string UpdatesFolder();

			std::string StartupFolder();

			std::string FontsFolder();

			std::string TempFilesFolder();

			// Replace strings like %appdata% with proper value
			std::string EnvironmentVariables(const std::string& path);

			// Output name may differ than input if already exists
			// if empty file failed to create
			std::string GetTempFile(std::string name);

		}

		/* MANAGE */
		namespace Manage {
			// Require 14393+ for outside localstate
			// Be careful, if the method fail, may cause file lock
			// if you want to create file without HANDLE then:
			// Use 'Imm::Storage::Stream' as below:
			// - 'fopen' and friends designed to fallback to UWP
			// - 'FilePutContents' can help to create new files
			// - 'FileGetContents' also helpful with the mode like 'w+'
			HANDLE CreateFile(std::string path, long accessMode = 0x80000000L, long shareMode = 0x00000001, long openMode = 3);

			bool CreateFolder(std::string path, bool replaceExisting = true, bool skipIfExists = false);

			std::list<ItemInfoUWP>GetFolderContents(std::string path, bool deepScan = false);

			bool IsExists(std::string path);

			bool IsDirectory(std::string path);

			int64_t GetSize(std::string path);

			bool Delete(std::string path);

			bool Rename(std::string path, std::string name);

			// Add file name to destination path
			bool Copy(std::string path, std::string dest, std::atomic<bool>* cancelled, std::atomic<int>* progress);

			// Add file name to destination path
			bool Move(std::string path, std::string dest, std::atomic<bool>* cancelled, std::atomic<int>* progress);

			// Check if folder accessible for UWP APIs
			bool CheckPathAccess(std::string path);

			// Drive name like 'C:'
			// Use 'checkFutureAccess' for listing purposes
			bool CheckDriveAccess(std::string driveName, bool checkFutureAccess);

			bool GetDriveFreeSpace(PathUWP path, int64_t& space);
		}

		/* STREAM */
		/* Those desgined to deal with internal UWP resolvers */
		namespace Stream {
			// To avoid issues use it with Imm::Storage::Stream functions
			FILE* FileGetStream(std::string path, const char* mode);

			// Has legacy support
			std::string FileGetContents(bool& state, std::string path, const char* mode = "r+", bool reportIfNotExists = true);

			bool FilePutContents(std::string path, std::string content, bool backup = false, bool createnew = false);

			// Helpful for legacy support to get file buffer
			uint8_t* FileGetBuffer(std::string path, size_t& outSize);

			// To avoid issues use it with Imm::Storage::Stream functions
			FILE* fopen(const char* filename, const char* mode);

			size_t fread(void* ptr, size_t size, size_t count, FILE* stream);

			size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

			int fseek(FILE* stream, long offset, int origin);

			int fclose(FILE* stream);

			int ferror(FILE* stream);

			int feof(FILE* stream);

			long ftell(FILE* stream);

			__int64 ftelli64(FILE* stream);

			void rewind(FILE* stream);

			int fflush(FILE* stream);

			FILE* freopen(const char* filename, const char* mode, FILE* stream);

			int fseeki64(FILE* stream, __int64 offset, int origin);

			int fgetc(FILE* stream);

			wint_t fgetwc(FILE* stream);

			int ungetc(int character, FILE* stream);

			wint_t ungetwc(wint_t character, FILE* stream);

			int fputc(int character, FILE* stream);

			wint_t fputwc(wchar_t character, FILE* stream);

			int fputs(const char* buffer, FILE* stream);

			int fputws(const wchar_t* buffer, FILE* stream);

			char* fgets(char* buffer, int maxCount, FILE* stream);

			wchar_t* fgetws(wchar_t* buffer, int maxCount, FILE* stream);

			extern int(*fprintf)(FILE* stream, const char* format, ...);

			extern int(*fwprintf)(FILE* stream, const wchar_t* format, ...);

			extern int(*fscanf)(FILE* stream, const char* format, ...);

			extern int(*fwscanf)(FILE* stream, const wchar_t* format, ...);

			int fstat(const char* name, struct stat* out);
		}

		/* PATH */
		namespace Path {
			// Ensure all '/' replaced by '\'
			void WindowsPath(std::string& path);

			std::string CombinePath(std::string fullPath, std::string subPath);

			bool IsChild(std::string parent, std::string child);

			// Parent full path, child full path, child name only
			bool IsParent(std::string parent, std::string child, std::string childName);

			// Parent and child full path
			std::string SubRoot(std::string parent, std::string child);
		}
	}

	/* ARCHIVES */
	namespace Archives {
		// Callback (state, output), pass nullptr if you want to skip callback
		void Extract(std::string archive, std::string dest, std::function<void(bool state, std::string output)> callback);

		// Callback (state, output), pass nullptr if you want to skip callback
		void Compress(std::string folder, std::string archive, std::function<void(bool state, std::string output)> callback, bool store);
	}
}
#endif

#endif // __cplusplus

#pragma endregion